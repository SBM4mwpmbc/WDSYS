#include <iostream>
#include <string>

bool internet_initialized = false;
bool internet_connected = false;

int internet_init(void)
{
    std::cout << "[INTERNET] Initializing internet..\n" << std::endl;

    // initialize:
    // NM (NetworkManager)
    // modem (ModemManager)
    // other

    internet_initialized = true;

    std::cout << "[INTERNET] Internet initialized\n" << std::endl;

    return 0;
}

int internet_connect()
{
    if (!internet_initialized)
    {
        std::cout << "[INTERNET] Internet not initialized\n" << std::endl;
        return 1;
    }

    std::cout << "[INTERNET] Connecting to the internet..\n" << std::endl;

    // establish connecton

    internet_connected = true;

    std::cout << "[INTERNET] Connected to the internet.\n" << std::endl;

    return 0;
}

int internet_disconnect()
{
    if (!internet_initialized)
    {
        std::cout << "[INTERNET] Unknown error" << std::endl;
        return 1;
    }

    std::cout << "[INTERNET] Disconnecting from internet..\n" << std::endl;

    // tell vro to disconnect this shitbox

    internet_connected = false;

    std::cout << "[INTERNET] Disconnected from the internet\n" << std::endl;

    return 0;
}

bool internet_is_connected()
{
    return internet_connected;
}

int main(void)
{
    std::cout << "[INTERNET] starting intuhnet\n" << std::endl;

    if (internet_init() != 0)
    {
        std::cout << "[INTERNET] Could not initialize internet.\n" << std::endl;
        return 1;
    }

    return 0;
}