
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define WD_INIT_VERSION                 1
#define WD_SHELL_VERSION                1

#define WD_SHELL_MAX_INPUT              256
#define WD_SHELL_MAX_DIRECTORY          256
#define WD_SHELL_MAX_ARGUMENTS          16
#define WD_SHELL_MAX_ARGUMENT_LENGTH    256

#define WD_SHELL_COMMAND_LNCH           "lnch"
#define WD_SHELL_COMMAND_DIR            "dir"
#define WD_SHELL_COMMAND_SNAP           "snap"
#define WD_SHELL_COMMAND_WHO            "who"
#define WD_SHELL_COMMAND_REQ            "req"
#define WD_SHELL_COMMAND_EXIT           "exit"

#define WD_SHELL_MAX_CUSTOM_COMMANDS    64
#define WD_SHELL_MAX_COMMAND_NAME       64
#define WD_SHELL_MAX_PROVIDER_NAME      128

#define WD_KRNL_SUCCESS                 0
#define WD_KRNL_INVALID_ARGUMENT        1
#define WD_KRNL_INIT_FAILED             2
#define WD_KRNL_FATAL_ERROR             3

typedef enum
{
    WD_SHELL_ERROR_NONE = 0,

    WD_SHELL_ERROR_UNKNOWN_COMMAND,
    WD_SHELL_ERROR_INVALID_ARGUMENT,
    WD_SHELL_ERROR_COMMAND_TOO_LONG,
    WD_SHELL_ERROR_PROVIDER_NOT_FOUND,
    WD_SHELL_ERROR_PROCESS_LAUNCH_FAILED,
    WD_SHELL_ERROR_KERNEL_COMMUNICATION,
    WD_SHELL_ERROR_NOT_INITIALIZED,
    WD_SHELL_ERROR_INTERNAL

} WD_SHELL_ERROR;

typedef struct
{
    WD_SHELL_ERROR error;
    uint32_t kernel_result;
    uint32_t process_id;

} WD_SHELL_ERROR_STATUS;

typedef enum
{
    WD_SHELL_STATE_NONE = 0,
    WD_SHELL_STATE_INITIALIZING,
    WD_SHELL_STATE_READY,
    WD_SHELL_STATE_RUNNING,
    WD_SHELL_STATE_FAILED,
    WD_SHELL_STATE_STOPPED

} WD_SHELL_STATE;

typedef enum
{
    WD_SHELL_KERNEL_OPERATION_NONE = 0,

    WD_SHELL_KERNEL_OPERATION_GET_STATUS,
    WD_SHELL_KERNEL_OPERATION_GET_DIRECTORY,
    WD_SHELL_KERNEL_OPERATION_SET_DIRECTORY,
    WD_SHELL_KERNEL_OPERATION_REQUEST,
    WD_SHELL_KERNEL_OPERATION_SNAPSHOT,
    WD_SHELL_KERNEL_OPERATION_LAUNCH

} WD_SHELL_KERNEL_OPERATION;

typedef enum
{
    WD_SHELL_COMMAND_UNKNOWN = 0,

    WD_SHELL_COMMAND_LNCH_ID,
    WD_SHELL_COMMAND_DIR_ID,
    WD_SHELL_COMMAND_SNAP_ID,
    WD_SHELL_COMMAND_WHO_ID,
    WD_SHELL_COMMAND_REQ_ID,
    WD_SHELL_COMMAND_EXIT_ID

} WD_SHELL_COMMAND_ID;

typedef struct
{
    char command[WD_SHELL_MAX_ARGUMENT_LENGTH];

    char arguments[
        WD_SHELL_MAX_ARGUMENTS
    ][WD_SHELL_MAX_ARGUMENT_LENGTH];

    uint32_t argument_count;

} WD_SHELL_COMMAND;

typedef struct
{
    WD_SHELL_STATE state;

    uint8_t initialized;
    uint8_t running;

    uint32_t process_id;

    char current_directory[
        WD_SHELL_MAX_DIRECTORY
    ];

    char input_buffer[
        WD_SHELL_MAX_INPUT
    ];

    WD_SHELL_COMMAND parsed_command;

    char execution_arguments[
        WD_SHELL_MAX_INPUT
    ];

    WD_SHELL_ERROR_STATUS error_status;

} WD_SHELL_DATA;

typedef struct
{
    uint32_t result;
    uint32_t process_id;

} WD_SHELL_PROCESS_RESULT;

typedef struct
{
    uint8_t registered;

    char command[
        WD_SHELL_MAX_COMMAND_NAME
    ];

    char provider[
        WD_SHELL_MAX_PROVIDER_NAME
    ];

} WD_SHELL_CUSTOM_COMMAND;

typedef struct
{
    WD_SHELL_KERNEL_OPERATION operation;

    uint32_t process_id;

    const void* input;
    uint32_t input_size;

    void* output;
    uint32_t output_size;

} WD_SHELL_KERNEL_REQUEST;

typedef struct
{
    uint32_t result;
    uint32_t output_size;

} WD_SHELL_KERNEL_RESPONSE;

typedef struct
{
    uint8_t initialized;
    uint8_t connected;

    uint32_t process_id;

} WD_SHELL_KERNEL_STATUS;

typedef struct
{
    uint8_t initialized;

    uint32_t process_id;

} WD_SHELL_PROCESS_INTERFACE;


static WD_SHELL_CUSTOM_COMMAND
    g_shell_custom_commands[
        WD_SHELL_MAX_CUSTOM_COMMANDS
    ];

static uint32_t
    g_shell_custom_command_count = 0;

static WD_SHELL_DATA g_shell;

static WD_SHELL_KERNEL_STATUS
    g_shell_kernel;

static WD_SHELL_PROCESS_INTERFACE
    g_shell_process;


/*
 * Function declarations.
 */

static uint32_t wd_shell_build_arguments(
    const WD_SHELL_COMMAND* command,
    char* output,
    uint32_t output_size
);

static uint32_t wd_shell_process_launch(
    const char* executable,
    const char* arguments,
    WD_SHELL_PROCESS_RESULT* result
);

static uint32_t wd_shell_launch_custom_provider(
    const WD_SHELL_COMMAND* command
);

static WD_SHELL_ERROR wd_shell_translate_error(
    uint32_t result
);

static uint32_t wd_shell_set_error(
    WD_SHELL_ERROR error,
    uint32_t kernel_result
);

static uint32_t wd_shell_parse_command(
    const char* input,
    WD_SHELL_COMMAND* command
);

static uint8_t wd_shell_command_is_empty(
    const WD_SHELL_COMMAND* command
);

static uint32_t wd_shell_execute_command(
    const WD_SHELL_COMMAND* command
);

static void wd_shell_clear_error(
    void
);


/*
 * Shell initialization.
 */

static uint32_t wd_shell_initialize(
    void
)
{
    g_shell.state =
        WD_SHELL_STATE_INITIALIZING;

    g_shell.initialized = 0;
    g_shell.running = 0;

    g_shell.process_id = 0;

    strcpy(
        g_shell.current_directory,
        "/"
    );

    g_shell.input_buffer[0] = '\0';

    g_shell.execution_arguments[0] = '\0';

    g_shell.error_status.error =
        WD_SHELL_ERROR_NONE;

    g_shell.error_status.kernel_result =
        WD_KRNL_SUCCESS;

    g_shell.error_status.process_id = 0;


    /*
     * Clear custom command registry.
     */

    g_shell_custom_command_count = 0;

    for (uint32_t i = 0;
         i < WD_SHELL_MAX_CUSTOM_COMMANDS;
         i++)
    {
        g_shell_custom_commands[i].registered =
            0;

        g_shell_custom_commands[i].command[0] =
            '\0';

        g_shell_custom_commands[i].provider[0] =
            '\0';
    }


    /*
     * Initialize kernel interface state.
     */

    g_shell_kernel.initialized = 0;
    g_shell_kernel.connected = 0;
    g_shell_kernel.process_id = 0;


    /*
     * Initialize process interface state.
     */

    g_shell_process.initialized = 0;
    g_shell_process.process_id = 0;


    g_shell.initialized = 1;

    g_shell.state =
        WD_SHELL_STATE_READY;

    return WD_KRNL_SUCCESS;
}


/*
 * Shell initialization validation.
 */

static uint32_t wd_shell_validate_initialization(
    void
)
{
    if (!g_shell.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_shell.state !=
            WD_SHELL_STATE_READY &&
        g_shell.state !=
            WD_SHELL_STATE_RUNNING)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_shell.input_buffer[0] != '\0')
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_shell.execution_arguments[0] != '\0')
    {
        return WD_KRNL_INIT_FAILED;
    }

    return WD_KRNL_SUCCESS;
}


/*
 * Parser cleanup.
 */

static void wd_shell_parser_clear(
    WD_SHELL_COMMAND* command
)
{
    if (command == 0)
    {
        return;
    }

    command->command[0] = '\0';

    command->argument_count = 0;

    for (uint32_t i = 0;
         i < WD_SHELL_MAX_ARGUMENTS;
         i++)
    {
        command->arguments[i][0] =
            '\0';
    }
}


/*
 * Command parser.
 */

static uint32_t wd_shell_parse_command(
    const char* input,
    WD_SHELL_COMMAND* command
)
{
    uint32_t input_index = 0;
    uint32_t output_index = 0;
    uint32_t argument_index = 0;

    if (input == 0 ||
        command == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    wd_shell_parser_clear(command);


    /*
     * Skip leading whitespace.
     */

    while (input[input_index] == ' ' ||
           input[input_index] == '\t')
    {
        input_index++;
    }


    /*
     * Empty input.
     */

    if (input[input_index] == '\0')
    {
        return WD_KRNL_SUCCESS;
    }


    /*
     * Parse command name.
     */

    while (input[input_index] != '\0' &&
           input[input_index] != ' ' &&
           input[input_index] != '\t')
    {
        if (output_index >=
            WD_SHELL_MAX_ARGUMENT_LENGTH - 1)
        {
            return WD_KRNL_INVALID_ARGUMENT;
        }

        command->command[output_index++] =
            input[input_index++];
    }

    command->command[output_index] =
        '\0';


    /*
     * Parse arguments.
     */

    while (input[input_index] != '\0')
    {
        while (input[input_index] == ' ' ||
               input[input_index] == '\t')
        {
            input_index++;
        }

        if (input[input_index] == '\0')
        {
            break;
        }

        if (argument_index >=
            WD_SHELL_MAX_ARGUMENTS)
        {
            return WD_KRNL_INVALID_ARGUMENT;
        }

        output_index = 0;

        while (input[input_index] != '\0' &&
               input[input_index] != ' ' &&
               input[input_index] != '\t')
        {
            if (output_index >=
                WD_SHELL_MAX_ARGUMENT_LENGTH - 1)
            {
                return WD_KRNL_INVALID_ARGUMENT;
            }

            command->arguments[
                argument_index
            ][output_index++] =
                input[input_index++];

        }

        command->arguments[
            argument_index
        ][output_index] = '\0';

        argument_index++;
    }

    command->argument_count =
        argument_index;

    return WD_KRNL_SUCCESS;
}


/*
 * Empty command check.
 */

static uint8_t wd_shell_command_is_empty(
    const WD_SHELL_COMMAND* command
)
{
    if (command == 0)
    {
        return 1;
    }

    if (command->command[0] == '\0')
    {
        return 1;
    }

    return 0;
}


/*
 * Identify built-in commands.
 */

static WD_SHELL_COMMAND_ID
wd_shell_identify_builtin(
    const char* command
)
{
    if (command == 0)
    {
        return WD_SHELL_COMMAND_UNKNOWN;
    }

    if (strcmp(
            command,
            WD_SHELL_COMMAND_LNCH) == 0)
    {
        return WD_SHELL_COMMAND_LNCH_ID;
    }

    if (strcmp(
            command,
            WD_SHELL_COMMAND_DIR) == 0)
    {
        return WD_SHELL_COMMAND_DIR_ID;
    }

    if (strcmp(
            command,
            WD_SHELL_COMMAND_SNAP) == 0)
    {
        return WD_SHELL_COMMAND_SNAP_ID;
    }

    if (strcmp(
            command,
            WD_SHELL_COMMAND_WHO) == 0)
    {
        return WD_SHELL_COMMAND_WHO_ID;
    }

    if (strcmp(
            command,
            WD_SHELL_COMMAND_REQ) == 0)
    {
        return WD_SHELL_COMMAND_REQ_ID;
    }

    if (strcmp(
            command,
            WD_SHELL_COMMAND_EXIT) == 0)
    {
        return WD_SHELL_COMMAND_EXIT_ID;
    }

    return WD_SHELL_COMMAND_UNKNOWN;
}


/*
 * lnch
 *
 * Actual service/process startup will be
 * connected later.
 */

static uint32_t wd_shell_command_lnch(
    const WD_SHELL_COMMAND* command
)
{
    if (command == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    if (command->argument_count < 1)
    {
        printf(
            "Usage: lnch <name>\n"
        );

        return WD_KRNL_INVALID_ARGUMENT;
    }

    printf(
        "[LNCH] Requested launch: %s\n",
        command->arguments[0]
    );

    printf(
        "[LNCH] Process/service launch "
        "interface is not connected yet.\n"
    );

    return WD_KRNL_SUCCESS;
}


/*
 * dir
 */

static uint32_t wd_shell_command_dir(
    const WD_SHELL_COMMAND* command
)
{
    if (command == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    if (command->argument_count < 1)
    {
        printf(
            "Usage: dir <path>\n"
        );

        return WD_KRNL_INVALID_ARGUMENT;
    }

    if (strlen(
            command->arguments[0]) >=
        WD_SHELL_MAX_DIRECTORY)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    strcpy(
        g_shell.current_directory,
        command->arguments[0]
    );

    printf(
        "Current directory: %s\n",
        g_shell.current_directory
    );

    return WD_KRNL_SUCCESS;
}


/*
 * snap
 */

static uint32_t wd_shell_command_snap(
    const WD_SHELL_COMMAND* command
)
{
    if (command == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    printf(
        "[SNAP] System snapshot requested.\n"
    );

    printf(
        "[SNAP] Snapshot subsystem is not "
        "connected yet.\n"
    );

    return WD_KRNL_SUCCESS;
}


/*
 * who
 */

static uint32_t wd_shell_command_who(
    const WD_SHELL_COMMAND* command
)
{
    if (command == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    printf("\n");

    printf(
        "WDSYS Worker Drone System\n"
    );

    printf(
        "Init Host Version: %u\n",
        WD_INIT_VERSION
    );

    printf(
        "Shell Version: %u\n",
        WD_SHELL_VERSION
    );

    printf(
        "Shell State: %u\n",
        g_shell.state
    );

    printf(
        "Kernel communication: %s\n",
        g_shell_kernel.connected
            ? "connected"
            : "pending"
    );

    printf(
        "Service manager: pending\n"
    );

    printf(
        "Custom commands: %u\n",
        g_shell_custom_command_count
    );

    printf(
        "Current directory: %s\n",
        g_shell.current_directory
    );

    printf("\n");

    return WD_KRNL_SUCCESS;
}


/*
 * req
 */

static uint32_t wd_shell_command_req(
    const WD_SHELL_COMMAND* command
)
{
    if (command == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    if (command->argument_count < 1)
    {
        printf(
            "Usage: req <object>\n"
        );

        return WD_KRNL_INVALID_ARGUMENT;
    }

    printf(
        "[REQ] Requesting object: %s\n",
        command->arguments[0]
    );

    printf(
        "[REQ] Request routing is not "
        "connected yet.\n"
    );

    return WD_KRNL_SUCCESS;
}


/*
 * exit
 */

static uint32_t wd_shell_command_exit(
    const WD_SHELL_COMMAND* command
)
{
    if (command == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    printf(
        "Shutting down shell...\n"
    );

    g_shell.running = 0;

    return WD_KRNL_SUCCESS;
}


/*
 * Execute a built-in command.
 */

static uint32_t wd_shell_execute_builtin(
    const WD_SHELL_COMMAND* command
)
{
    WD_SHELL_COMMAND_ID command_id;

    if (command == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    command_id =
        wd_shell_identify_builtin(
            command->command
        );

    switch (command_id)
    {
        case WD_SHELL_COMMAND_LNCH_ID:
            return wd_shell_command_lnch(
                command
            );

        case WD_SHELL_COMMAND_DIR_ID:
            return wd_shell_command_dir(
                command
            );

        case WD_SHELL_COMMAND_SNAP_ID:
            return wd_shell_command_snap(
                command
            );

        case WD_SHELL_COMMAND_WHO_ID:
            return wd_shell_command_who(
                command
            );

        case WD_SHELL_COMMAND_REQ_ID:
            return wd_shell_command_req(
                command
            );

        case WD_SHELL_COMMAND_EXIT_ID:
            return wd_shell_command_exit(
                command
            );

        case WD_SHELL_COMMAND_UNKNOWN:
        default:
            return WD_KRNL_INVALID_ARGUMENT;
    }
}


/*
 * Custom command registration.
 */

static uint32_t wd_shell_register_custom_command(
    const char* command,
    const char* provider
)
{
    uint32_t i;

    if (command == 0 ||
        provider == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    if (command[0] == '\0' ||
        provider[0] == '\0')
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    for (i = 0;
         i < g_shell_custom_command_count;
         i++)
    {
        if (strcmp(
                g_shell_custom_commands[i].command,
                command) == 0)
        {
            return WD_KRNL_INVALID_ARGUMENT;
        }
    }

    if (g_shell_custom_command_count >=
        WD_SHELL_MAX_CUSTOM_COMMANDS)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    strncpy(
        g_shell_custom_commands[
            g_shell_custom_command_count
        ].command,

        command,

        WD_SHELL_MAX_COMMAND_NAME - 1
    );

    g_shell_custom_commands[
        g_shell_custom_command_count
    ].command[
        WD_SHELL_MAX_COMMAND_NAME - 1
    ] = '\0';


    strncpy(
        g_shell_custom_commands[
            g_shell_custom_command_count
        ].provider,

        provider,

        WD_SHELL_MAX_PROVIDER_NAME - 1
    );

    g_shell_custom_commands[
        g_shell_custom_command_count
    ].provider[
        WD_SHELL_MAX_PROVIDER_NAME - 1
    ] = '\0';


    g_shell_custom_commands[
        g_shell_custom_command_count
    ].registered = 1;

    g_shell_custom_command_count++;

    return WD_KRNL_SUCCESS;
}


/*
 * Find custom command.
 */

static const WD_SHELL_CUSTOM_COMMAND*
wd_shell_find_custom_command(
    const char* command
)
{
    if (command == 0)
    {
        return 0;
    }

    for (uint32_t i = 0;
         i < g_shell_custom_command_count;
         i++)
    {
        if (!g_shell_custom_commands[i].registered)
        {
            continue;
        }

        if (strcmp(
                g_shell_custom_commands[i].command,
                command) == 0)
        {
            return &g_shell_custom_commands[i];
        }
    }

    return 0;
}


/*
 * Route custom command.
 */

static uint32_t wd_shell_route_custom_command(
    const WD_SHELL_COMMAND* command
)
{
    if (command == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    if (wd_shell_find_custom_command(
            command->command) == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    return wd_shell_launch_custom_provider(
        command
    );
}


/*
 * Execute any command.
 */

static uint32_t wd_shell_execute_command(
    const WD_SHELL_COMMAND* command
)
{
    WD_SHELL_COMMAND_ID command_id;
    uint32_t result;

    if (command == 0)
    {
        return wd_shell_set_error(
            WD_SHELL_ERROR_INVALID_ARGUMENT,
            WD_KRNL_INVALID_ARGUMENT
        );
    }

    wd_shell_clear_error();

    command_id =
        wd_shell_identify_builtin(
            command->command
        );

    if (command_id !=
        WD_SHELL_COMMAND_UNKNOWN)
    {
        result =
            wd_shell_execute_builtin(
                command
            );

        if (result != WD_KRNL_SUCCESS)
        {
            return wd_shell_set_error(
                wd_shell_translate_error(
                    result
                ),
                result
            );
        }

        return WD_KRNL_SUCCESS;
    }


    result =
        wd_shell_route_custom_command(
            command
        );

    if (result != WD_KRNL_SUCCESS)
    {
        return wd_shell_set_error(
            WD_SHELL_ERROR_UNKNOWN_COMMAND,
            result
        );
    }

    return WD_KRNL_SUCCESS;
}


/*
 * Kernel request bridge.
 *
 * The real M22 IPC transport will be connected
 * here when the kernel-side interface is ready.
 */

static uint32_t wd_shell_kernel_request(
    const WD_SHELL_KERNEL_REQUEST* request,
    WD_SHELL_KERNEL_RESPONSE* response
)
{
    if (request == 0 ||
        response == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    response->result =
        WD_KRNL_INVALID_ARGUMENT;

    response->output_size = 0;


    /*
     * IPC transport is intentionally not
     * faked here.
     */

    return WD_KRNL_SUCCESS;
}


/*
 * Kernel interface initialization.
 */

static uint32_t wd_shell_kernel_initialize(
    uint32_t process_id
)
{
    g_shell_kernel.initialized = 0;
    g_shell_kernel.connected = 0;
    g_shell_kernel.process_id =
        process_id;

    if (process_id == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    /*
     * Real M22 IPC connection will be
     * established here later.
     */

    g_shell_kernel.connected = 1;
    g_shell_kernel.initialized = 1;

    return WD_KRNL_SUCCESS;
}


/*
 * Kernel status request.
 */

static uint32_t wd_shell_kernel_get_status(
    void
)
{
    WD_SHELL_KERNEL_REQUEST request;
    WD_SHELL_KERNEL_RESPONSE response;

    request.operation =
        WD_SHELL_KERNEL_OPERATION_GET_STATUS;

    request.process_id =
        g_shell_kernel.process_id;

    request.input = 0;
    request.input_size = 0;

    request.output = 0;
    request.output_size = 0;

    return wd_shell_kernel_request(
        &request,
        &response
    );
}


/*
 * Kernel directory request.
 */

static uint32_t wd_shell_kernel_set_directory(
    const char* path
)
{
    WD_SHELL_KERNEL_REQUEST request;
    WD_SHELL_KERNEL_RESPONSE response;

    if (path == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    request.operation =
        WD_SHELL_KERNEL_OPERATION_SET_DIRECTORY;

    request.process_id =
        g_shell_kernel.process_id;

    request.input = path;

    request.input_size =
        (uint32_t)(strlen(path) + 1);

    request.output = 0;
    request.output_size = 0;

    return wd_shell_kernel_request(
        &request,
        &response
    );
}


/*
 * Kernel launch request.
 */

static uint32_t wd_shell_kernel_launch(
    const char* executable
)
{
    WD_SHELL_KERNEL_REQUEST request;
    WD_SHELL_KERNEL_RESPONSE response;

    if (executable == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    request.operation =
        WD_SHELL_KERNEL_OPERATION_LAUNCH;

    request.process_id =
        g_shell_kernel.process_id;

    request.input = executable;

    request.input_size =
        (uint32_t)(strlen(executable) + 1);

    request.output = 0;
    request.output_size = 0;

    return wd_shell_kernel_request(
        &request,
        &response
    );
}


/*
 * Process interface initialization.
 */

static uint32_t wd_shell_process_initialize(
    uint32_t process_id
)
{
    g_shell_process.initialized = 0;

    g_shell_process.process_id =
        process_id;

    if (process_id == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    g_shell_process.initialized = 1;

    return WD_KRNL_SUCCESS;
}


/*
 * Process launch interface.
 *
 * This is deliberately NOT starting services yet.
 */

static uint32_t wd_shell_process_launch(
    const char* executable,
    const char* arguments,
    WD_SHELL_PROCESS_RESULT* result
)
{
    if (!g_shell_process.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (executable == 0 ||
        result == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    result->result =
        WD_KRNL_INVALID_ARGUMENT;

    result->process_id = 0;


    /*
     * Actual M20 process-launch integration
     * will be connected here later.
     */

    return WD_KRNL_SUCCESS;
}


/*
 * Launch custom command provider.
 */

static uint32_t wd_shell_launch_custom_provider(
    const WD_SHELL_COMMAND* command
)
{
    const WD_SHELL_CUSTOM_COMMAND*
        custom_command;

    WD_SHELL_PROCESS_RESULT
        process_result;

    uint32_t result;


    if (command == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    custom_command =
        wd_shell_find_custom_command(
            command->command
        );

    if (custom_command == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    if (!custom_command->registered)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    if (custom_command->provider[0] == '\0')
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }


    result =
        wd_shell_build_arguments(
            command,
            g_shell.execution_arguments,
            WD_SHELL_MAX_INPUT
        );

    if (result != WD_KRNL_SUCCESS)
    {
        return result;
    }


    result =
        wd_shell_process_launch(
            custom_command->provider,
            g_shell.execution_arguments,
            &process_result
        );

    if (result != WD_KRNL_SUCCESS)
    {
        return result;
    }

    if (process_result.result !=
        WD_KRNL_SUCCESS)
    {
        return process_result.result;
    }

    g_shell.error_status.process_id =
        process_result.process_id;

    return WD_KRNL_SUCCESS;
}


/*
 * Build command arguments.
 */

static uint32_t wd_shell_build_arguments(
    const WD_SHELL_COMMAND* command,
    char* output,
    uint32_t output_size
)
{
    uint32_t output_index = 0;

    if (command == 0 ||
        output == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    if (output_size == 0)
    {
        return WD_KRNL_INVALID_ARGUMENT;
    }

    output[0] = '\0';


    for (uint32_t i = 1;
         i < command->argument_count;
         i++)
    {
        uint32_t argument_length =
            (uint32_t)strlen(
                command->arguments[i]
            );


        if (output_index != 0)
        {
            if (output_index + 1 >=
                output_size)
            {
                return WD_KRNL_INVALID_ARGUMENT;
            }

            output[output_index++] =
                ' ';
        }


        if (output_index +
                argument_length >=
            output_size)
        {
            return WD_KRNL_INVALID_ARGUMENT;
        }


        memcpy(
            &output[output_index],
            command->arguments[i],
            argument_length
        );

        output_index +=
            argument_length;
    }


    output[output_index] =
        '\0';

    return WD_KRNL_SUCCESS;
}


/*
 * Translate kernel result to shell error.
 */

static WD_SHELL_ERROR
wd_shell_translate_error(
    uint32_t result
)
{
    switch (result)
    {
        case WD_KRNL_SUCCESS:
            return WD_SHELL_ERROR_NONE;

        case WD_KRNL_INVALID_ARGUMENT:
            return WD_SHELL_ERROR_INVALID_ARGUMENT;

        case WD_KRNL_INIT_FAILED:
            return WD_SHELL_ERROR_NOT_INITIALIZED;

        default:
            return WD_SHELL_ERROR_INTERNAL;
    }
}


/*
 * Set shell error.
 */

static uint32_t wd_shell_set_error(
    WD_SHELL_ERROR error,
    uint32_t kernel_result
)
{
    g_shell.error_status.error =
        error;

    g_shell.error_status.kernel_result =
        kernel_result;

    return kernel_result;
}


/*
 * Clear shell error.
 */

static void wd_shell_clear_error(
    void
)
{
    g_shell.error_status.error =
        WD_SHELL_ERROR_NONE;

    g_shell.error_status.kernel_result =
        WD_KRNL_SUCCESS;

    g_shell.error_status.process_id =
        0;
}


/*
 * Error messages.
 */

static const char* wd_shell_error_message(
    WD_SHELL_ERROR error
)
{
    switch (error)
    {
        case WD_SHELL_ERROR_NONE:
            return "No error.";

        case WD_SHELL_ERROR_UNKNOWN_COMMAND:
            return "Unknown command.";

        case WD_SHELL_ERROR_INVALID_ARGUMENT:
            return "Invalid argument.";

        case WD_SHELL_ERROR_COMMAND_TOO_LONG:
            return "Command is too long.";

        case WD_SHELL_ERROR_PROVIDER_NOT_FOUND:
            return "Command provider not found.";

        case WD_SHELL_ERROR_PROCESS_LAUNCH_FAILED:
            return "Process launch failed.";

        case WD_SHELL_ERROR_KERNEL_COMMUNICATION:
            return "Kernel communication failed.";

        case WD_SHELL_ERROR_NOT_INITIALIZED:
            return "Shell is not initialized.";

        case WD_SHELL_ERROR_INTERNAL:
        default:
            return "Internal shell error.";
    }
}


/*
 * Main shell runtime.
 */

static void wd_shell_runtime(
    void
)
{
    uint32_t result;

    g_shell.state =
        WD_SHELL_STATE_RUNNING;

    g_shell.running = 1;


    printf("\n");

    printf(
        "====================================\n"
    );

    printf(
        " WDSYS Worker Drone System Shell\n"
    );

    printf(
        " Shell Version %u\n",
        WD_SHELL_VERSION
    );

    printf(
        "====================================\n"
    );

    printf(
        "Type 'who' for system information.\n"
    );

    printf(
        "Type 'exit' to stop the shell.\n"
    );

    printf("\n");


    while (g_shell.running)
    {
        g_shell.input_buffer[0] =
            '\0';


        printf(
            "WDSYS:%s> ",
            g_shell.current_directory
        );

        fflush(stdout);


        if (fgets(
                g_shell.input_buffer,
                WD_SHELL_MAX_INPUT,
                stdin) == 0)
        {
            printf("\n");

            printf(
                "[SHELL] Input stream closed. "
                "Stopping shell.\n"
            );

            g_shell.running = 0;

            break;
        }


        /*
         * Remove newline.
         */

        for (uint32_t i = 0;
             g_shell.input_buffer[i] != '\0';
             i++)
        {
            if (g_shell.input_buffer[i] == '\n' ||
                g_shell.input_buffer[i] == '\r')
            {
                g_shell.input_buffer[i] =
                    '\0';

                break;
            }
        }


        result =
            wd_shell_parse_command(
                g_shell.input_buffer,
                &g_shell.parsed_command
            );


        if (result != WD_KRNL_SUCCESS)
        {
            wd_shell_set_error(
                wd_shell_translate_error(
                    result
                ),
                result
            );

            printf(
                "Error: %s\n",
                wd_shell_error_message(
                    g_shell.error_status.error
                )
            );

            continue;
        }


        if (wd_shell_command_is_empty(
                &g_shell.parsed_command))
        {
            continue;
        }


        result =
            wd_shell_execute_command(
                &g_shell.parsed_command
            );


        if (result != WD_KRNL_SUCCESS)
        {
            wd_shell_set_error(
                wd_shell_translate_error(
                    result
                ),
                result
            );

            printf(
                "Error: %s\n",
                wd_shell_error_message(
                    g_shell.error_status.error
                )
            );
        }
    }


    g_shell.state =
        WD_SHELL_STATE_STOPPED;
}


/*
 * wdinithost entry.
 */

static uint32_t wdinithost_main(
    void
)
{
    uint32_t result;


    result =
        wd_shell_initialize();

    if (result != WD_KRNL_SUCCESS)
    {
        return result;
    }


    result =
        wd_shell_validate_initialization();

    if (result != WD_KRNL_SUCCESS)
    {
        return result;
    }


    /*
     * The shell can run independently while
     * the real kernel/service interfaces are
     * still being completed.
     */

    wd_shell_runtime();


    return WD_KRNL_SUCCESS;
}


/*
 * Program entry.
 */

int main(
    void
)
{
    uint32_t result;

    result =
        wdinithost_main();

    if (result != WD_KRNL_SUCCESS)
    {
        printf(
            "WDSYS init host failed. "
            "Error code: %u\n",
            result
        );

        return 1;
    }

    return 0;
}