#include <stdio.h>
#include <iostream>
#include <portaudio.h>

int main(void)
{
    PaError err = Pa_Initialize();

    if (err != paNoError)
    {
        printf("PORTAUDIO INIT FAIL: %d\n", Pa_GetErrorText(err));
        return 1;
    }

    printf("Available mic devices:\n");

    int device_count = Pa_GetDeviceCount();

    if (device_count < 0)
    {
        printf("LIST AUDIO DEV ERR %d\n", Pa_GetErrorText(device_count));
        Pa_Terminate();
        return 1;
    }

    for (int i = 0; i < device_count; ++i)
    {
        const PaDeviceInfo* device_info = Pa_GetDeviceInfo(i);

        if (device_info != nullptr && device_info->maxInputChannels > 0)
        {
            std::cout << i << ": " << device_info->name << "\n";
        }
    }

    Pa_Terminate();
    return 0;
}