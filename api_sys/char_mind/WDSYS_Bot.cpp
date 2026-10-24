// warnings
// difflib
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <portaudio.h>
#include <random>
#include <filesystem>
#include <regex>
#include <string>
// atexit
// yolo
// pytesseract
#include <chrono>
#include <ctime>
// face_regocntion
// whisper
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using json = nlohmann::json;

// load configs

int configread(void)
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
} // later

// global var
bool known_face_encodings = [];
bool known_face_names = [];
bool current_speaker = "Unknown";
bool temp_memory_cache = set();

bool whisper_model = whisper.load_model("large");

// load faces that are known

int load_known_faces(folder="Faces");
{
    if (!std::filesystem::exists(folder))
    {
        std::filesystem::create_directories(folder);

        std::cout << "Created '" << folder << "' folder. Place your known face images inside (e.g., " << USER_NAME << ".jpg).\n";
    }

    
}