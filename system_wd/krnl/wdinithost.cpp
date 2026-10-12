#include <stdio.h>
#include "wdinithost.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <filesystem>
#include <array>
// why have includes when you can  already include them in your own language?
// add the bools in the header, so my brain doesnt explode

bool service_initialized = true;
bool service_status = "Initializing..";

struct Service
{
	std::string name;
	bool initialized = false;
};

std::array<Service, 14> services = {{
    {"face_render.exe"},
    {"imgread.exe"},
    {"digest_reg.exe"},
    {"linuxpraise.exe"},
    {"demochck.exe"},
    {"emrgchck.exe"},
    {"prcss.exe"},
    {"cnnct.exe"},
    {"gpt.exe"},
    {"c_ai_talk.exe"},
    {"see.exe"},
    {"flexmov.exe"},
    {"mdterminal.exe"},
    {"wdsys_setup.exe"}
    // you know what? Im not even done nron_multi yet, imma end this array off for now
	// mdterminal is a secret terminal ;)
}};

// who cares? just make it all voids and bools and hope that it doesnt break..

bool reg_read(void)
{
	// read the registry to see if the setup needs to be initialized, then just
	// if the setup mark ISNT there, start the setup

	if (!service_initialized)
	{
		std::cout << "[WDINITHOST] UNKNOWN ERROR\n" << std::endl;
		return 1;
	}
	
	if (!srvc14_init)
	{
		srvc14_init = true;
		// 2 routes: 1: start the srvc via here. 2: do it via srvce_start. Lets do 2 for now.
	}
	return 0;
}

bool SRVCE_START(void)
{
	
	// i have no idea on how to start .exes in C++, im so cooked
	// do placeholders for now
	
	if (!srvc1_init)
	{
		// init the .exe, but this is the placeholder so far, so just change the actual state
		srvc1_init = true;
	}
	
	// …
	
	if (srvc14_init = WDINITHOST_SUCCESS)
	{
		// start setup here
	}

	// dont do those status ones too, those are pure typin stuff that makes your fingers burn

	return 0;
}
	
bool SRVCE_INIT(void)
{
	std::cout << "Initializing services.. STATUS: " << service_status  << "\n" << std::endl;
	
	if (SRVCE_START() != WDINITHOST_SUCCESS)
	{
		std::cout << "Couldnt initialize services.\n" << std::endl;
		return 1;
	}

	service_initialized = true;
	service_status = "Pass off ready";
	std::cout << "Initialized. Ready to pass on.. STATUS: " << service_status << "\n" << std::endl;
	// the main  will pass on here eventually
	return 0;
}

bool SRVCE_RUNTIME(void)
{
	if (!service_initialized)
	{
		std::cout << "UNKNOWN ERROR\n" << std::endl;
		return 1;
	}
	
    service_status = "Passing off..";
	std::cout << "Passing on to the runtime function.. STATUS: " << service_status << "\n";
	service_status = "Runtime.";
	std::cout << "Passed on. Entering runtime..\n" << std::endl;
	
	while (service_status = "Runtime.")
	{
        std::cout << "STATUS: " << service_status << "\n" << std::endl;
        // runtime loop so the program keeps running
    }

    return 0;
}

int main(void)
{
	std::cout << "Startup detected!\n" << std::endl;
	
	if (SRVCE_INIT() != 0)
	{
        std::cout << "Failed to start.\n" << std::endl;
        return 1;
    }
    else
    {
        if (SRVCE_RUNTIME() == 1)
        {
            return 1;
        }
    }
}
