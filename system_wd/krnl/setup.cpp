#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

// defines for the STATUS CODES 🗣️🔥
// why the hell is there an emoji? i didnt know that was possible to add
// in code
/* Dictionary:
    DUR - In progress
    CPLT - Complete
    VLDTE - Validate
    CPY - Copy
    INSTL - Install
    ERR - Error */
#define ERR 0
#define INIT_DUR 1
#define INIT_CPLT 2
#define READ_DUR 3
#define READ_CPLT 4
#define VLDTE_DUR 5
#define VLDTE_CPLT 6
#define CPY_DUR 7
#define CPY_CPLT 8
#define INSTL_DUR 9
#define INSTL_CPLT 10
#define PRSE_DUR 11
#define PRSE_CPLT 12
#define EXIT_DUR 13
#define EXIT_CPLT 14

// when is N and Uzi gonna have babies already ahrfughghghhhhhhhhhhh ikm ,shittijng fdPAHHHHAHRHUGGHHH
// i llvole N and Uzi fnaartt anedfur89finjHUHYUHHHHGHGHGHG8UGHGHHA ARGGHGHGHGHGH HEKP LHELP HELP IM GOING SINSABN EEEEEE

int read_setup_config()
{
    std::cout << "[WDSYS SETUP] Reading SETUP.dat\n" << std::endl;

    std::ifstream setup_file("SETUP.dat");

    if (!setup_file.is_open())
    {
        std::cout << "[WDSYS SETUP] Unable to open SETUP.dat\n" << std::endl;
        return 0;
    }

    std::string line;

    while (std::getline(setup_file, line))
    {
        // temporary parsing for SETUP.dat
    }

    setup_file.close();

    std::cout << "[WDSYS SETUP] Read config file.\n" << std::endl;

    return 4;
}

int validate_setup_config()
{
    std::cout << "[WDSYS SETUP] Validating config\n" << std::endl;

    std::ifstream setup_file("SETUP.dat");

    if (!setup_file.is_open())
    {
        std::cout << "[WDSYS SETUP] Unable to open config file.\n" << std::endl;
        return 1;
    }

    std::string line;
    bool has_data = false;

    while (std::getline(setup_file, line))
    {
        if (!line.empty())
        {
            has_data = true;
            break;
        }
    }

    setup_file.close();

    if (!has_data)
    {
        std::cout << "[WDSYS SETUP] config is empty or invalid.\n" << std::endl;
        return 0;
    }

    std::cout << "[WDSYS SETUP] CONFIG is valid.\n" << std::endl;

    return 6;
}

int validate_system()
{
    std::cout << "Validating the system...\n" << std::endl;
    // validate the sys  here
    std::cout << "System validated. Continuing setup...\n" << std::endl;

    return 6;
}

int copy_files()
{
    std::cout << "[WDSYS SETUP] Copying WDSYS files from USB/CD to Hard Disk.. This may take a moment..\n" << std::endl;

    // todo: copy CD/USB files to harddisk here

    std::cout << "[WDSYS SETUP] Exploring files..\n" << std::endl;
    std::filesystem::path source = "D:/WDSYS";
    std::filesystem::path destination = "C:/WDSYS";

    if (!std::filesystem::exists(source))
    {
        std::cout << "[WDSYS SETUP] No installation media found.\n" << std::endl;
        return ERR;
    }
    std::cout << "[WDSYS SETUP] Extracting and expanding files..\n" << std::endl;
    std::error_code ec;
    std::cout << "[WDSYS SETUP] Copying files..\n" << std::endl;
    std::filesystem::copy(source, destination, std::filesystem::copy_options::recursive, ec);

    if (ec)
    {
        std::cout << "[WDSYS SETUP] Could not copy files.\n" << std::endl;
        std::cout << "[WDSYS SETUP] Error: " << ec.message() << "\n" << std::endl;
        return ERR;
    }

    std::cout << "[WDSYS SETUP] Copied! Finalizing..\n" << std::endl;
    return CPY_CPLT;
}

int write_setup_mark(void)
{
    std::cout << "[WDSYS SETUP] Writing setup mark\n" << std::endl;
    
    std::ofstream setup_file("SETUP.dat", std::ios::app);

    if (!setup_file.is_open())
    {
        std::cout << "[WDSYS SETUP] Unable to write setup mark\n" << std::endl;
        return ERR;
    }

    setup_file << "\n[ \"wdsys-setup-mark\"\n" << "\tENTRYNAME=[WDSYS].[BOOTCONFIG]/[SETUPVLDTE]\n" << "\tVALUEDATA=\"SETUPCPLT\":mark-first-boot-validate:\n" << "\t:wdinithost-frstboot-chck: ]\n";
    
    setup_file.close();

    std::cout << "[WDSYS SETUP] Setup completion mark written\n" << std::endl;

    return INSTL_CPLT;
}

int finalize_setup(void)
{
    if (copy_files() == CPY_CPLT)
    {
        validate_system();
        read_setup_config();
        validate_setup_config();
        write_setup_mark();
        std::cout << "Verified integrity of hard disk. Exiting finalization function..\n" << std::endl;
        return INSTL_CPLT;
    }
    else
    {
        std::cout << "An unknown error has been encountered.\n" << std::endl;
        return ERR;
    }
}

int main(void)
{
    std::cout << "[WDSYS SETUP] Preparing setup..\n" << std::endl;
    std::cout << "[WDSYS SETUP] Starting setup...\n" << std::endl;
    // Initialize the setup
    int status = validate_system();

    if (status == ERR)
    {
        std::cout << "[WDSYS SETUP] Sys validate failed. Unable to continue\n" << std::endl;
        return ERR;
    }
    
    status = read_setup_config();

    if (status == ERR)
    {
        std::cout << "[WDSYS SETUP] config could not be loaded.\n" << std::endl;
        return ERR;
    }

    status = validate_setup_config();

    if (status == ERR)
    {
        // STOP FUCKING COPYING IT TO E2BIG ARHGHGGHGHHHGGHGHG PLEEAASSEEE
        std::cout << "[WDSYS SETUP] config validation failed\n" << std::endl;
        return ERR;
    }

    status = finalize_setup();

    if (status == ERR)
    {
        std::cout << "Couldnt finialize setup." << std::endl;
    }
    else
    {
        std::cout << "[WDSYS SETUP] Finished setup and installation. Please restart your drone.\n" << std::endl;
        return 2;
    }
}