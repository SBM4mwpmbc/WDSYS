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
    unsigned long long bytes_per_pixel;

    if (!g_camera.initialized)
    {
        return 0;
    }

    switch (g_camera.pixel_format)
    {
        case CAMCTRL_PIXEL_RGB24:
            bytes_per_pixel = 3;
            break;
        
            case CAMCTRL_PIXEL_RGBA32:
            bytes_per_pixel = 4;
            break;
        
            case CAMCTRL_PIXEL_GRAY8:
            bytes_per_pixel = 1;
            break;
        
        default:
            return 0;
    }

    return (unsigned long long)g_camera.width * g_camera.height * bytes_per_pixel;

}

// submit a captured frame. soon a future driver can do the camera data.

int camctrl_submit_frame(
    const unsigned char* data,
    unsigned long long data_size
)
{
    unsigned long long required_size;

    if (!g_camera.initialized)
    {
        return CAMCTRL_NOT_INITIALIZED;
    }

    if (data == NULL)
    {
        return CAMCTRL_ERROR;
    }

    required_size = camctrl_get_frame_size();
    
    if (data_size != required_size)
    {
        return CAMCTRL_ERROR;
    }

    if (g_camera.current_frame.data == NULL)
    {
        return CAMCTRL_ERROR;
    }

    memcpy(g_camera.current_frame.data, data, required_size);

    g_camera.current_frame.width = g_camera.width;
    g_camera.current_frame.height = g_camera.height;
    g_camera.current_frame.pixel_format = g_camera.pixel_format;
    g_camera.current_frame.frame_size = required_size;

    g_camera.frames_captured++;

    return CAMCTRL_OK;
}

int camctrl_get_frame_info(
    unsigned int *width,
    unsigned int *height,
    unsigned int *pixel_format,
    unsigned long long *frame_size
)
{
    if (!g_camera.initialized)
    {
        return CAMCTRL_NOT_INITIALIZED;
    }

    if (g_camera.current_frame.data == NULL)
    {
        return CAMCTRL_ERROR;
    }

    if (width != NULL)
        *width = g_camera.current_frame.width;

    if (height != NULL)
        *height = g_camera.current_frame.height;

    if (pixel_format != NULL)
        *pixel_format = g_camera.current_frame.pixel_format;

    if (frame_size != NULL)
        *frame_size = g_camera.current_frame.frame_size;

    return CAMCTRL_OK;
}

int camctrl_copy_frame(
    // unfinished