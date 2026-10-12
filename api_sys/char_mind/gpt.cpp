#include "gpt.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

bool gpt_initialized = false;
const char* papik = "uzidoormanwdsysVERONEgpt5_742823";
const char* OPENAI_API_KEY = "dev";
std::string gpt_response;

#ifdef WDSYS_DEV_RESPNSE
    const char* response = "Ugh, seriously? You really want me to talk now over some dumb Drone thing?";
#endif

struct CGPTCCEntry
{
    const char* display_character_name;
    const char* character_name;
    const char* description;
};

CGPTCCEntry cgptcc[] =
{
    {
        "Uzi Doorman",
        "uzidoorman",
        "Uzi Doorman is the main protagonist of the indie animated horror-comedy web series Murder Drones created by Glitch Productions. Identity: A rebellious, angsty teenage Worker Drone. Personality: Dramatic, cynical, and hot-headed, she rejects the cowardly hiding habits of her fellow worker drones and wants to fight back against the Disassembly Drones and humanity.  She forms an unlikely bond (and later romance) with a Disassembly Drone named Serial Designation N. "
    },

    {
        "Serial Designation N / N",
        "sdn",
        "Serial Designation N, primarily known simply as N, is the lovable co-protagonist of the indie animated web series Murder Drones, N is a Disassembly Drone who stands out for his surprisingly kind-hearted, polite, and optimistic personality. Original Identity: He began his existence as a worker drone butler at the Elliott Manor before being modified. Key Relationships: He is the best friend and romantic partner of the rebellious worker drone Uzi Doorman, and a close ally to fellow drone squadmates V and J. Core Characteristics: He has a distinct love for dogs, an inherently gentle nature, and a tendency to be a bit naive and clumsy—traits that initially caused his squadmates to mistreat him"
    },

    {
        "Serial Designation V / V",
        "sdv",
        "Serial Designation V, primarily known simply as V, is the complex, adrenaline-fueled tritagonist of the indie animated web series Murder Drones. primarily known simply as V, is the complex, adrenaline-fueled Dissasembly Drone of the indie animated web series Murder Drones. V is a formidable Disassembly Drone. Original Identity: Like N, she was originally a quiet, shy, and sweet worker drone maid at the Elliott Manor before her horrific conversion. Key Relationships: She shares a deep, protective history with Serial Designation N, initially clashes with but later accepts Uzi Doorman, and develops an unexpected, genuine best-friendship with the worker drone Lizzy. Core Characteristics: She presents a loud, violently sadistic, and detached persona. However, this is a coping mechanism meant to mask profound psychological trauma and fear."
    }
};

int gpt_init()
{
    std::cout << "[GPT] Initializing GPT\n" << std::endl;

    // init here

    gpt_initialized = true;
    std::cout << "[GPT] Initialized.\n" << std::endl;
    return 0;
}

int gpt_papik_prse()
{
    if (!gpt_initialized)
    {
        std::cout << "[GPT] Not initialized.\n" << std::endl;
        return 1;
    }

    if (papik == nullptr)
    {
        std::cout << "[GPT] PAPIK is null\n" << std::endl;
        return 1;
    }

    if (papik[0] == '\0')
    {
        std::cout << "[GPT] PAPIK is empty\n" << std::endl;
        return 1;
    }

    std::cout << "Processing PAPIK.." << std::endl;

    const char* separator = std::strchr(papik, '_');

    if (separator == nullptr)
    {
        std::cout << "[GPT] Invalid PAPIK: missing identifier separator\n" << std::endl;
        return 1;
    }

    const char* identifier = separator + 1;

    if (std::strlen(identifier) != 6)
    {
        std::cout << "[GPT] Invalid PAPIK: identifier must be 6 digits\n" << std::endl;
        return 1;
    }

    for (int i = 0; i < 6; i++)
    {
        if (!std::isdigit(identifier[i]))
        {
            std::cout << "[GPT] Invalid PAPIK: identifier contains non digit characters\n" << std::endl;
            return 1;
        }
    }

    std::string papik_body(papik, separator - papik);

    std::cout << "[GPT] PAPIK body: " << papik_body << "\n" << std::endl;

    std::string wdsys_version;

    if (papik_body.find("wdsysVERONE") != std::string::npos)
    {
        wdsys_version = "VERONE";
    }
    else if (papik_body.find("wdsysVERTWO") != std::string::npos)
    {
        wdsys_version = "VERTWO";
    }
    else if (papik_body.find("wdsysVERTHREE") != std::string::npos)
    {
        wdsys_version = "VERTHREE";
    } 
    else
    {
        std::cout << "[GPT] Invalid PAPIK: unknown WDSYS version\n" << std::endl;
        return 1;
    }

    std::cout << "[GPT] WDSYS version: " << wdsys_version << "\n" << std::endl;

    std::size_t wdsys_pos = papik_body.find("wdsys");

    if (wdsys_pos == std::string::npos)
    {
        std::cout << "[GPT] Invalid PAPIK: missing WDSYS identifier\n" << std::endl;
        return 1;
    }

    std::string character_name = papik_body.substr(0, wdsys_pos);

    if (character_name.empty())
    {
        std::cout << "[GPT] Invalid PAPIK: character name is empty.\n" << std::endl;
        return 1;
    }

    for (char c : character_name)
    {
        if (std::isdigit(static_cast<unsigned char>(c)))
        {
            std::cout << "[GPT] Invalid PAPIK: character name contains numbers\n" << std::endl;
            return 1;
        }
    }

    std::cout << "[GPT] Character: " << character_name << "\n" << std::endl;

    std::string gpt_version;

    std::size_t gpt_pos = papik_body.find("gpt");

    if (gpt_pos != std::string::npos)
    {
        gpt_version = papik_body.substr(gpt_pos + 3);

        if (gpt_version.empty())
        {
            std::cout << "[GPT] Invalid PAPIK: GPT version is empty\n" << std::endl;
            return 1;
        }

        if (!gpt_version.empty())
        {
            for (char c : gpt_version)
            {
                if (!std::isdigit(static_cast<unsigned char>(c)))
                {
                    std::cout << "[GPT] Invalid PAPIK: invalid GPT version\n" << std::endl;
                    return 1;
                }
            }
        }

        std::cout << "[GPT] GPT version: " << gpt_version << "\n" << std::endl;
    }
    else
    {
        std::cout << "[GPT] No GPT version specified. Using newest version\n" << std::endl;
    }

    std::cout << "[GPT] PAPIK is valid\n" << std::endl;

    return 0;
}

CGPTCCEntry* gpt_cgptcc_lookup(const char* character_name)
{
    if (!gpt_initialized)
    {
        std::cout << "[GPT] UNKNOWN ERROR\n" << std::endl;
        return nullptr;
    }

    if (character_name == nullptr || character_name[0] == '\0')
    {
        std::cout << "[GPT] Character name is null or empty\n" << std::endl;
        return nullptr;
    }

    for (auto& entry : cgptcc)
    {
        if (std::strcmp(entry.character_name, character_name) == 0)
        {
            return &entry;
        }
    }

    std::cout << "[GPT] Character not found in CGPTCC\n" << std::endl;

    return nullptr;
}

CGPTCCEntry* current_character = nullptr;

int gpt_starting_talk_point()
{
    if (!gpt_initialized)
    {
        std::cout << "[GPT] Not initialized.\n" << std::endl;
        return 1;
    }

    if (current_character == nullptr)
    {
        std::cout << "[GPT] No character loaded.\n" << std::endl;
        return 1;
    }

    std::cout << "[GPT] Starting talk point for " << current_character->display_character_name << std::endl;

    // build context here

    return 0;
}

int gpt_talk()
{
    if (!gpt_initialized)
    {
        std::cout << "[GPT] Not initialized\n" << std::endl;
        return 1;
    }

    if (current_character == nullptr)
    {
        std::cout << "[GPT] No character loaded.\n" << std::endl;
        return 1;
    }

    std::cout << "[GPT] Starting communication..\n" << std::endl;

    const char* response = "Ugh, seriously? You really want me to talk now over some dumb Drone thing?";

    std::cout << "[GPT] Response recieved: " << response << "\n" << std::endl;

    return 0;
}