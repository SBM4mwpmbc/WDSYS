#include <string>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <thread>
#include <iostream>

const char* msg = "LINUX IS THE BEST";
bool loop = true;

int main(void)
{
    while (loop = true)
    {
        printf(msg);
        
        std::this_thread::sleep_for(std::chrono::seconds(5));
        bool loop = false;
        return 0;
    }
}