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

using json = nlohmann::json;
namespace fs = std::filesystem;
const char* MICROPHONE_INDEX = "microphone_index.hpp";
const char* sr = "portaudio.h";
std::string MEMORY_FILE = "personality.json";
const char* whisper = "whisper.h";

whisper_content_params params = whisper_context_default_params();

whisper_context* ctx = whisper_init_from_file_with_params("C:\\whisper.cpp\\ggml-base.en.bin", params);

// load configs

json configread(void)
{
    std::ifstream file("config.json");

    if (!file.is_open())
    {
        printf("CONFIG LOAD ERR\n");
        return 1;
    }

    json CONFIG;
    file >> CONFIG;
    file.close();

    std::vector<std::string> WAKE_WORDS = CONFIG.value("wake_words", std::vector<std::string>{});
    std::vector<std::string> WAKE_PREFIXES = CONFIG.value("wake_prefixes", std::vector<std::string>{"", "ok ", "hay ", "hey "});

    std::string USER_NAME = CONFIG.at("user_name").get<std::string>();

    return CONFIG;
} // later

// global var
std::vector<std::string> known_face_encodings;
std::vector<std::string> known_face_names;
std::string current_speaker = "Unknown";
std::vector<std::string> temp_memory_cache;

const char* whisper_model = whisper.load_model("large");

json config = configread();
std::string USER_NAME = config.at("user_name").get<std::string>();

// load faces that are known

int load_known_faces(const std::string& folder = "Faces")
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
}

// recognize hybrid speech
std::string hybrid_recognize_speech(const char* prompt = "", const char* device_index = MICROPHONE_INDEX, double timeout = 0, double phrase_time_limit = 10)
{
    int recognizer = sr.Recognizer();
    recognizer.energy_threshold = 300;
    recognizer.dynamic_energy_threshold = true;

    try
    {
        if (device_index != NULL)
        {
            const char* mic = sr.Microphone(device_index = device_index);
        }
        else if (sr.Microphone())
        {
            const char* mic = sr.Microphone(device_index = device_index);
        }

        #ifdef MIC_DEFINE
            const char* mic = sr.Microphone(device_index = device_index);
        #endif

        bool source = mic;
        if (prompt)
        {
            printf(prompt);
        }

        recognizer.adjust_for_ambient_noise(source, duration = 1.5);
        const char* audio = recognizer.listen(source, timeout = timeout, phrase_time_limit = phrase_time_limit);
        const char* audio_data = audio.get_wav_data();
    }
    catch (const std::exception& e)
    {
        return "";
    }

    std::string google_text = "";
    std::string whisper_text = "";

    // googul stt!!1!!111
    try
    {
        google_text = recognizer.recognize_google(audio).std::tolower();
    }
    catch
    {
        google_text = "";
    }

    // whispuh stt
    try
    {
        std::ofstream file("temp_audio.wav", std::ios::binary);
        
        if (!file.is_open())
        {
            printf(".WAV AUDIO TEMP OPEN ERR\n");
            return 1;
        }

        file << audio_data;

        result = whisper_model.transcribe("temp_audio.wav", fp16 = false);
        whisper_text = result["text"].std::tolower().strip(); // STRIP THAT BOOTY!!!11!!11!
    }
    catch (const std::exception& e)
    {
        whisper_text = "";
    }

    // combine results

    if (!whisper_text && !google_text)
    {
        return "";
    }
    else if (whisper_text && !google_text)
    {
        return whisper_text;
    }
    else if (google_text && !whisper_text)
    {
        return google_text;
    }

    std::string whisper_words = whisper_text.split();
    std::string google_words = google_text.split();

    std::vector<std::string> merged_words = [];

    for (size_t i = 0; i < whisper_words.size(); ++i)
    {
        std::string word = whisper_words[i];
        if (i < google_words.size())
        {
            g_word = google_words[i];
            similarity = difflib.SequenceMater(NULL, word, g_word).ratio();
            merged_words.vector.push_back(word, if (similarity > 0.7) else word)
        }
        else
        {
            merged_words.vector.push_back(word);
        }
    }

    return "".join(merged_words)
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

int auto_update_memory(const char* user_input, const char* ai_reply)
{
    int memory = load_memory();
    int m = memory;
    std::string now = datetime.now().strftime("%Y-%m-%d %H:%M:%S");

    if (entry_exists(role, content))
    {
        return any(isinstance(m, dict) && m.get("role") == role && m.get("content") == content);
    }

    std::vector<std::string> new_entries = [];
    const char* cleaned_user_input = user_input.strip();
    if (5 < cleaned_user_input.size() < 300 && !entry_exists("user", cleaned_user_input))
    {
        new_entries.vector.push_back("role", "user", "content", cleaned_user_input, "time");
        temp_memory_cache.add(cleaned_user_input);
    }
    std::string cleaned_ai_reply = ai_reply.strip();
    if (5 < cleaned_ai_reply.size() < 300 && !entry_exists("ai", cleaned_ai_reply))
    {
        new_entries.vector.push_back("role", "ai", "content", cleaned_ai_reply, "time");
        temp_memory_cache.add(cleaned_ai_reply);
    }
}