#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAMCTRL_VERSION "1.0"

#define CAMCTRL_OK                0
#define CAMCTRL_ERROR            -1
#define CAMCTRL_NOT_INITIALIZED  -2
#define CAMCTRL_ALREADY_RUNNING  -3

#define CAMCTRL_PIXEL_RGB24      1
#define CAMCTRL_PIXEL_RGBA32     2
#define CAMCTRL_PIXEL_GRAY8      3

typedef struct
{
    unsigned int width;
    unsigned int height;
    unsigned int pixel_format;
    unsigned long long frame_size;
    unsigned char *data;
} CAMCTRL_FRAME;

typedef struct
{
    int initialized;
    int running;
    
    unsigned int width;
    unsigned int height;
    unsigned int pixel_format;

    unsigned long long frames_captured;

    CAMCTRL_FRAME current_frame;
} CAMCTRL_STATE;

static CAMCTRL_STATE g_camera;

int camctrl_initialize(
    unsigned int width,
    unsigned int height,
    unsigned int pixel_format
)
{
    if (g_camera.initialized)
    {
        return CAMCTRL_ALREADY_RUNNING;
    }

    if (width == 0 || height == 0)
    {
        return CAMCTRL_ERROR;
    }

    if (pixel_format != CAMCTRL_PIXEL_RGB24 && pixel_format != CAMCTRL_PIXEL_RGBA32 && pixel_format != CAMCTRL_PIXEL_GRAY8)
    {
        return CAMCTRL_ERROR;
    }

    memset(&g_camera, 0, sizeof(g_camera));

    g_camera.width = width;
    g_camera.height = height;
    g_camera.pixel_format = pixel_format;

    g_camera.initialized = 1;
    g_camera.running = 1;

    return CAMCTRL_OK;
}

void camctrl_shutdown(void)
{
    if (g_camera.current_frame.data != NULL)
    {
        free(g_camera.current_frame.data);
        g_camera.current_frame.data = NULL;
    }

    memset(&g_camera, 0, sizeof(g_camera));
}

unsigned long long camctrl_get_frame_size(void)
{
    // unfinished
}