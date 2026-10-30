// difflib
#include <curl.h>
#include <json.hpp>
#include <portaudio.h>
#include <baseapi.h>
#include <allheaders.h>
#include <random>
#include <filesystem>
#include <regex>
#include <string>
// atexit
// yolo
#include <chrono>
#include <ctime>
// face_regocntion
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <microphone_index.hpp>
#include <webcam_index.hpp>
#include <cstddef>
#include <random>
#include <cctype>
#include <stdexcept>
#include <whisper.h>
#include <format>

using json = nlohmann::json;
namespace fs = std::filesystem;
const char* MICROPHONE_INDEX = "microphone_index.hpp";
const char* sr = "portaudio.h";
std::string MEMORY_FILE = "mrmy.json";
const char* whisper = "whisper.h";

struct PRSE_RESPN
{
    std::string dialogue;
    std::vector<std::string> actions;
};

whisper_context_params ctx_params = whisper_context_default_params();

whisper_context* ctx = whisper_init_from_file_with_params("C:\\whisper.cpp\\ggml-base.en.bin", ctx_params);

// load configs

json configread(void)
{
    std::ifstream file("config.json");

    if (!file.is_open())
    {
        throw std::runtime_error("CONFIG LOAD ERR");
    }

    json CONFIG;
    file >> CONFIG;
    file.close();

    std::vector<std::string> WAKE_WORDS = CONFIG.value("wake_words", std::vector<std::string>{});
    std::vector<std::string> WAKE_PREFIXES = CONFIG.value("wake_prefixes", std::vector<std::string>{"", "ok ", "hay ", "hey "});

    std::string USER_NAME = CONFIG.at("user_name").get<std::string>();

    return CONFIG;
}

// global var
std::vector<std::string> known_face_encodings;
std::vector<std::string> known_face_names;
std::string current_speaker = "Unknown";
std::vector<std::string> temp_memory_cache;

json config = configread();
std::string USER_NAME = config.at("user_name").get<std::string>();

std::string transcribe_audio(whisper_context* ctx, const std::vector<float>& audio_samples)
{
    if (ctx == nullptr || audio_samples.empty())
    {
        return "";
    }

    whisper_full_params params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);

    params.print_progress = false;
    params.print_realtime = false;
    params.print_timestamps = false;

    int result = whisper_full(ctx, params, audio_samples.data(), static_cast<int>(audio_samples.size()));

    if (result != 0)
    {
        return "";
    }

    std::string transcript;

    for (int i = 0; i < whisper_full_n_segments(ctx); ++i)
    {
        transcript += whisper_full_get_segment_text(ctx, i);
    }

    return transcript;
}

// load faces that are known

bool load_known_faces(const std::string& folder = "Faces")
{
    if (!fs::exists(folder))
    {
        fs::create_directories(folder);

        std::cout << "Created '" << folder << "' folder. Place your known face images inside (e.g., " << USER_NAME << ".jpg).\n";
    }

    for (const auto& entry : fs::directory_iterator(folder))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }

        std::string file_name = entry.path().filename().string();
        std::string extension = entry.path().extension().string();

        // convert extension to lowercase
        std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c) { return std::tolower(c); });

        if (extension != ".jpg" && extension != ".jpeg" && extension != ".png")
        {
            continue;
        }

        std::string name = entry.path().stem().string();

        try
        {
            cv::Mat face_img = cv::imread(entry.path().string());

            if (face_img.empty())
            {
                std::cerr << "LOADING FILE ERROR: " << file_name << "\n";
                continue;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "PRCSS ERROR: " << file_name << ": " << e.what() << "\n";
        }
    }

    return true;
}

// recognize hybrid speech
std::vector<float> capture_audio(int device_index, double phrase_time_limit);
std::string recognize_google_local(const std::vector<float>& audio_samples);
std::string normalize_text(const std::string& text);
std::string merge_transcripts(const std::string& whisper_text, const std::string& google_text);

std::string hybrid_recognize_speech()
{
    std::vector<float> audio = capture_audio(0, 10.0);

    if (audio.empty())
    {
        return "";
    }

    std::string whisper_text = transcribe_audio(ctx, audio);
    std::string google_text = recognize_google_local(audio);

    return merge_transcripts(whisper_text, google_text);
}

// memory func

json load_memory(void)
{
    if (!fs::exists(MEMORY_FILE))
    {
        return json::array();
    }

    std::ifstream file(MEMORY_FILE);

    if (!file.is_open())
    {
        return json::array();
    }

    try
    {
        json memory;
        file >> memory;

        return memory.is_array() ? memory : json::array();
    }
    catch(const std::exception& e)
    {
        return json::array();
    }
    
}

std::string trim(const std::string& input)
{
    const size_t start = input.find_first_not_of(" \t\n\r");

    if (start == std::string::npos)
    {
        return "";
    }

    const size_t end = input.find_last_not_of(" \t\n\r");
    
    return input.substr(start, end - start + 1);
}

void auto_update_memory(const char* user_input, const char* ai_reply)
{
    json memory = load_memory();
    // some ugly shit going on here! E
    auto now = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    std::tm local_time{};
    localtime_s(&local_time, &time_now);
    std::ostringstream timestamp;
    timestamp << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

    std::string cleaned_user_input = user_input ? trim(user_input) : "";
    std::string cleaned_ai_reply = ai_reply ? trim(ai_reply) : "";

    auto entry_exists = [](const json& data, const std::string& role, const std::string& content) -> bool
    {
        for (const auto& entry : data)
        {
            if (entry.is_object() && entry.value("role", "") == role && entry.value("content", "") == content)
            {
                return true;
            }
        }

        return false;
    };

    if (cleaned_user_input.size() > 5 && cleaned_user_input.size() < 300 && !entry_exists(memory, "user", cleaned_user_input))
    {
        memory.push_back({{"role", "user"}, {"content", cleaned_user_input}, {"time", timestamp.str()}});

        temp_memory_cache.push_back(cleaned_user_input);
    }
    
    if (cleaned_ai_reply.size() > 5 && cleaned_ai_reply.size() < 300 && !entry_exists(memory, "ai", cleaned_user_input))
    {
        memory.push_back({{"role", "ai"}, {"content", cleaned_ai_reply}, {"time", timestamp.str()}});

        temp_memory_cache.push_back(cleaned_ai_reply);
    }

    std::ofstream file(MEMORY_FILE);

    if (!file.is_open())
    {
        throw std::runtime_error("MEMORY SAVE ERR");
    }

    file << memory.dump(4);
}