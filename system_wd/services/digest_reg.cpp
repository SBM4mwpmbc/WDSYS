// Do not change ANYTHING in this script or else i will FUCKING SLIME YOU OUT

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#define WD_DIGEST_SUCCESS             0
#define WD_DIGEST_GENERAL_ERROR      -1
#define WD_DIGEST_INVALID_ITEM       -2
#define WD_DIGEST_INVALID_TYPE       -3
#define WD_DIGEST_INVALID_VALUE      -4
#define WD_DIGEST_NOT_FOUND          -5
#define WD_DIGEST_ALREADY_EXISTS     -6
#define WD_DIGEST_STORAGE_ERROR      -7
#define WD_DIGEST_NOT_INITIALIZED    -8
#define WD_DIGEST_FILE_ERROR         -9
#define WD_DIGEST_INVALID_COMMAND   -10

#define WD_DIGEST_FOOD    1
#define WD_DIGEST_DRINK   2
#define WD_DIGEST_SNACK   3

#define WD_REG_FILE "reg.dat"

struct DigestItem
{
    std::string name;

    int category;
    std::string category_code;

    std::string effect;
    std::string mood;

    int sugar;
    int energy;
    int hydration;
    int fullness;
};

struct DigestEffect
{
    std::string name;
    std::time_t expires;
};

struct DigestMood
{
    std::string name;
    std::time_t expires;
};

struct CustomDigestItem
{
    const char* name;
    int category;

    const char* effect;
    const char* mood;

    int sugar;
    int energy;
    int hydration;
    int fullness;
};

static std::vector<DigestItem> g_items;
static std::vector<DigestEffect> g_effects;
static std::vector<DigestMood> g_moods;

static bool g_initialized = false;
static bool g_active = false;

static std::string g_current_item;
static std::string g_current_effect;
static std::string g_current_mood;

static int g_current_sugar = 0;
static int g_current_energy = 0;
static int g_current_hydration = 0;
static int g_current_fullness = 0;

static const CustomDigestItem CUSTOM_ITEMS[] =
{
    {
        "Drone Burger",
        WD_DIGEST_FOOD,
        "Filling",
        "Satisfied",
        10, 30, 5, 80
    },

    {
        "Hot Drone",
        WD_DIGEST_FOOD,
        "Filling",
        "Happy",
        15, 30, 5, 80
    },

    {
        "bred",
        WD_DIGEST_FOOD,
        "Filling",
        "Happy",
        2, 60, 3, 90
    },

    {
        "Droney Eggy",
        WD_DIGEST_FOOD,
        "Very Filling",
        "Satisfied",
        10, 55, 10, 75
    },

    {
        "Droneza",
        WD_DIGEST_FOOD,
        "Very Filling",
        "Happy",
        20, 40, 7, 90
    },

    {
        "watuh",
        WD_DIGEST_DRINK,
        "Hydrating",
        "Refreshed",
        0, 5, 100, 10
    },

    {
        "Soda",
        WD_DIGEST_DRINK,
        "Refreshing",
        "Hyper",
        30, 50, 60, 30
    },

    {
        "Battery Acid",
        WD_DIGEST_DRINK,
        "Dizzy",
        "Hyper",
        60, 85, 45, 40
    },

    {
        "Candy",
        WD_DIGEST_SNACK,
        "Sugar Rush",
        "Hyper",
        90, 20, 0, 10
    },

    {
        "Chocolate Drone",
        WD_DIGEST_SNACK,
        "Filling",
        "Satisfied",
        70, 30, 0, 10
    },

    {
        "Pop Drone",
        WD_DIGEST_SNACK,
        "Filling",
        "Hyper",
        75, 30, 0, 15
    },

    {
        "Batteries Non-Acid",
        WD_DIGEST_SNACK,
        "Filling",
        "Satisfied",
        50, 40, 0, 40
    },

    {
        "Batteries",
        WD_DIGEST_SNACK,
        "Sugar Rush",
        "Satisfied",
        60, 50, 20, 45
    }
};

static std::string trim(const std::string& text)
{
    size_t start = text.find_first_not_of(" \t\r\n");

    if (start == std::string::npos)
    {
        return "";
    }

    size_t end = text.find_last_not_of(" \t\r\n");

    return text.substr(start, end - start + 1);
}

static bool starts_with(const std::string& text, const std::string& prefix)
{
    return text.compare(0, prefix.length(), prefix) == 0;
}

static std::string category_code(int category)
{
    switch (category)
    {
        case WD_DIGEST_FOOD:
            return "FD";
        
        case WD_DIGEST_DRINK:
            return "DR";
        
        case WD_DIGEST_SNACK:
            return "SN";

        default:
            return "UK";
    }
}

static bool valid_category(int category)
{
    return category == WD_DIGEST_FOOD || category == WD_DIGEST_DRINK || category == WD_DIGEST_SNACK;
}

static bool valid_value(int value)
{
    return value >= 0 && value <= 100;
}

static DigestItem* find_item(const char* name)
{
    if (name == nullptr)
    {
        return nullptr;
    }

    for (auto& item : g_items)
    {
        if (item.name == name)
        {
            return &item;
        }
    }

    return nullptr;
}

static const DigestItem* find_item_const(const char* name)
{
    if (name == nullptr)
    {
        return nullptr;
    }

    for (const auto& item : g_items)
    {
        if (item.name == name)
        {
            return &item;
        }
    }

    return nullptr;
}

static int copy_string(const std::string& source, char* buffer, unsigned long buffer_size)
{
    if (buffer == nullptr || buffer_size == 0)
    {
        return WD_DIGEST_INVALID_VALUE;
    }

    if (source.size() + 1 > buffer_size)
    {
        buffer[0] = '\0';
        return WD_DIGEST_STORAGE_ERROR;
    }

    std::memcpy(buffer, source.c_str(), source.size() + 1);

    return WD_DIGEST_SUCCESS;
}

static int copy_int(int value, char* buffer, unsigned long buffer_size)
{
    if (buffer == nullptr || buffer_size == 0)
    {
        return WD_DIGEST_INVALID_VALUE;
    }

    int written = std::snprintf(buffer, buffer_size, "%d", value);

    if (written < 0)
    {
        buffer[0] = '\0';
        return WD_DIGEST_GENERAL_ERROR;
    }

    if (static_cast<unsigned long>(written) >= buffer_size)
    {
        buffer[0] = '\0';
        return WD_DIGEST_STORAGE_ERROR;
    }

    return WD_DIGEST_SUCCESS;
}

static int load_custom_items(void)
{
    const unsigned long count = sizeof(CUSTOM_ITEMS) / sizeof(CUSTOM_ITEMS[0]);

    for (unsigned long i = 0; i < count; ++i)
    {
        const CustomDigestItem& custom = CUSTOM_ITEMS[i];

        if (custom.name == nullptr || custom.name[0] == '\0')
        {
            return WD_DIGEST_INVALID_ITEM;
        }

        if (!valid_category(custom.category))
        {
            return WD_DIGEST_INVALID_TYPE;
        }

        if (!valid_value(custom.sugar) || !valid_value(custom.energy) || !valid_value(custom.hydration) || !valid_value(custom.fullness))
        {
            return WD_DIGEST_INVALID_VALUE;
        }

        if (find_item(custom.name) != nullptr)
        {
            return WD_DIGEST_ALREADY_EXISTS;
        }

        DigestItem item;

        item.name = custom.name;
        item.category = custom.category;
        item.category_code = category_code(custom.category);

        item.effect = custom.effect != nullptr ? custom.effect : "No special effect";

        item.mood = custom.mood != nullptr ? custom.mood : "Neutral";

        item.sugar = custom.sugar;
        item.energy = custom.energy;
        item.hydration = custom.hydration;
        item.fullness = custom.fullness;

        g_items.push_back(item);
    }

    return WD_DIGEST_SUCCESS;
}

static std::string effect_entry_name(const std::string& effect)
{
    return "digest.effect/" + effect + "/affects_mood";
}

static std::string mood_entry_name(const std::string& mood)
{
    return "digest.mood/" + mood + "/character";
}

static void remove_expired_effects(void)
{
    std::time_t now = std::time(nullptr);

    g_effects.erase(std::remove_if(g_effects.begin(), g_effects.end(), [&](const DigestEffect& effect){ return effect.expires <= now; }), g_effects.end());
}

static void remove_expired_moods(void)
{
    std::time_t now = std::time(nullptr);

    g_moods.erase(std::remove_if(g_moods.begin(), g_moods.end(), [&](const DigestMood& mood){ return mood.expires <= now; }), g_moods.end());
}

static void check_expiration(void)
{
    const std::time_t now = std::time(nullptr);

    g_current_effect = "No special effect";
    g_current_mood = "Neutral";

    for (const DigestEffect& effect : g_effects)
    {
        if (effect.expires > now)
        {
            g_current_effect = effect.name;
        }
    }

    for (const DigestMood& mood : g_moods)
    {
        if (mood.expires > now)
        {
            g_current_mood = mood.name;
        }
    }
}

static int save_registry(void)
{
    std::ifstream input(WD_REG_FILE);

    if (!input.is_open())
    {
        return WD_DIGEST_FILE_ERROR;
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(input, line))
    {
        lines.push_back(line);
    }

    std::vector<std::string> preserved;
    bool skipping_digest_registry = false;

    for (const std::string& current_line : lines)
    {
        if (current_line.rfind("[ \"DIGEST EFFECT - ", 0) == 0 || current_line.rfind("[ \"DIGEST MOOD - ", 0) == 0)
        {
            skipping_digest_registry = true;
            continue;
        }

        if (skipping_digest_registry)
        {
            if (current_line.empty())
            {
                skipping_digest_registry = false;
            }

            continue;
        }

        preserved.push_back(current_line);
    }

    std::ofstream file(WD_REG_FILE, std::ios::app);

    if (!file.is_open())
    {
        return WD_DIGEST_FILE_ERROR;
    }

    for (const std::string& preserved_line : preserved)
    {
        file << preserved_line << "\n";
    }

    file << "\n";

    const std::time_t now = std::time(nullptr);

    for (const DigestEffect& effect : g_effects)
    {
        const char* status = effect.expires <= now ? "Expired" : "Active";

        file << "[ \"DIGEST EFFECT - " << effect.name << "\"\n";
        file << "\tENTRYNAME=" << effect_entry_name(effect.name) << "\n";
        file << "\tVALUEDATA=\"" << effect.name << "\":EXPIRES=" << static_cast<long long>(effect.expires) << ":STATUS=" << status << ":\n";
        file << ":APPLY: ]\n\n";
    }

    for (const DigestMood& mood : g_moods)
    {
        const char* status = mood.expires <= now ? "Expired" : "Active";

        file << "[ \"DIGEST MOOD - " << mood.name << "\"\n";
        file << "\tENTRYNAME=" << mood_entry_name(mood.name) << "\n";
        file << "\tVALUEDATA=\"" << mood.name << "\":EXPIRES=" << static_cast<long long>(mood.expires) << ":STATUS=" << status << ":\n";
        file << ":APPLY: ]\n\n";
    }

    return WD_DIGEST_SUCCESS;
}

int wd_digest_init(void)
{
    if (g_initialized)
    {
        return WD_DIGEST_SUCCESS;
    }

    g_items.clear();
    g_effects.clear();
    g_moods.clear();

    g_current_item.clear();
    g_current_effect = "No special effects";
    g_current_mood = "Neutral";

    g_current_sugar = 0;
    g_current_energy = 0;
    g_current_hydration = 0;
    g_current_fullness = 0;

    g_active = false;

    int result = load_custom_items();

    if (result != WD_DIGEST_SUCCESS)
    {
        g_items.clear();
        return result;
    }

    g_initialized = true;

    return WD_DIGEST_SUCCESS;
}

void wd_digest_shutdown(void)
{
    if (!g_initialized)
    {
        return;
    }

    save_registry();

    g_items.clear();
    g_effects.clear();
    g_moods.clear();

    g_current_item.clear();
    g_current_effect.clear();
    g_current_mood.clear();

    g_current_sugar = 0;
    g_current_energy = 0;
    g_current_hydration = 0;
    g_current_fullness = 0;

    g_active = false;
    g_initialized = false;
}

// register item api

int wd_digest_register_item(
    const char* name,
    int category
)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    if (name == nullptr || name[0] == '\0')
    {
        return WD_DIGEST_INVALID_ITEM;
    }

    if (!valid_category(category))
    {
        return WD_DIGEST_INVALID_TYPE;
    }

    if (find_item(name) != nullptr)
    {
        return WD_DIGEST_ALREADY_EXISTS;
    }

    DigestItem item;

    item.name = name;
    item.category = category;
    item.category_code = category_code(category);

    item.effect = "No special effect";
    item.mood = "Neutral";

    item.sugar = 0;
    item.energy = 0;
    item.hydration = 0;
    item.fullness = 0;

    g_items.push_back(item);

    return WD_DIGEST_SUCCESS;
}

int wd_digest_item_exists(const char* name)
{
    if (!g_initialized || name == nullptr)
    {
        return 0;
    }

    return find_item(name) != nullptr ? 1 : 0;
}

int wd_digest_remove_item(const char* name)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    if (name == nullptr || name[0] == '\0')
    {
        return WD_DIGEST_INVALID_ITEM;
    }

    auto iterator = std::find_if(g_items.begin(), g_items.end(), [&](const DigestItem& item){ return item.name == name; });

    if (iterator == g_items.end())
    {
        return WD_DIGEST_NOT_FOUND;
    }

    g_items.erase(iterator);

    return WD_DIGEST_SUCCESS;
}

int wd_digest_consume(const char* name)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    const DigestItem* item = find_item_const(name);

    if (item == nullptr)
    {
        return WD_DIGEST_NOT_FOUND;
    }

    // nah cuz imagine fucking breathing in the big 26

    g_current_item = item->name;

    g_current_sugar += item->sugar;
    g_current_energy += item->energy;
    g_current_hydration += item->hydration;
    g_current_fullness += item->fullness;

    if (g_current_sugar > 100)
    {
        g_current_sugar = 100;
    }

    if (g_current_energy > 100)
    {
        g_current_energy = 100;
    }

    if (g_current_hydration > 100)
    {
        g_current_hydration = 100;
    }

    if (g_current_fullness > 100)
    {
        g_current_fullness = 100;
    }

    std::time_t now = std::time(nullptr);

    DigestEffect effect;

    effect.name = item->effect;
    effect.expires = now + 300;

    g_effects.push_back(effect);

    g_active = true;

    check_expiration();

    save_registry();

    return WD_DIGEST_SUCCESS;
}

int wd_digest_clear_state(void)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    g_current_item.clear();

    g_current_effect = "No special effect";
    g_current_mood = "Neutral";

    g_current_sugar = 0;
    g_current_energy = 0;
    g_current_hydration = 0;
    g_current_fullness = 0;

    g_active = false;

    g_effects.clear();
    g_moods.clear();

    save_registry();

    return WD_DIGEST_SUCCESS;
}

int wd_digest_is_active(void)
{
    if (!g_initialized)
    {
        return 0;
    }

    check_expiration();

    return g_active ? 1 : 0;
}

int wd_digest_get_category(const char* name)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    const DigestItem* item = find_item_const(name);

    if (item == nullptr)
    {
        return WD_DIGEST_NOT_FOUND;
    }

    return item->category;
}

int wd_digest_get_effect(const char* name, char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    const DigestItem* item = find_item_const(name);

    if (item == nullptr)
    {
        return WD_DIGEST_NOT_FOUND;
    }

    return copy_string(item->effect, buffer, buffer_size);
}

int wd_digest_get_mood(const char* name, char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    const DigestItem* item = find_item_const(name);

    if (item == nullptr)
    {
        return WD_DIGEST_NOT_FOUND;
    }

    return copy_string(item->mood, buffer, buffer_size);
}

int wd_digest_get_sugar(const char* name, char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    const DigestItem* item = find_item_const(name);

    if (item == nullptr)
    {
        return WD_DIGEST_NOT_FOUND;
    }

    return copy_int(item->sugar, buffer, buffer_size);
}

int wd_digest_get_energy(const char* name, char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    const DigestItem* item = find_item_const(name);

    if (item == nullptr)
    {
        return WD_DIGEST_NOT_FOUND;
    }

    return copy_int(item->energy, buffer, buffer_size);
}

int wd_digest_get_hydration(const char* name, char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    const DigestItem* item = find_item_const(name);

    if (item == nullptr)
    {
        return WD_DIGEST_NOT_FOUND;
    }

    return copy_int(item->hydration, buffer, buffer_size);
}

int wd_digest_get_fullness(const char* name, char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    const DigestItem* item = find_item_const(name);

    if (item == nullptr)
    {
        return WD_DIGEST_NOT_FOUND;
    }

    return copy_int(item->fullness, buffer, buffer_size);
}

// WAY FUCKING longer than i expected

int wd_digest_get_current_item(char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    return copy_string(g_current_item, buffer, buffer_size);
}

int wd_digest_get_current_effect(char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    check_expiration();

    return copy_string(g_current_effect, buffer, buffer_size);
}

int wd_digest_get_current_mood(char* buffer, unsigned long buffer_size
)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    check_expiration();

    return copy_string(g_current_mood, buffer, buffer_size);
}

int wd_digest_get_current_sugar(char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    return copy_int(g_current_sugar, buffer, buffer_size);
}

int wd_digest_get_current_energy(char* buffer, unsigned long buffer_size
)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    return copy_int(g_current_energy, buffer, buffer_size);
}

int wd_digest_get_current_hydration(char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    return copy_int(g_current_hydration, buffer, buffer_size);
}

int wd_digest_get_current_fullness(char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    return copy_int(g_current_fullness, buffer, buffer_size);
}

int wd_digest_reset_effects(void)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    g_effects.clear();
    g_moods.clear();

    g_current_effect = "No special effect";
    g_current_mood = "Neutral";

    save_registry();

    return WD_DIGEST_SUCCESS;
}

static void print_effects(void)
{
    check_expiration();

    printf("\n[DIGEST] Active effects: %zu\n", g_effects.size());

    if (g_effects.empty())
    {
        printf("None\n");
        return;
    }

    std::time_t now = std::time(nullptr);

    for (const auto& effect : g_effects)
    {
        long long remaining = static_cast<long long>(effect.expires - now);

        if (remaining < 0)
        {
            remaining = 0;
        }

        printf("%s - %11lld seconds remaining\n", effect.name.c_str(), remaining);
    }
}

static void print_moods(void)
{
    check_expiration();

    printf("\n[DIGEST] Active moods: %zu\n", g_moods.size());

    if (g_moods.empty())
    {
        printf("None\n");
        return;
    }

    std::time_t now = std::time(nullptr);

    for (const auto& mood : g_moods)
    {
        long long remaining = static_cast<long long>(mood.expires - now);

        if (remaining < 0)
        {
            remaining = 0;
        }

        printf("%s - %11lld seconds remaining\n", mood.name.c_str(), remaining);
    }
}

int wd_digest_get_state_summary(char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    check_expiration();

    int written = std::snprintf(buffer, buffer_size, "ITEM=%s | ", "EFFECT=%s | ", "MOOD=%s | ", "SUGAR=%d | ", "ENERGY=%d | ", "HYDRATION=%d | ", "FULLNESS=%d | ", g_current_item.c_str(), g_current_effect.c_str(), g_current_mood.c_str(), g_current_sugar, g_current_energy, g_current_hydration, g_current_fullness);

    if (written < 0)
    {
        if (buffer != nullptr && buffer_size != 0)buffer[0] = '\0';
        {
            return WD_DIGEST_GENERAL_ERROR;
        }
    }

    if (static_cast<unsigned long>(written) >= buffer_size)
    {
        if (buffer != nullptr && buffer_size != 0)buffer[0] = '\0';
        {
            return WD_DIGEST_STORAGE_ERROR;
        }
    }

    return WD_DIGEST_SUCCESS;
}

int wd_digest_get_character_message(char* buffer, unsigned long buffer_size)
{
    if (!g_initialized)
    {
        return WD_DIGEST_NOT_INITIALIZED;
    }

    check_expiration();

    std::string message;

    if (!g_active)
    {
        message = "I have not consumed anything recently.";
    }
    else if (g_current_mood == "Hyper")
    {
        message = "I'm really hyper!";
    }
    else if (g_current_mood == "Happy")
    {
        message = "I feel pretty good!";
    }
    else if (g_current_mood == "Tired")
    {
        message = "I'm feeling tired.";
    }
    else if (g_current_mood == "Sick")
    {
        message = "I don't feel very good.";
    }
    else
    {
        message = "I consumed " + g_current_item + ".";
    }

    return copy_string(message, buffer, buffer_size);
}

static void print_help(void)
{
    printf("\n");
    printf("DIGEST_REG CMDs\n");
    printf("HELP - Show this help\n");
    printf("STATUS - Show current digestion state\n");
    printf("LIST - List digest items\n");
    printf("CONSUME <name> - Consume an item\n");
    printf("GET <name> - Show item information\n");
    printf("EFFECTS - Show active effects\n");
    printf("MOODS - Show active moods\n");
    printf("CHECK - Check effect/mood expiration\n");
    printf("RESET - Reset active effects and moods\n");
    printf("CLEAR - Clear digestion state\n");
    printf("SAVE - Save registry\n");
    printf("EXIT - Shut down digest_reg\n");
    printf("\n");
}

static void print_items(void)
{
    printf("\n[DIGEST] Registered items: %zu\n", g_items.size());

    for (const auto& item : g_items)
    {
        printf(" %s [%s] | Effect=%s | Mood=%s | Sugar=%d | Energy=%d | Hydration=%d | Fullness=%d\n", item.name.c_str(), item.category_code.c_str(), item.effect.c_str(), item.mood.c_str(), item.sugar, item.energy, item.hydration, item.fullness);
    }
}

static void print_item(const std::string& name)
{
    const DigestItem* item = find_item_const(name.c_str());

    if (item == nullptr)
    {
        printf("[DIGEST] Item not found.\n");
        return;
    }

    printf("\n");
    printf("NAME - %s\n", item->name.c_str());
    printf("CATEGORY - %s\n", item->category_code.c_str());
    printf("EFFECT: - %s\n", item->effect.c_str());
    printf("MOOD - %s\n", item->mood.c_str());
    printf("SUGAR - %d\n", item->sugar);
    printf("ENERGY - %d\n", item->energy);
    printf("HYDRATION - %d\n", item->hydration);
    printf("FULLNESS - %d\n", item->fullness);
}

static void print_status(void)
{
    check_expiration();

    printf("\n");
    printf("[DIGEST] STATUS\n");
    printf("Active - %s\n", g_active ? "YES" : "NO");
    printf("Item - %d\n", g_current_item.empty(), g_current_item.empty() ? "None" : g_current_item.c_str());
    printf("Effect - %s\n", g_current_effect.c_str());
    printf("Mood - %s\n", g_current_mood.c_str());
    printf("Sugar - %d\n", g_current_sugar);
    printf("Energy - %d\n", g_current_energy);
    printf("Hydration - %d\n", g_current_hydration);
    printf("Fullness - %d\n", g_current_fullness);
}

static void process_command(const std::string& command)
{
    std::string input = trim(command);

    if (input.empty())
    {
        return;
    }
    else if (input == "HELP")
    {
        print_help();
        return;
    }
    else if (input == "STATUS")
    {
        print_status();
        return;
    }
    else if (input == "LIST")
    {
        print_items();
        return;
    }
    else if (input == "EFFECTS")
    {
        print_effects();
        return;
    }
    else if (input == "MOODS")
    {
        print_moods();
        return;
    }
    else if (input == "CHECK")
    {
        check_expiration();
        save_registry();

        printf("[DIGEST] Expiration check complete.\n");
        return;
    }
    else if (input == "RESET")
    {
        wd_digest_reset_effects();

        printf("[DIGEST] Effects and moods reset.\n");
        return;
    }
    else if (input == "CLEAR")
    {
        wd_digest_clear_state();

        printf("[DIGEST] State cleared.\n");
        return;
    }
    else if (input == "SAVE")
    {
        int result = save_registry();

        if (result == WD_DIGEST_SUCCESS)
        {
            printf("[DIGEST] Registry saved successfully!\n");
        }
        else
        {
            printf("[DIGEST] Registry failed to save.\n");
        }

        return;
    }
    else if (starts_with(input, "CONSUME "))
    {
        std::string name = trim(input.substr(8));

        int result = wd_digest_consume(name.c_str());

        if (result == WD_DIGEST_SUCCESS)
        {
            printf("[DIGEST] Consumed: %s\n", name.c_str());
        }
        else
        {
            printf("[DIGEST] Failed to consume item. Code: %d\n", result);
        }
        
        return;
    }
    else if (starts_with(input, "GET "))
    {
        std::string name = trim(input.substr(4));

        print_item(name);
        return;
    }
    else
    {
        printf("[DIGEST] Unknown command: %s\n", input.c_str());
    }
}

int main(void)
{
    printf("\n");
    printf("WDSYS Digestive Registry Manager, V1\n");

    int result = wd_digest_init();

    if (result != WD_DIGEST_SUCCESS)
    {
        printf("[DIGEST] Initialization failed. Code: %d\n", result);

        return 1;
    }

    printf("[DIGEST] Digestive Registry initialized.\n");
    printf("[DIGEST] %zu items loaded.\n", g_items.size());
    printf("[DIGEST] Type HELP for CMDs.\n\n");

    std::string command;

    while (g_initialized)
    {
        check_expiration();

        printf("DIGEST> ");

        if (!std::getline(std::cin, command))
        {
            break;
        }

        if (command == "EXIT")
        {
            break;
        }

        process_command(command);
    }

    printf("[DIGEST] Saving registry...\n");

    save_registry();

    wd_digest_shutdown();

    printf("[DIGEST] Shutting down, what the fuck do you expect?\n");

    return 0;
}

// What a fucking hellhole.
