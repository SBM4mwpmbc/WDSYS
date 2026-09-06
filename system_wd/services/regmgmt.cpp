#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define WD_REG_SUCCESS             0
#define WD_REG_GENERAL_ERROR      -1
#define WD_REG_INVALID_KEY        -2
#define WD_REG_NOT_FOUND          -3
#define WD_REG_ALREADY_EXISTS     -4
#define WD_REG_FILE_ERROR         -5
#define WD_REG_NOT_INITIALIZED    -6
#define WD_REG_INVALID_COMMAND    -7

#define WD_REG_FILE "reg.dat"

struct WDRegistryEntry
{
    std::string name;
    std::string entryname;
    std::string valuedata;
    std::string function;
    std::string call;
};

static std::vector<WDRegistryEntry> g_registry;
static bool g_reg_initialized = false;

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

static bool starts_with(
    const std::string& text,
    const std::string& prefix
)
{
    return text.compare(0, prefix.length(), prefix) == 0;
}

static std::string remove_prefix(
    const std::string& text,
    const std::string& prefix
)
{
    if (!starts_with(text, prefix))
    {
        return text;
    }

    return text.substr(prefix.length());
}

static std::string remove_surrounding_quotes(
    const std::string& text
)
{
    std::string value = trim(text);

    if (value.length() >= 2 && value.front() == '"' && value.back() == '"')
    {
        return value.substr(1, value.length() - 2);
    }

    return value;
}

static int wd_reg_find(
    const std::string& entryname
)
{
    for (size_t i = 0; i < g_registry.size(); ++i)
    {
        if (g_registry[i].entryname == entryname)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

int wd_reg_init(void)
{
    if (g_reg_initialized)
    {
        return WD_REG_SUCCESS;
    }

    std::ifstream file(WD_REG_FILE);

    if (!file.is_open())
    {
        return WD_REG_FILE_ERROR;
    }

    std::string line;

    WDRegistryEntry current;
    bool inside_entry = false;

    while (std::getline(file, line))
    {
        std::string trimmed = trim(line);

        if (trimmed.empty())
        {
            continue;
        }

        if (trimmed == "reg.dat")
        {
            continue;
        }

        if (starts_with(trimmed, "["))
        {
            current = WDRegistryEntry();
            inside_entry = true;

            size_t quote_start = trimmed.find('"');
            size_t quote_end = trimmed.find('"', quote_start + 1);

            if (quote_start != std::string::npos && quote_end != std::string::npos)
            {
                current.name = trimmed.substr(quote_start + 1, quote_end - quote_start - 1);
            }

            continue;
        }

        if (!inside_entry)
        {
            continue;
        }

        if (starts_with(trimmed, "ENTRYNAME="))
        {
            current.entryname = trim(remove_prefix(trimmed, "ENTRYNAME="));

            continue;
        }

        if (starts_with(trimmed, "VALUEDATA="))
        {
            std::string data = trim(remove_prefix(trimmed, "VALUEDATA="));

            size_t first_quote = data.find('"');

            if (first_quote != std::string::npos)
            {
                size_t second_quote = data.find('"', first_quote + 1);

                if (second_quote != std::string::npos)
                {
                    current.valuedata = data.substr(first_quote + 1, second_quote - first_quote - 1);

                    std::string function_part = data.substr(second_quote + 1);

                    function_part = trim(function_part);

                    if (function_part.front() == ':')
                    {
                        function_part.erase(0, 1);
                    }

                    if (!function_part.empty() && function_part.back() == ':')
                    {
                        function_part.pop_back();
                    }

                    current.function = trim(function_part);

                }

                continue;
            }
        }

        if (starts_with(trimmed, ":CALL:"))
        {
            std::string call_part = trimmed.substr(strlen(":CALL:"));

            call_part = trim(call_part);

            if (!call_part.empty() && call_part.back() == ']')
            {
                call_part.pop_back();
            }

            current.call = trim(call_part);

            if (!current.entryname.empty())
            {
                g_registry.push_back(current);
            }

            current = WDRegistryEntry();
            inside_entry = false;

            continue;
        }
    }

    g_reg_initialized = true;

    return WD_REG_SUCCESS;
}

int wd_reg_set(
    const char* name,
    const char* entryname,
    const char* valuedata,
    const char* function,
    const char* call
)
{
    if (!g_reg_initialized)
    {
        return WD_REG_NOT_INITIALIZED;
    }

    if (name == nullptr || entryname == nullptr || valuedata == nullptr || function == nullptr || call == nullptr)
    {
        return WD_REG_INVALID_KEY;
    }

    if (name[0] == '\0' || entryname[0] == '\0')
    {
        return WD_REG_INVALID_KEY;
    }

    int  index = wd_reg_find(entryname);

    WDRegistryEntry entry;

    entry.name = name;
    entry.entryname = entryname;
    entry.valuedata = valuedata;
    entry.function = function;
    entry.call = call;

    if (index >= 0)
    {
        g_registry[index] = entry;

        return WD_REG_SUCCESS;
    }

    g_registry.push_back(entry);

    return WD_REG_SUCCESS;
}

int wd_reg_get(
    const char* entryname,
    WDRegistryEntry& output
)
{
    if (!g_reg_initialized)
    {
        return WD_REG_NOT_INITIALIZED;
    }

    if (entryname == nullptr || entryname[0] == '\0')
    {
        return WD_REG_INVALID_KEY;
    }

    int index = wd_reg_find(entryname);

    if (index < 0)
    {
        return WD_REG_NOT_FOUND;
    }

    output = g_registry[index];

    return WD_REG_SUCCESS;
}

int wd_reg_remove(
    const char* entryname
)
{
    if (!g_reg_initialized)
    {
        return WD_REG_NOT_INITIALIZED;
    }

    if (entryname == nullptr || entryname[0] == '\0')
    {
        return WD_REG_INVALID_KEY;
    }

    int index = wd_reg_find(entryname);

    g_registry.erase(g_registry.begin() + index);

    return WD_REG_SUCCESS;
}

int wd_reg_save(void)
{
    if (!g_reg_initialized)
    {
        return WD_REG_NOT_INITIALIZED;
    }

    std::ofstream file(WD_REG_FILE, std::ios::trunc);

    if (!file.is_open())
    {
        return WD_REG_FILE_ERROR;
    }

    file << "reg.dat\n\n";

    for (const WDRegistryEntry& entry : g_registry)
    {
        file << "[ \"" << entry.name << "\"\n";

        file << "\tENTRYNAME=" << entry.entryname << "\n";

        file << "\tVALUEDATA=\"" << entry.valuedata << "\":" << entry.function << ":\n";

        /* CALL AND ] stay on the SAME FUCKING LINE */

        file << ":" << entry.call << ": ]\n\n";
    }

    return WD_REG_SUCCESS;
}

static void wd_reg_list(void)
{
    if (g_registry.empty())
    {
        printf("[REGMGMT] Registry is empty.\n");
        return;
    }

    printf("\n");
    printf("WDSYS Registry\n");

    for (size_t i = 0; i < g_registry.size(); ++i)
    {
        printf("\n");
        printf("[%zu] %s\n", i + 1, g_registry[i].name.c_str());
        printf("ENTRYNAME: %s\n", g_registry[i].entryname.c_str());
        printf("VALUE: %s\n", g_registry[i].valuedata.c_str());
        printf("FUNCTION: %s\n", g_registry[i].function.c_str());
        printf("CALL: %s\n", g_registry[i].call.c_str());
    }
}

static void wd_reg_status(void)
{
    printf("\n");
    printf("[REGMGMT] Status\n");
    printf("[REGMGMT] Initialized : %s\n", g_reg_initialized ? "Yes" : "No");
    printf("[REGMGMT] Entries: %zu\n", g_registry.size());
    printf("[REGMGMT] File: %s\n", WD_REG_FILE);
    printf("\n");
}

static void wd_reg_help(void)
{
    printf("\n");
    printf("REGMGMT HELP\n");
    printf("SET - Create or modify a registry\n");
    printf("GET - Retrieve a registry\n");
    printf("REMOVE - Remove a registry\n");
    printf("LIST - List all registries\n");
    printf("SAVE - Save registry to reg.dat\n");
    printf("RELOAD - Reload registry from reg.dat\n");
    printf("HELP - Display this help menu\n");
    printf("EXIT - Save and shutdown REGMGMT\n");
}

static void wd_reg_print_entry(
    const WDRegistryEntry& entry
)
{
    printf("\n");
    printf("[ \"%s\"\n", entry.name.c_str());
    printf("\tENTRYNAME=%s\n", entry.entryname.c_str());
    printf("\tVALUEDATA=\"%s\":%s:\n", entry.valuedata.c_str(), entry.function.c_str());
    printf(":%s: ]\n\n", entry.call.c_str());
}

static void wd_reg_command_set(void)
{
    std::string name;
    std::string entryname;
    std::string valuedata;
    std::string function;
    std::string call;

    printf("Registry name: ");
    std::getline(std::cin, name);

    printf("Entry name: ");
    std::getline(std::cin, entryname);

    printf("Value data: ");
    std::getline(std::cin, valuedata);

    printf("Function: ");
    std::getline(std::cin, function);

    printf("Call: ");
    std::getline(std::cin, call);

    int result = wd_reg_set(name.c_str(), entryname.c_str(), valuedata.c_str(), function.c_str(), call.c_str());

    if (result == WD_REG_SUCCESS)
    {
        printf("[REGMGMT] Registry updated.\n");

        result = wd_reg_save();

        if (result != WD_REG_SUCCESS)
        {
            printf("[REGMGMT] WARNING: Registry changed in memory but could not be changed.\n");
        }
    }
    else
    {
        printf("[REGMGMT] SET failed. Error: %d\n", result);
    }
}

static void wd_reg_command_get(void)
{
    std::string entryname;

    printf("Entry name: ");
    std::getline(std::cin, entryname);

    WDRegistryEntry entry;

    int result = wd_reg_get(entryname.c_str(), entry);

    if (result != WD_REG_SUCCESS)
    {
        printf("[REGMGMT] Registry not found.\n");
        return;
    }

    wd_reg_print_entry(entry);
}

static void wd_reg_command_remove(void)
{
    std::string entryname;

    printf("Entry name: ");
    std::getline(std::cin, entryname);

    int result = wd_reg_remove(entryname.c_str());

    if (result == WD_REG_SUCCESS)
    {
        printf("[REGMGMT] Registry removed.\n");
    
        result = wd_reg_save();

        if (result != WD_REG_SUCCESS)
        {
            printf("[REGMGMT] WARNING: Registry removed in memory but could not be saved.\n");
        }
    }
    else
    {
        printf("[REGMGMT] Registry not found.\n");
    }
}

static bool wd_reg_process_command(
    const std::string& command
)
{
    if (command == "SET")
    {
        wd_reg_command_set();
        return true;
    }

    if (command == "GET")
    {
        wd_reg_command_get();
        return true;
    }

    if (command == "REMOVE")
    {
        wd_reg_command_remove();
        return true;
    }

    if (command == "LIST")
    {
        wd_reg_list();
        return true;
    }

    if (command == "SAVE")
    {
        int result = wd_reg_save();

        if (result ==  WD_REG_SUCCESS)
        {
            printf("[REGMGMT] Registry saved.\n");
        }
        else
        {
            printf("[REGMGMT] Failed to save registry.\n");
        }

        return true;
    }

    if (command == "RELOAD")
    {
        g_reg_initialized = false;

        int result = wd_reg_init();

        if (result == WD_REG_SUCCESS)
        {
            printf("[REGMGMT] Registry reloaded.\n");
        }
        else
        {
            printf("[REGMGMT] Failed to reload registry.\n");
        }

        return true;
    }

    if (command == "STATUS")
    {
        wd_reg_status();
        return true;
    }

    if (command == "HELP")
    {
        wd_reg_help();
        return true;
    }

    if (command == "EXIT")
    {
        return false;
    }

    if (!command.empty())
    {
        printf("[REGMGMT] Unknown command: %s\n", command.c_str());
    }

    return true;
}

void wd_reg_shutdown(void)
{
    if (!g_reg_initialized)
    {
        return;
    }

    // always save before shutting down, mother fucking dumbass.

    wd_reg_save();

    g_reg_initialized = false;
}

int main(void)
{
    printf("\n");
    printf("WDSYS Registry manager\n");

    int result = wd_reg_init();

    if (result != WD_REG_SUCCESS)
    {
        printf("[REGMGMT] Initialization failed. Error: %d\n", result);
        return 1;
    }

    printf("[REGMGMT] Registry initialized.\n");
    printf("[REGMGMT] Loaded %zu registry entr%s.\n", g_registry.size(), g_registry.size() == 1 ? "y" : "ies");
    printf("[REGMGMT] Type HELP for commands.\n");
    printf("\n");

    std::string command;

    while (true)
    {
        printf("REG> ");

        if (!std::getline(std::cin, command))
        {
            printf("\n[REGMGMT] Input closed.\n");
            break;
        }

        command = trim(command);

        for (char& c : command)
        {
            if (c >= 'a' && c <= 'z')
            {
                c = static_cast<char>(c - ('a' - 'A'));
            }
        }

        if (!wd_reg_process_command(command))
        {
            break;
        }
    }

    printf("[REGMGMT] Saving registry...\n");

    result = wd_reg_save();

    if (result != WD_REG_SUCCESS)
    {
        printf("[REGMGMT] WARNING: Failed to save registry.\n");
    }

    wd_reg_shutdown();

    printf("[REGMGMT] Shutting the absolute hell down...\n");

    return 0;
}