// this system is based on ImDaGoatCreates' Cyn_AI python project
// some bot stuff is trash af so i gotta come up with some new ahh stuff

// too many includes
#include <curl.h>
#include <json.hpp>
#include <portaudio.h>
#include <baseapi.h>
#include <allheaders.h>
#include <random>
#include <filesystem>
#include <regex>
#include <string>
#include <chrono>
#include <ctime>
#include <objdetect.hpp>
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
#include <dnn.hpp>
#include <algorithm>
#include <dnn.h>
#include <frontal_face_detector.h>
#include <image_io.h>
#include <stdint.h>

// some namespaces and some global vars

using json = nlohmann::json;
namespace fs = std::filesystem;
const char* MICROPHONE_INDEX = "microphone_index.hpp";
const char* sr = "portaudio.h";
std::string MEMORY_FILE = "mrmy.json";
const char* whisper = "whisper.h";
cv::Mat frame;

struct PRSE_RESPN
{
    std::string dialogue;
    std::vector<std::string> actions;
};

// whisper context params

whisper_context_params ctx_params = whisper_context_default_params();

whisper_context* ctx = whisper_init_from_file_with_params("C:\\WDSYS\\api_sys\\char_mind\\whisper\\ggml-base.en.bin", ctx_params);

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
std::vector<dlib::matrix<float, 0, 1>> known_face_encodings;
std::vector<dlib::matrix<float, 0, 1>> face_encodings;
std::vector<std::string> known_face_names;
std::string current_speaker = "Unknown";
std::vector<std::string> temp_memory_cache;

json config = configread();

std::vector<std::string> WAKE_WORDS =  config.value("wake_words", std::vector<std::string>{});

std::vector<std::string> WAKE_PREFIXES =  config.value("wake_prefixes", std::vector<std::st ing>{"", "ok ", "hay ", "hey "});

std::string USER_NAME = config.at("user_name").get<std::string>();

// transcribe audio from the mic

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

bool load_known_faces(const std::string& folder = "C:\\WDSYS\\gui\\assets\\default")
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

// trim helper

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

// auto update memory, dunno if it should have a wait command or some crap like that

void auto_update_memory(const char* user_input, const char* ai_reply)
{
    json memory = load_memory();
    // some ugly stuff going on here! E
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
    
    if (cleaned_ai_reply.size() > 5 && cleaned_ai_reply.size() < 300 && !entry_exists(memory, "ai", cleaned_ai_reply))
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

// self explanatory

json load_system_prompt(const std::string& file_path = "personality.json")
{
    try
    {
        std::ifstream file(file_path);

        if (!file.is_open())
        {
            throw std::runtime_error("personality.json could not be loaded.\n");
        }

	json personality;
	file >> personality;

	return personality;

    }
    catch (const std::exception& e)
    {
        return "";
    }
}

std::string  get_chat_response(const char* user_input, const std::string& file_path = "personality.json")
{
    json system_prompt_content = load_system_prompt(file_path);

    if (user_input.empty())
    {
      return "";
    }

    json data = {
        {"model", "WDSYS_BotModel"},
        {"messages", json::array({
            {
                {"role", "system"},
                {"content", system_prompt_content}
            },
            {
                {"role", "user"},
                {"content", user_input}
            }
        })}
    };

    json headers = {
        {"Content-Type", "application/json"}
    };

    json response = requests.post(
        "http://localhost:1234/v1/chat/completions",
        headers,
        data.dump(4)
    );

    if (response.status_code == 200)
    {
        json response_json = response.json();
        return response_json["choices"][0]["message"]["content"].get<std::string>();
    }
    else
    {
        return "";
    }
}

cv::Mat capture_webcam_frame()
{
    cv::VideoCapture cap(1, cv::CAP_DSHOW);
    for (int i = 0; i < 35; i++)
    {
        bool ret = cap.read(frame);
        if (ret)
        {
            return frame;
        }
    }
    cap.release();
    return frame;
}

std::string image_to_text()
{
    tesseract::TessBaseAPI tessapi;

    if (tessapi.Init(nullptr, "eng") != 0)
    {
        throw std::runtime_error("TESSEACT IMAGE_TO_TEXT INIT ERR");
    }

    tessapi.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);

    tessapi.SetImage(frame.data, frame.cols, frame.rows, frame.channels(), static_cast<int>(frame.step));
    char* result = tessapi.GetUTF8Text();

    std::string text = result ? result : "";

    delete[] result;
    tessapi.End();

    return text;
}

std::string read_text_from_frame()
{
    if (frame.empty())
    {
        return "";
    }
    std::string text = image_to_text(frame);

    return text;
}

std::string detect_obj_from_frame()
{
  if (frame.empty())
  {
    return "OBJ DETECT NULL/TYPE:FRAMEEMPTY";
  }

  const char* yolo_model(bool verbose = false);
  bool names = results.name();

  std::vector<double> class_ids;

  for (const auto& detection : detections) {
    class_ids.push_back(detection.class_id);
  }

  std::vector<std::string> labels;

  for (int c : class_ids)
  {
    labels.push_back(names[c]);
  }

  if (!labels)
  {
    return "OBJ DETECT NULL/TYPE:NOTLABEL";
  }

  std::vector summary = {};

  for (label : labels)
  {
    summary[label] = summary.get(label, 0)++;
  }

  std::string result;

  for (const auto& [label, count] : summary)
  {
    if (!result.empty())
    {
      result += ", ";
    }

    result += std::to_string(count) + " ";
    result += (count == 1) ? label : label + "s";
  }

  return result;
}

const char* describe_faces_in_frame()
{
  if (frame == NULL)
  {
    return "I can't see anything.";
  }

  cv::cvtColor rgb_frame(frame, cv::COLOR_BGR2RGB);
  std::vector<std::string> face_encodings = std::vector<dlib::matrix<float, 0, 1>> face_encodings;

  if (!face_encoding)
  {
    return "No faces detected.";
  }

  std::vector summary = {};

  for (const auto& face_encoding : face_encodings)
  {
    bool face_matched = false;

    for (const auto& known_encoding : known_face_encodings)
    {
      double distance = dlib::length(known_encoding - face_encoding);

      if (distance <= 0.45)
      {
	face_matched = true;
	break;
      }
    }

    if (face_matched)
    {
      const char* name = known_face_names[matches.index(True)];
      summary[name] = summary.get(name, 0)++;
      if (name == USER_NAME)
      {
	current_speaker = USER_NAME;
      }
    }
    else
    {
      summary["Unknown"] = summary.get("Unknown", 0) + 1;
    }
  }

  std::string result = "I see ";

  bool first = true;

  for (const auto& [name, count] : summary)
  {
    if (!first)
    {
      result += ", ";
    }

    result += (count > 1) ? std::to_string(count) + " " + name : name;

    first = false;
  }

  return result + ".";
  // this func had so many for loops, i wish i could never do it again
}

const char* recognize_face_greeting()
{
  frame = capture_webcam_frame();
  if (frame == NULL)
  {
    return "CAMERA ERR";
  }

  cv::cvtColor rgb_frame(frame, cv::COLOR_BGR2RGB);

  std::vector<dlib::matrix<float, 0, 1>> face_encodings;

  for (const auto& face : face_rectangles)
  {
    auto shape = shape_predictor(rgb_frame, face);
    auto face_chip = dlib::extract_image_chip(rgb_frame, dlib::get_face_chip_details(shape));
    face_encodings.push_back(face_rec_model.compute_face_descriptor(face_chip));
  }

  if (!face_encodings)
  {
    return "I don't see anyone in particular";
  }

  std::vector<bool> matches;

  for (const auto& known_encoding : known_face_encodings)
  {
    double distance = dlib::length(known_encoding - face_encoding);

    matches.push_back(distance <= 0.45);

    if (std::find(matches.begin(), matches.end(), true) != matches.end())
    {
      std::vector<std::string> name = known_face_names[matches.index(True)];

      if (name == USER_NAME)
      {
	std::string current_speaker = USER_NAME;
      }

      return "Hey.. or whatever..";
    }
  }

  return "Who are you... exactly?";
}

double similarity_ratio(const std::string& a, const std::string& b)
{
  if (a.empty() && b.empty())
  {
    return 1.0;
  }

  const size_t m = a.size();
  const size_t n = b.size();

  std::vector<size_t> previous(n + 1);
  std::vector<size_t> current(n + 1);

  for (size_t j = 0; j <= n; ++j)
  {
    previous[j] = j;
  }

  for (size_t i = 1; i <= m; ++i)
  {
    current[0] = i;

    for (size_t j = 1; j <= n; ++j)
    {
      size_t cost = (a[i - 1] == b[j - 1]) ? 0 : 1;

      current[j] = std::min({previous[j] + 1, current[j - 1] + 1, previous[j - 1] + cost});
    }

    previous.swap(current);
  }

  size_t distance = previous[n];

  return 1.0 - static_cast<double>(distance) / std::max(m, n);
}

bool precise_wakeword_detected()
{
  std::vector<std::string> wake_phrases;

  for (const auto& prefix : WAKE_PREFIXES)
  {
    for (const auto& word : WAKE_WORDS)
    {
      wake_phrases.push_back(prefix + word);
    }
  }

  std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c)
  {
    return static_cast<char>(std::tolower(c));
  });

  auto start = text.find_first_not_of(" \t\n\r");
  auto end = text.find_last_not_of(" \t\n\r");

  text = (start == std::string::npos) ? "" : text.substr(start, end = start + 1);

  text.erase(std::remove_if(text.begin(), text.end(), [](unsigned char c)
  {
    return std::ispunct(c);
  }), text.end());

  for (const auto& phrase : wake_phrases)
  {
    double similarity = similarity_ratio(text, phrase);

    if (similarity > 0.85 || const auto& phrase : text)
    {
      return true;
    }
  }

  return false;
}

std::string check_for_depart()
{
  if (const auto& word : user_input == "bye" ||  "see you" || "cya" || "see ya" ||  "goodbye")
  {
    return "See ya";
  }
}

int main(void)
{
  config_read();
  load_known_faces();

  bool in_conversation = false;

  while (true)
  {
    if (!in_coversation)
    {
      std::string wake_text = hybrid_recognize_speech(double timeout = 0, double phrase_time_limit = 6);

      if (wake_text && precise_wakeword_detected())
      {
	in_conversation = true;
	if (current_speaker == "Unknown")
	{
	  current_speaker = USER_NAME;
	}

	printf(recognize_face_greeting());
      }

      continue;
    }

    user_input = hybrid_recognize_speech(double timeout = 8, double phrase_time_limit = 22.5);

    if (!user_input)
    {
      continue;
    }

    const char* user_text_lower = user_input.lower();

    if (check_for_farewell(user_text_lower))
    {
      in_conversation = false;
      current_speaker = "Unknown";
      continue;
    }
    else if 

  


       
  

