#include "regmgmt.h"

#include <map>
#include <string>

static std::map<std::string, std::string> g_registry;
static bool g_reg_initialized = false;

int wd_reg_init(void)
{
    if (g_reg_initialized)
    {
        return WD_REG_SUCCESS;
    }

    g_registry.clear();
    g_reg_initialized = true;

    return WD_REG_SUCCESS;
}

int wd_reg_set(
    const char* key,
    const char* value
)
{
    if (!g_reg_initialized)
    {
        return WD_REG_GENERAL_ERROR;
    }

    if (key == nullptr || key[0] == '\0')
    {
        return WD_REG_INVALID_KEY;
    }

    if (g_registry.find(key) == g_registry.end())
    {
        return 0;
    }

    return 1;
}

int wd_reg_remove(
    const char* key
)
{
    if (!g_reg_initialized)
    {
        return WD_REG_GENERAL_ERROR;
    }

    if (key == nullptr || key[0] == '\0')
    {
        return WD_REG_INVALID_KEY;
    }

    auto entry = g_registry.find(key);

    if (entry == g_registry.end())
    {
        return WD_REG_NOT_FOUND;
    }

    g_registry.erase(entry);

    return WD_REG_SUCCESS;
}

void wd_reg_shutdown(void)
{
    g_registry.clear();
    g_reg_initialized = false;
}

int main(void)
{
    int result = wd_reg_init();

    if (result != WD_REG_SUCCESS)
    {
        return result;
    }

    return WD_REG_SUCCESS;
}