#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdint.h"

#define IMGREAD_VERSION "1.0"

#define IMGREAD_SUCCESS       0
#define IMGREAD_FILE_ERROR   -1
#define IMGREAD_NOT_PNG      -2
#define IMGREAD_FORMAT_ERROR -3
#define IMGREAD_MEMORY_ERROR -4

typedef struct
{
    FILE* file;

    uint32_t width;
    uint32_t height;

    unsigned char bit_depth;
    unsigned char colour_type;
    unsigned char compression;
    unsigned char filter;
    unsigned char interlace;

    unsigned char* image_data;
    size_t image_size;

    int loaded;
} PNGImage;

// ugly hell hole here!

static uint32_t crc32_table[256];
static int crc32_ready = 0;

static void crc32_init(void)
{
    uint32_t i;
    uint32_t j;
    uint32_t crc;

    if (crc32_ready)
        return;
    
    for (i = 0; i < 256; i++)
    {
        crc = i;

        for (j = 0; j < 8; j++)
        {
            if (crc & 1)
                crc = 0xEDB88320U ^ (crc >> 1);
            else
                crc >>= 1;
        }

        crc32_table[i] = crc;
    }

    crc32_ready = 1;
}

static uint32_t crc32_calculate(
    const unsigned char* data,
    size_t size
)
{
    uint32_t crc = 0xFFFFFFFFU;
    size_t i;

    crc32_init();

    for (i = 0; i < size; i++)
    {
        crc = crc32_table[(crc ^ data[i]) & 0xFFU] ^ (crc >> 8);
    }

    return crc ^ 0xFFFFFFFFU;
}

// im a fucking barbie girl in a barbie world

static uint32_t read_u32_be(const unsigned char* data)
{
    return ((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) | ((uint32_t)data[2] << 8) | ((uint32_t)data[3]);
}

static int png_check_signature(FILE* file)
{
    static const unsigned char signature[8] =
    {
       0x89,
        0x50,
        0x4E,
        0x47,
        0x0D,
        0x0A,
        0x1A,
        0x0A
    };

    unsigned char buffer[8];

    if (fread(buffer, 1, 8, file) != 8)
        return 0;
    
    if (memcmp(buffer, signature, 8) != 0)
        return 0;

    return 1;
}

// time to die in coding hell >:D

static int png_read_chunk(
    FILE* file,
    unsigned char** type,
    unsigned char** data,
    uint32_t* size
)
{
    unsigned char length_buffer[4];
    unsigned char crc_buffer[4];

    unsigned char chunk_type[4];

    unsigned char* chunk_data = NULL;

    if (fread(length_buffer, 1, 4, file) != 4)
    return 0;

    *size = read_u32_be(length_buffer);

    if (fread(chunk_type, 1, 4, file) != 4)
        return 0;

    if (*size > 0)
    {
        chunk_data = (unsigned char*)malloc(*size);

        if (chunk_data == NULL)
        return 0;

        if (fread(chunk_data, 1, *size, file) != *size)
        {
            free(chunk_data);
            return 0;
        }
    }  
    if (fread(crc_buffer, 1, 4, file) != 4)
    {
        free(chunk_data);
        return 0;
    }

    *type = (unsigned char*)malloc(4);

    if (*type == NULL)
    {
        free(chunk_data);
        return 0;
    }

    memcpy(*type, chunk_type, 4);

    *data = chunk_data;

    return 1;
}

static int png_open(
    PNGImage* image,
    const char* path
)
{
    unsigned char* type = NULL;
    unsigned char* data = NULL;

    uint32_t size;

    if (image == NULL || path == NULL)
        return IMGREAD_FORMAT_ERROR;

    memset(image, 0, sizeof(PNGImage));

    image->file = fopen(path, "rb");

    if (image->file == NULL)
        return IMGREAD_FILE_ERROR;
    
    if (!png_check_signature(image->file))
    {
        fclose(image->file);
        image->file = NULL;

        return IMGREAD_NOT_PNG;
    }

    while (1)
    {
        if (!png_read_chunk(image->file, &type, &data, &size))
        {
            fclose(image->file);
            image->file = NULL;

            return IMGREAD_FORMAT_ERROR;
        }

        if (memcmp(type, "IHDR", 4) == 0)
        {
            if (size != 13)
            {
                free(type);
                free(data);

                fclose(image->file);
                image->file = NULL;

                return IMGREAD_FORMAT_ERROR;
            }

            image->width = read_u32_be(&data[0]);

            image->height = read_u32_be(&data[4]);

            image->bit_depth = data[8];

            image->colour_type = data[9];

            image->compression = data[10];

            image->filter = data[11];

            image->interlace = data[12];

            printf("PNG: %lu x %lu\n", (unsigned long)image->width, (unsigned long)image->height);

            printf("PNG: bit depth: %u\n", image->bit_depth);

            printf("PNG: colour type: %u\n", image->colour_type);

            free(type);
            free(data);

            break;
        }

        free(type);
        free(data);
        type = NULL;
        data = NULL;
    }

image->loaded = 1;

return IMGREAD_SUCCESS;

}

static void png_close(PNGImage* image)
{
    if (image == NULL)
        return;

    if (image->file != NULL)
    {
        fclose(image->file);
        image->file = NULL;
    }

    if (image->image_data != NULL)
    {
        free(image->image_data);
        image->image_data = NULL;
    }

    image->image_size = 0;
    image->loaded = 0;
}

static void print_help(void)
{
    printf("\n");
    printf("WDSYS IMGREAD %s\n", IMGREAD_VERSION);
    printf("\n");

    printf("Commands:\n");
    printf("  OPEN <path>   Open a PNG file\n");
    printf("  CLOSE         Close the current image\n");
    printf("  INFO          Display image information\n");
    printf("  HELP          Display this help\n");
    printf("  EXIT          Shut down imgread\n");
    printf("\n");
}

// this is fuckin light, eh?

int main(void)
{
    PNGImage image;

    char command[1024];

    memset(&image, 0, sizeof(PNGImage));

    printf("WDSYS IMGREAD %s\n", IMGREAD_VERSION);
    printf("Native PNG reader\n");
    printf("No external image libraries\n");
    printf("\n");

    print_help();

    while (1)
    {
        printf("imgread> ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL)
            break;

        command[strcspn(command, "\r\n")] = '\0';

        if (strcmp(command, "EXIT") == 0)
        {
            break;
        }

        if (strcmp(command, "HELP") == 0)
        {
            print_help();
        }

        if (strcmp(command, "CLOSE") == 0)
        {
            png_close(&image);

            printf("Image closed.\n");

            continue;
        }

        if (strcmp(command, "INFO") == 0)
        {
            if (!image.loaded)
            {
                printf("No image loaded.\n");
                continue;
            }

            printf("\n");
            printf("Width:      %lu\n", (unsigned long)image.width);
            printf("Height:     %lu\n", (unsigned long)image.height);
            printf("Bit Depth:  %u\n", image.bit_depth);
            printf("Colour Type: %u\n", image.colour_type);
            printf("Interlace:  %u\n", image.interlace);

            continue;
        }

        if (strncmp(command, "OPEN ", 5) == 0)
        {
            const char* path = command + 5;

            png_close(&image);

            printf("Opening: %s\n", path);

            {
                int result = png_open(&image, path);

                if (result == IMGREAD_SUCCESS)
                {
                    printf(
                        "PNG opened successfully.\n"
                    );
                }
                else if (result == IMGREAD_FILE_ERROR)
                {
                    printf(
                        "ERROR: Could not open file.\n"
                    );
                }
                else if (result == IMGREAD_NOT_PNG)
                {
                    printf(
                        "ERROR: File is not a PNG.\n"
                    );
                }
                else
                {
                    printf(
                        "ERROR: Invalid PNG structure.\n"
                    );
                }
            }

            continue;
        }

        printf("Unknown command. Type HELP.\n");

    }

    png_close(&image);

    printf("IMGREAD shutting down.\n");

    return 0;
}