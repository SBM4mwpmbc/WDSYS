#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CAMCTRL_DEFAULT_WIDTH       1280
#define CAMCTRL_DEFAULT_HEIGHT       720
#define CAMCTRL_DEFAULT_BPP            24

#define CAMCTRL_SUCCESS                0
#define CAMCTRL_NOT_INITIALIZED       -1
#define CAMCTRL_ALREADY_INITIALIZED   -2
#define CAMCTRL_INVALID_ARGUMENT      -3
#define CAMCTRL_MEMORY_ERROR          -4
#define CAMCTRL_BUFFER_TOO_SMALL      -5
#define CAMCTRL_NO_FRAME              -6
#define CAMCTRL_GENERAL_ERROR         -7


static int g_initialized = 0;

static unsigned int g_width = 0;
static unsigned int g_height = 0;
static unsigned int g_bpp = 0;

static unsigned long g_frame_size = 0;

static unsigned char* g_frame_buffer = NULL;

static unsigned long g_frame_number = 0;

static int camctrl_calculate_frame_size(
    unsigned int width,
    unsigned int height,
    unsigned int bpp,
    unsigned long* size
)
{
    unsigned long bytes_per_pixel;
    unsigned long pixels;

    if (size == NULL) 
    {
        return CAMCTRL_INVALID_ARGUMENT;
    }

    if (width == 0 || height == 0 || bpp == 0) 
    {
        return CAMCTRL_INVALID_ARGUMENT;
    }

    if ((bpp % 8) != 0)
    {
        return CAMCTRL_INVALID_ARGUMENT;
    }

    bytes_per_pixel = bpp / 8;

    if ((unsigned long)width > ULONG_MAX / (unsigned long)height)
    {
        return CAMCTRL_GENERAL_ERROR;
    }

    pixels = (unsigned long)width * (unsigned long)height;

    if (pixels > ULONG_MAX / bytes_per_pixel)
    {
        return CAMCTRL_GENERAL_ERROR;
    }

    *size = pixels * bytes_per_pixel;

    return CAMCTRL_SUCCESS;
}

int camctrl_int(
    unsigned int width,
    unsigned int height,
    unsigned int bpp
)
{
    unsigned long frame_size;
    unsigned char* buffer;

    if (g_initialized)
    {
        return CAMCTRL_ALREADY_INITIALIZED;
    }

    if (camctrl_calculate_frame_size(width, height, bpp, &frame_size) != CAMCTRL_SUCCESS)
    {
        return CAMCTRL_INVALID_ARGUMENT;
    }

    buffer = (unsigned char*)malloc(frame_size);

    if (buffer == NULL)
    {
        return CAMCTRL_MEMORY_ERROR;
    }

    memset(buffer, 0, frame_size);

    g_width = width;
    g_height = height;
    g_bpp = bpp;

    g_frame_size = frame_size;

    g_frame_buffer = buffer;

    g_frame_number = 0;

    g_initialized = 1;

    return CAMCTRL_SUCCESS;
}

int camctrl_shutdown(void)
{
    if (!g_initialized)
    {
        return CAMCTRL_NOT_INITIALIZED;
    }

    if (g_frame_buffer != NULL)
    {
        free(g_frame_buffer);
        g_frame_buffer = NULL;
    }

    g_width = 0;
    g_height = 0;
    g_bpp = 0;

    g_frame_size = 0;
    g_frame_number = 0;

    g_initialized = 0;

    return CAMCTRL_SUCCESS;
}

int camctrl_submit_frame(
    const unsigned char* frame,
    unsigned long frame_size
)
{
    if (!g_initialized)
    {
        return CAMCTRL_NOT_INITIALIZED;
    }

    if (frame == NULL)
    {
        return CAMCTRL_INVALID_ARGUMENT;
    }

    if (frame_size != g_frame_size)
    {
        return CAMCTRL_INVALID_ARGUMENT;
    }

    memcpy(g_frame_buffer, frame, g_frame_size);

    g_frame_number++;

    return CAMCTRL_SUCCESS;
}

int camctrl_get_frame_info(
    unsigned int* width,
    unsigned int* height,
    unsigned int* bpp,
    unsigned long* frame_size,
    unsigned long* frame_number
)
{
    if (!g_initialized)
    {
        return CAMCTRL_NOT_INITIALIZED;
    }

    if (width == NULL || height == NULL || bpp == NULL || frame_size == NULL || frame_number == NULL)
    {
        return CAMCTRL_INVALID_ARGUMENT;
    }

    *width = g_width;
    *height = g_height;
    *bpp = g_bpp;
    *frame_size = g_frame_size;
    *frame_number = g_frame_number;

    return CAMCTRL_SUCCESS;
}

int camctrl_copy_frame(
    unsigned char* destination,
    unsigned long destination_size
)
{
    if (!g_initialized)
    {
        return CAMCTRL_NOT_INITIALIZED;
    }

    if (destination == NULL)
    {
        return CAMCTRL_INVALID_ARGUMENT;
    }

    if (destination_size < g_frame_size)
    {
        return CAMCTRL_BUFFER_TOO_SMALL;
    }

    if (g_frame_number == 0)
    {
        return CAMCTRL_NO_FRAME;
    }

    memcpy(destination, g_frame_buffer, g_frame_size);

    return CAMCTRL_SUCCESS;
}

void camctrl_print_info(void)
{
    if (!g_initialized)
    {
        printf("CAMCTRL: Camera is not initialized.\n");
        return;
    }

    printf("CAMCTRL Camera Info\n");

    printf("Resolution: %u x %u\n", g_width, g_height);

    printf("Colour depth: %u bpp\n", g_bpp);

    printf("Frame size: %lu bytes\n", g_frame_size);

    printf("Frame count: %lu\n", g_frame_number);
}

static void camctrl_generate_test_frame(
    unsigned char* buffer,
    unsigned int width,
    unsigned int height
)
{
    unsigned int x;
    unsigned int y;

    if (buffer == NULL)
    {
        return;
    }

    /*
    RGB24 test
    this is only for testing camctrl
    it isnt the final camera output
    */

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            unsigned long index;

            index = ((unsigned long)y * (unsigned long)width + (unsigned long)x) * 3;

            buffer[index + 0] = (unsigned char)(x % 256);

            buffer[index + 1] = (unsigned char)(y % 256);

            buffer[index + 2] = (unsigned char)((x + y) % 256);
        }
    }
}

int main(void)
{
    int result;

    unsigned int width;
    unsigned int height;
    unsigned int bpp;

    unsigned long frame_size;
    unsigned long frame_number;

    unsigned char* test_frame;
    unsigned char* copied_frame;

    printf("WDSYS CAMCTRL TEST COPY\n");

    result = camctrl_init(CAMCTRL_DEFAULT_WIDTH, CAMCTRL_DEFAULT_HEIGHT, CAMCTRL_DEFAULT_BPP);