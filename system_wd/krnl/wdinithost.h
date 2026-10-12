// i wrote this in school, so it might be a bit messy, but it works.

#ifndef WDINITHOST_H
#define WDINITHOST_H
#include <string>

// add these bools to the header, so it's simple, and add these too so the compiler can stop
// yapping

extern bool service_initialized;
extern std::string service_status;
bool srvc1_init = false;
bool srvc2_init = false;
bool srvc3_init = false;
bool srvc4_init = false;
bool srvc5_init = false;
bool srvc6_init = false;
bool srvc7_init = false;
bool srvc8_init = false;
bool srvc9_init = false;
bool srvc10_init = false;
bool srvc11_init = false;
bool srvc12_init = false;
bool srvc13_init = false;
bool srvc14_init = false;

#define WDINITHOST_SUCCESS true
#define WDINITHOST_ERROR false

bool reg_read();
bool SRVCE_START();
bool SRVCE_INIT();
bool SRVCE_RUNTIME();

// i dont know if you can add structs in headers, but add the struct to the .cpp just in case if it
// doesnt

#endif
