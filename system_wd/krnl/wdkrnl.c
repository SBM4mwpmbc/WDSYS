#include <stdint.h>
#include <stdio.h>

#define WD_KERNEL_MAJOR 1
#define WD_KERNEL_MINOR 0
#define WD_KERNEL_PATCH 0

#define WD_KRNL_SUCCESS        0
#define WD_KRNL_INIT_FAILED    1
#define WD_KRNL_FATAL_ERROR    2

#define WD_MEMORY_PAGE_SIZE 4096
#define WD_KRNL_MAX_INTERRUPTS 256
#define WD_STORAGE_MAX_DEVICES 16
#define WD_EXEC_MAX_PATH 256
#define WD_KRNL_EXCEPTION_COUNT 32
#define WD_MEMORY_MAX_REGIONS 64
#define WD_MEMORY_MAX_ALLOCATIONS 128
#define WD_IDT_ENTRY_COUNT 256
#define WD_INTERRUPT_TIMER 32
#define WD_CPU_VENDOR_MAX_LENGTH 13
#define WD_CPU_BRAND_MAX_LENGTH 49
#define WD_HARDWARE_MAX_DEVICES 128
#define WD_HARDWARE_NAME_LENGTH 64
#define WD_STORAGE_SECTOR_SIZE 512
#define WD_STORAGE_DRIVER_NAME_LENGTH 32
#define WD_STORAGE_MAX_DRIVERS 32
#define WD_FS_MAX_FILES 10000
#define WD_FS_MAX_PATH 1000
#define WD_FS_MAX_NAME 1000
#define WD_PE_DOS_SIGNATURE 0x5A4D
#define WD_PE_SIGNATURE 0x00004550
#define WD_PE_MACHINE_X86 0x014C
#define WD_PE_MACHINE_X86_64 0x8664
#define WD_PE_MAX_SECTIONS 96
#define WD_PE_SECTION_NAME_LENGTH 8
#define WD_PROCESS_MAX_PROCESSES 864
#define WD_PROCESS_MAX_NAME 64
#define WD_PROCESS_STACK_SIZE (16 * WD_MEMORY_PAGE_SIZE)
#define WD_THREAD_MAX_THREADS 1024
#define WD_THREAD_MAX_NAME 64
#define WD_IPC_MAX_ENDPOINTS 256
#define WD_IPC_MAX_MESSAGES 256
#define WD_IPC_MAX_MESSAGE_DATA 256
#define WD_IPC_QUEUE_SIZE 16
#define WD_IPC_MAX_QUEUES 256
#define WD_IPC_MAX_CHANNELS 256
#define WD_IPC_MAX_PERMISSION_SETS 256
#define WD_DEVICE_MAX_DEVICES 256
#define WD_DEVICE_MAX_NAME 64
#define WD_DEVICE_MAX_RESOURCES 16
#define WD_DEVICE_MAX_DRIVERS 128
#define WD_DEVICE_MAX_DRIVER_NAME 64
#define WD_DEVICE_ERROR_NONE 0
#define WD_DEVICE_ERROR_GENERAL 1
#define WD_DEVICE_ERROR_INITIALIZATION 2
#define WD_DEVICE_ERROR_DRIVER 3
#define WD_DEVICE_ERROR_RESOURCE 4
#define WD_DEVICE_ERROR_HARDWARE 5
#define WD_DEVICE_ERROR_TIMEOUT 6
#define WD_DEVICE_ERROR_NOT_PRESENT 7
#define WD_DEVICE_ERROR_UNSUPPORTED 8
#define WD_INIT_HANDOFF_VERSION 1
#define WD_INIT_PROCESS_NAME "wdinithost.exe"
#define WD_INIT_VERSION 1
#define WD_INIT_MAX_RESTARTS 3

typedef uint16_t WD_CHAR16;

typedef struct
{
    void* reset;
    void* output_string;
    void* test_string;
    void* query_mode;
    void* set_mode;
    void* set_attribute;
    void* clear_screen;
    void* set_cursor_position;
    void* enable_cursor;
    void* mode;
} WD_EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct
{
    uint8_t header[24];

    void* firmware_vendor;
    uint32_t firmware_revision;

    void* console_in_handle;
    void* con_in;

    void* console_out_handle;
    WD_EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* con_out;

} WD_EFI_SYSTEM_TABLE;

static WD_EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* g_wd_console = 0;



typedef enum
{
    WD_INIT_OPERATION_NONE = 0,
    WD_INIT_OPERATION_HELLO,
    WD_INIT_OPERATION_GET_STATUS,
    WD_INIT_OPERATION_GET_HANDOFF,
    WD_INIT_OPERATION_HEARTBEAT,
    WD_INIT_OPERATION_SHUTDOWN
} WD_INIT_OPERATION;

typedef enum
{
    WD_INIT_STATE_NONE = 0,
    WD_INIT_STATE_STARTING,
    WD_INIT_STATE_READY,
    WD_INIT_STATE_FAILED,
    WD_INIT_STATE_TERMINATED
} WD_INIT_STATE;

typedef enum
{
    WD_INIT_HANDOFF_STATE_NONE = 0,
    WD_INIT_HANDOFF_STATE_READY,
    WD_INIT_HANDOFF_STATE_TRANSFERRED,
    WD_INIT_HANDOFF_STATE_FAILED
} WD_INIT_HANDOFF_STATE;

typedef enum
{
    WD_RECOVERY_ACTION_NONE = 0,
    WD_RECOVERY_ACTION_RETRY,
    WD_RECOVERY_ACTION_RECOVER,
    WD_RECOVERY_ACTION_DEGRADE,
    WD_RECOVERY_ACTION_PANIC
} WD_RECOVERY_ACTION;

typedef enum
{
    WD_RECOVERY_ERROR_NONE = 0,
    WD_RECOVERY_ERROR_MEMORY,
    WD_RECOVERY_ERROR_PROCESS,
    WD_RECOVERY_ERROR_THREAD,
    WD_RECOVERY_ERROR_INTERRUPT,
    WD_RECOVERY_ERROR_DEVICE,
    WD_RECOVERY_ERROR_IPC,
    WD_RECOVERY_ERROR_STORAGE,
    WD_RECOVERY_ERROR_FILESYSTEM,
    WD_RECOVERY_ERROR_KERNEL,
    WD_RECOVERY_ERROR_HEALTH
} WD_RECOVERY_ERROR;

typedef enum
{
    WD_HEALTH_STATE_UNKNOWN = 0,
    WD_HEALTH_STATE_HEALTHY,
    WD_HEALTH_STATE_DEGRADED,
    WD_HEALTH_STATE_FAILED
} WD_HEALTH_STATE;

typedef enum
{
    WD_RECOVERY_STATE_NORMAL = 0,
    WD_RECOVERY_STATE_DEGRADED,
    WD_RECOVERY_STATE_RECOVERING,
    WD_RECOVERY_STATE_FAILED,
    WD_RECOVERY_STATE_PANIC
} WD_RECOVERY_STATE;

typedef enum
{
    WD_POWER_OPERATION_SLEEP = 0,
    WD_POWER_OPERATION_CHARGING_SLEEP,
    WD_POWER_OPERATION_SHUTDOWN,
    WD_POWER_OPERATION_REBOOT,
    WD_POWER_OPERATION_GET_STATE,
    WD_POWER_OPERATION_GET_STATUS
} WD_POWER_OPERATION;

typedef enum
{
    WD_DEVICE_POWER_ON = 0,
    WD_DEVICE_POWER_IDLE,
    WD_DEVICE_POWER_SLEEP,
    WD_DEVICE_POWER_OFF
} WD_DEVICE_POWER_STATE;

typedef enum
{
    WD_POWER_STATE_ON = 0,
    WD_POWER_STATE_IDLE,
    WD_POWER_STATE_SLEEP,
    WD_POWER_STATE_SHUTDOWN,
    WD_POWER_STATE_REBOOT
} WD_POWER_STATE;

typedef enum
{
    WD_DEVICE_OPERATION_GET = 0,
    WD_DEVICE_OPERATION_ENABLE,
    WD_DEVICE_OPERATION_DISABLE,
    WD_DEVICE_OPERATION_ENUMERATE,
    WD_DEVICE_OPERATION_GET_STATE,
    WD_DEVICE_OPERATION_GET_TYPE,
    WD_DEVICE_OPERATION_GET_RESOURCE,
    WD_DEVICE_OPERATION_GET_ERROR,
    WD_DEVICE_OPERATION_RECOVER
} WD_DEVICE_OPERATION;

typedef enum
{
    WD_DEVICE_RESOURCE_NONE = 0,
    WD_DEVICE_RESOURCE_MEMORY,
    WD_DEVICE_RESOURCE_IO,
    WD_DEVICE_RESOURCE_INTERRUPT,
    WD_DEVICE_RESOURCE_DMA
} WD_DEVICE_RESOURCE_TYPE;

typedef struct // man fuck this shit
{
    WD_DEVICE_RESOURCE_TYPE type;
    uint64_t start;
    uint64_t length;
    uint32_t flags;
    uint8_t assigned;
} WD_DEVICE_RESOURCE;

WD_DEVICE_RESOURCE resources[WD_DEVICE_MAX_RESOURCES];
uint32_t resource_count;

typedef enum
{
    WD_IPC_PERMISSION_NONE = 0,
    WD_IPC_PERMISSION_SEND,
    WD_IPC_PERMISSION_RECEIVE,
    WD_IPC_PERMISSION_CONNECT,
    WD_IPC_PERMISSION_CLOSE

} WD_IPC_PERMISSION;

typedef enum
{
    WD_IPC_WAIT_NONE = 0,
    WD_IPC_WAIT_MESSAGE,
    WD_IPC_WAIT_CHANNEL

} WD_IPC_WAIT_TYPE;

typedef enum
{
    WD_IPC_CHANNEL_STATE_UNUSED = 0,
    WD_IPC_CHANNEL_STATE_CREATED,
    WD_IPC_CHANNEL_STATE_CONNECTED,
    WD_IPC_CHANNEL_STATE_CLOSED,
    WD_IPC_CHANNEL_STATE_ERROR

} WD_IPC_CHANNEL_STATE;

typedef enum
{
    WD_IPC_MESSAGE_NONE = 0,
    WD_IPC_MESSAGE_DATA,
    WD_IPC_MESSAGE_REQUEST,
    WD_IPC_MESSAGE_RESPONSE,
    WD_IPC_MESSAGE_EVENT

} WD_IPC_MESSAGE_TYPE;

typedef enum
{
    WD_THREAD_STATE_UNUSED = 0,
    WD_THREAD_STATE_CREATED,
    WD_THREAD_STATE_READY,
    WD_THREAD_STATE_RUNNING,
    WD_THREAD_STATE_BLOCKED,
    WD_THREAD_STATE_TERMINATED,
    WD_THREAD_STATE_ERROR

} WD_THREAD_STATE;

typedef enum
{
    WD_PROCESS_STATE_UNUSED = 0,
    WD_PROCESS_STATE_CREATED,
    WD_PROCESS_STATE_READY,
    WD_PROCESS_STATE_RUNNING,
    WD_PROCESS_STATE_TERMINATED,
    WD_PROCESS_STATE_ERROR
} WD_PROCESS_STATE;

typedef enum
{
    WD_FS_TYPE_UNKNOWN = 0,
    WD_FS_TYPE_FILE,
    WD_FS_TYPE_DIRECTORY
} WD_FS_ENTRY_TYPE;

typedef enum
{
    WD_DEVICE_STATE_UNUSED = 0,
    WD_DEVICE_STATE_REGISTERED,
    WD_DEVICE_STATE_INITIALIZING,
    WD_DEVICE_STATE_READY,
    WD_DEVICE_STATE_DISABLED,
    WD_DEVICE_STATE_ERROR

} WD_DEVICE_STATE;

typedef enum
{
    WD_STORAGE_TYPE_UNKNOWN = 0,
    WD_STORAGE_TYPE_SATA,
    WD_STORAGE_TYPE_NVME,
    WD_STORAGE_TYPE_USB,
    WD_STORAGE_TYPE_VIRTUAL
} WD_STORAGE_TYPE;

typedef enum
{
    WD_KRNL_STATE_OFF = 0,
    WD_KRNL_STATE_INITIALIZING,
    WD_KRNL_STATE_RUNNING,
    WD_KRNL_STATE_ERROR
} WD_KRNL_STATE;

typedef enum
{
    WD_KRNL_ERROR_NONE = 0,
    WD_KRNL_ERROR_INITIALIZATION,
    WD_KRNL_ERROR_EXCEPTION,
    WD_KRNL_ERROR_FATAL
} WD_KRNL_ERROR_CODE;

typedef enum
{
    WD_EXCEPTION_DIVIDE_ERROR = 0,
    WD_EXCEPTION_DEBUG,
    WD_EXCEPTION_NON_MASKABLE_INTERRUPT,
    WD_EXCEPTION_BREAKPOINT,
    WD_EXCEPTION_OVERFLOW,
    WD_EXCEPTION_BOUND_RANGE,
    WD_EXCEPTION_INVALID_OPCODE,
    WD_EXCEPTION_DEVICE_NOT_AVAILABLE,
    WD_EXCEPTION_DOUBLE_FAULT,
    WD_EXCEPTION_INVALID_TSS,
    WD_EXCEPTION_SEGMENT_NOT_PRESENT,
    WD_EXCEPTION_STACK_SEGMENT_FAULT,
    WD_EXCEPTION_GENERAL_PROTECTION_FAULT,
    WD_EXCEPTION_PAGE_FAULT,
    WD_EXCEPTION_RESERVED,
    WD_EXCEPTION_X87_FLOATING_POINT,
    WD_EXCEPTION_ALIGNMENT_CHECK,
    WD_EXCEPTION_MACHINE_CHECK,
    WD_EXCEPTION_SIMD_FLOATING_POINT,
    WD_EXCEPTION_VIRTUALIZATION,
    WD_EXCEPTION_CONTROL_PROTECTION,
    WD_EXCEPTION_RESERVED_22,
    WD_EXCEPTION_RESERVED_23,
    WD_EXCEPTION_RESERVED_24,
    WD_EXCEPTION_RESERVED_25,
    WD_EXCEPTION_RESERVED_26,
    WD_EXCEPTION_RESERVED_27,
    WD_EXCEPTION_HYPERVISOR_INJECTION,
    WD_EXCEPTION_VMM_COMMUNICATION,
    WD_EXCEPTION_SECURITY,
    WD_EXCEPTION_RESERVED_31
} WD_EXCEPTION_CODE;  

typedef enum
{
    WD_CPU_ARCH_UNKNOWN = 0,
    WD_CPU_ARCH_X86_64
} WD_CPU_ARCH;

typedef enum
{
    WD_HARDWARE_TYPE_UNKNOWN = 0,
    WD_HARDWARE_TYPE_CPU,
    WD_HARDWARE_TYPE_MEMORY,
    WD_HARDWARE_TYPE_STORAGE,
    WD_HARDWARE_TYPE_NETWORK,
    WD_HARDWARE_TYPE_DISPLAY,
    WD_HARDWARE_TYPE_USB,
    WD_HARDWARE_TYPE_PCI,
    WD_HARDWARE_TYPE_OTHER
} WD_HARDWARE_TYPE;

typedef uint32_t (*WD_STORAGE_READ)(
    uint32_t device_id,
    uint64_t lba,
    uint32_t sector_count,
    void* buffer
);

typedef uint32_t (*WD_STORAGE_WRITE)(
    uint32_t device_id,
    uint64_t lba,
    uint32_t sector_count,
    const void* buffer
);

typedef struct
{
    uint16_t e_magic;

    uint8_t reserved[58];

    uint32_t e_lfanew;

} WD_PE_DOS_HEADER;

typedef struct
{
    uint8_t initialized;
    uint8_t enabled;
    uint64_t heartbeat;
    uint64_t last_checked_heartbeat;
    uint32_t check_count;
    uint32_t failure_count;
} WD_WATCHDOG_STATUS;

static WD_WATCHDOG_STATUS g_watchdog_status;

typedef struct
{
    WD_HEALTH_STATE state;
    uint8_t initialized;
    uint64_t heartbeat;
    uint32_t check_count;
    uint32_t failure_count;
} WD_HEALTH_STATUS;

static WD_HEALTH_STATUS g_health_status;

static uint32_t g_process_count = 0;

static uint32_t g_current_process = 0;

static uint32_t g_thread_count = 0;

static uint32_t g_current_thread = 0;

typedef struct
{
    char vendor[WD_CPU_VENDOR_MAX_LENGTH];
    char brand[WD_CPU_BRAND_MAX_LENGTH];

    uint32_t maximum_basic_leaf;
    uint32_t maximum_extended_leaf;

    uint32_t family;
    uint32_t model;
    uint32_t stepping;

    uint32_t feature_ecx;
    uint32_t feature_edx;

    uint8_t cpuid_supported;
} WD_CPU_HARDWARE_INFO;

typedef struct
{
    uint32_t sender_id;
    uint32_t receiver_id;

    WD_IPC_MESSAGE_TYPE type;

    uint32_t size;

    uint8_t data[WD_IPC_MAX_MESSAGE_DATA];

    uint8_t valid;

} WD_IPC_MESSAGE;

typedef struct
{
    uint32_t id;

    uint32_t source_endpoint;
    uint32_t target_endpoint;

    uint32_t queue_id;

    WD_IPC_CHANNEL_STATE state;

    uint8_t active;

} WD_IPC_CHANNEL;

static WD_IPC_CHANNEL g_ipc_channels[WD_IPC_MAX_CHANNELS];

static uint32_t g_ipc_channel_count = 0;

typedef struct
{
    uint32_t id;

    uint32_t endpoint_id;

    WD_IPC_MESSAGE messages[WD_IPC_QUEUE_SIZE];

    uint32_t head;
    uint32_t tail;
    uint32_t count;

    uint8_t active;
} WD_IPC_QUEUE;

typedef struct
{
    uint32_t id;

    uint32_t process_id;
    uint32_t thread_id;

    uint8_t active;

} WD_IPC_ENDPOINT;

typedef struct
{
    uint32_t endpoint_id;

    uint8_t send;
    uint8_t receive;
    uint8_t connect;
    uint8_t close;

    uint8_t active;

} WD_IPC_PERMISSION_SET;

static WD_IPC_PERMISSION_SET g_ipc_permissions[WD_IPC_MAX_PERMISSION_SETS];

static uint32_t g_ipc_permission_count = 0;

typedef struct
{
    uint32_t id;

    WD_FS_ENTRY_TYPE type;

    uint64_t size;
    uint64_t storage_offset;

    uint8_t exists;
    uint8_t readable;
    uint8_t writable;

    char name[WD_FS_MAX_NAME];
    char path[WD_FS_MAX_PATH];
} WD_FS_ENTRY;

typedef struct
{
    uint32_t id;
    WD_HARDWARE_TYPE type;

    uint16_t vendor_id;
    uint16_t device_id;

    uint8_t present;
    uint8_t enabled;

    char name[WD_HARDWARE_NAME_LENGTH];
} WD_HARDWARE_DEVICE;

typedef struct
{
    WD_CPU_ARCH architecture;
    uint8_t long_mode;
    uint8_t initialized;
} WD_CPU_INFO;

typedef struct
{
    WD_POWER_STATE state;
    uint8_t initialized;
    uint8_t charging_mode;
    uint8_t transition_active;
} WD_POWER_STATUS;

static WD_POWER_STATUS g_power_status;

typedef struct
{
    uint64_t base;
    uint64_t size;
    uint8_t available;
} WD_MEMORY_REGION;

typedef struct
{
    uint64_t base;
    uint64_t size;
    uint8_t active;
} WD_MEMORY_ALLOCATION;

static WD_MEMORY_ALLOCATION g_memory_allocations[WD_MEMORY_MAX_ALLOCATIONS];

static uint32_t g_memory_allocation_count = 0;

typedef struct 
{
    uint32_t cpu_id;
    uint32_t cpu_features;

    uint64_t memory_size;

    uint8_t hardware_detected;
} WD_HARDWARE_INFO;

typedef struct 
{
    uint32_t id;
    uint64_t size;
    uint8_t available;
} WD_STORAGE_DEVICE;

typedef struct
{
    uint32_t id;

    WD_HARDWARE_TYPE type;

    WD_DEVICE_STATE state;

    uint16_t vendor_id;
    uint16_t device_id;

    uint8_t present;
    uint8_t enabled;
    uint8_t initialized;

    uint32_t error_code;
    uint32_t error_count;
    uint8_t error_recoverable;

    WD_DEVICE_POWER_STATE power_state;
    uint8_t power_management_supported;
    uint8_t wake_capable;
    uint8_t power_transition_active;

    char name[WD_DEVICE_MAX_NAME];

    WD_DEVICE_RESOURCE resources[WD_DEVICE_MAX_RESOURCES];
    uint32_t resource_count;

} WD_DEVICE;

typedef int (*WD_DEVICE_DRIVER_PROBE)(WD_DEVICE* device);
typedef int (*WD_DEVICE_DRIVER_REMOVE)(WD_DEVICE* device);
typedef int (*WD_DEVICE_DRIVER_ENABLE)(WD_DEVICE* device);
typedef int (*WD_DEVICE_DRIVER_DISABLE)(WD_DEVICE* device);
typedef int (*WD_DEVICE_DRIVER_POWER_SET)(WD_DEVICE* device, WD_DEVICE_POWER_STATE state);
typedef int (*WD_DEVICE_DRIVER_POWER_GET)(WD_DEVICE* device, WD_DEVICE_POWER_STATE* state);

static WD_DEVICE g_devices[WD_DEVICE_MAX_DEVICES];

static uint32_t g_device_count = 0;

static uint8_t g_device_management_initialized = 0;

typedef struct 
{
    uint32_t id;
    char name[WD_DEVICE_MAX_DRIVER_NAME];

    WD_HARDWARE_TYPE supported_type;

    WD_DEVICE_DRIVER_PROBE probe;
    WD_DEVICE_DRIVER_REMOVE remove;
    WD_DEVICE_DRIVER_ENABLE enable;
    WD_DEVICE_DRIVER_DISABLE disable;
    WD_DEVICE_DRIVER_POWER_SET power_set;
    WD_DEVICE_DRIVER_POWER_GET power_get;

    uint8_t registered;
    uint8_t bound;
    uint32_t bound_device_id;
} WD_DEVICE_DRIVER;

static WD_DEVICE_DRIVER g_device_drivers[WD_DEVICE_MAX_DRIVERS];

static uint32_t g_device_driver_count = 0;
static uint8_t g_device_driver_management_initialized = 0;

typedef struct
{
    char path[WD_EXEC_MAX_PATH];

    uint64_t load_address;
    uint64_t entry_address;
    uint64_t image_size;

    uint8_t loaded;
} WD_EXECUTABLE;

typedef struct
{
    uint64_t system_table;
    uint64_t memory_map;
    uint64_t memory_map_size;
    uint64_t memory_descriptor_size;

    uint64_t kernel_base;
    uint64_t kernel_size;

    uint8_t uefi_boot;
} WD_BOOT_INFO;

typedef struct
{
    WD_EXCEPTION_CODE code;

    uint64_t instruction_pointer;
    uint64_t stack_pointer;
    uint64_t error_code;

    uint8_t occurred;
} WD_EXCEPTION_INFO;

typedef struct
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t list;
    uint8_t type_attributes;
    uint16_t offset_middle;
    uint32_t offset_high;
    uint32_t reserved;
} WD_IDT_ENTRY;

typedef struct 
{
    uint16_t limit;
    uint64_t base;
} WD_IDT_POINTER;

typedef struct
{
    uint32_t id;

    WD_STORAGE_TYPE type;

    uint8_t initialized;
    uint8_t available;

    uint64_t sector_count;
    uint32_t sector_size;

    WD_STORAGE_READ read;
    WD_STORAGE_WRITE write;

    char name[WD_STORAGE_DRIVER_NAME_LENGTH];
} WD_STORAGE_DRIVER;

typedef struct
{
    uint16_t machine;

    uint16_t number_of_sections;

    uint32_t time_date_stamp;

    uint32_t pointer_to_symbol_table;

    uint32_t number_of_symbols;

    uint16_t size_of_optional_header;

    uint16_t characteristics;

} WD_PE_COFF_HEADER;

typedef struct
{
    WD_DEVICE_OPERATION operation;

    uint32_t device_id;
    uint32_t index;

    WD_HARDWARE_TYPE type;

    uint32_t resource_index;

    uint32_t error_code;

    void* data;
} WD_DEVICE_REQUEST;

typedef struct
{
    uint16_t magic;

    uint8_t major_linker_version;
    uint8_t minor_linker_version;

    uint32_t size_of_code;

    uint32_t size_of_initialized_data;

    uint32_t size_of_uninitialized_data;

    uint32_t address_of_entry_point;

    uint32_t base_of_code;

    uint64_t image_base;

    uint32_t section_alignment;

    uint32_t file_alignment;

    uint16_t major_os_version;

    uint16_t minor_os_version;

    uint16_t major_image_version;

    uint16_t minor_image_version;

    uint16_t major_subsystem_version;

    uint16_t minor_subsystem_version;

    uint32_t win32_version_value;

    uint32_t size_of_image;

    uint32_t size_of_headers;

    uint32_t checksum;

    uint16_t subsystem;

    uint16_t dll_characteristics;

} WD_PE_OPTIONAL_HEADER;

typedef struct
{
    char name[WD_PE_SECTION_NAME_LENGTH];

    uint32_t virtual_size;

    uint32_t virtual_address;

    uint32_t size_of_raw_data;

    uint32_t pointer_to_raw_data;

    uint32_t pointer_to_relocations;

    uint32_t pointer_to_line_numbers;

    uint16_t number_of_relocations;

    uint16_t number_of_line_numbers;

    uint32_t characteristics;

} WD_PE_SECTION_HEADER;

typedef struct
{
    WD_RECOVERY_STATE state;
    uint8_t initialized;
    uint32_t last_error;
    uint32_t error_count;
    uint32_t recovery_count;
    uint8_t panic_active;
    uint32_t panic_error;
} WD_RECOVERY_STATUS;

static WD_RECOVERY_STATUS g_recovery_status;

typedef struct
{
    WD_POWER_OPERATION operation;
    void* data;
} WD_POWER_REQUEST;

typedef struct
{
    uint64_t rip;
    uint64_t rsp;
    uint64_t rbp;

    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;

    uint64_t rsi;
    uint64_t rdi;

    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;

    uint64_t rflags;

} WD_PROCESS_CONTEXT;

typedef struct
{
    uint32_t id;

    WD_PROCESS_STATE state;
    WD_PROCESS_CONTEXT context;

    uint64_t image_base;
    uint64_t image_size;
    uint64_t entry_address;

    uint64_t stack_base;
    uint64_t stack_size;

    uint8_t loaded;

    char name[WD_PROCESS_MAX_NAME];

} WD_PROCESS;

static WD_PROCESS g_processes[WD_PROCESS_MAX_PROCESSES];

typedef struct
{
    uint32_t id;

    uint32_t process_id;

    WD_THREAD_STATE state;

    WD_PROCESS_CONTEXT context;

    uint64_t stack_base;
    uint64_t stack_size;

    uint8_t initialized;

    WD_IPC_WAIT_TYPE ipc_wait_type;

    uint32_t ipc_wait_id;

    uint8_t ipc_waiting;

    char name[WD_THREAD_MAX_NAME];

} WD_THREAD;

static WD_THREAD g_threads[WD_THREAD_MAX_THREADS];

typedef struct
{
    uint32_t version;
    uint32_t size;

    uint64_t kernel_base;
    uint64_t kernel_size;

    uint64_t memory_map;
    uint64_t memory_map_size;
    uint64_t memory_descriptor_size;

    uint32_t cpu_count;
    uint32_t device_count;

    uint8_t uefi_boot;
} WD_INIT_HANDOFF;

typedef struct
{
    WD_INIT_HANDOFF_STATE state;
    uint8_t initialized;
} WD_INIT_HANDOFF_STATUS;

typedef struct
{
    WD_INIT_STATE state;
    uint8_t initialized;
    uint32_t version;

    uint32_t failure_count;
    uint32_t last_error;
} WD_INIT_STATUS;

typedef struct
{
    WD_INIT_OPERATION operation;
    uint32_t process_id;
    void* data;
} WD_INIT_REQUEST;

typedef struct
{
    int32_t result;
    uint32_t operation;
    void* data;
} WD_INIT_RESPONSE;

typedef struct
{
    uint8_t initialized;
    uint8_t connected;
    uint32_t init_process_id;
    uint64_t message_count;
} WD_INIT_COMM_STATUS;

static WD_INIT_COMM_STATUS g_init_comm_status;

typedef void (*WD_INTERRUPT_HANDLER)(void);

static WD_FS_ENTRY g_filesystem_entries[WD_FS_MAX_FILES];
static WD_INTERRUPT_HANDLER g_interrupt_handlers[WD_KRNL_MAX_INTERRUPTS];
static WD_HARDWARE_INFO g_hardware_info;
static WD_STORAGE_DEVICE g_storage_devices[WD_STORAGE_MAX_DEVICES];
static WD_EXECUTABLE g_current_executable;
static WD_CPU_INFO g_cpu_info;
static WD_IDT_ENTRY g_idt[WD_IDT_ENTRY_COUNT];
static WD_IDT_POINTER g_idt_pointer;
static WD_CPU_HARDWARE_INFO g_cpu_hardware_info;
static WD_HARDWARE_DEVICE g_hardware_devices[WD_HARDWARE_MAX_DEVICES];
static WD_STORAGE_DRIVER g_storage_drivers[WD_STORAGE_MAX_DRIVERS];
static uint32_t g_storage_driver_count = 0;
static uint32_t g_hardware_device_count = 0;
static uint32_t g_filesystem_entry_count = 0;
static uint8_t g_filesystem_initialized = 0;
static uint8_t g_filesystem_mounted = 0;
static volatile uint64_t g_interrupt_count = 0;
static volatile uint64_t g_timer_ticks = 0;
static volatile uint8_t g_interrupts_enabled = 0;
static volatile uint64_t g_system_ticks = 0;
static volatile uint32_t g_timer_frequency = 0;
static volatile WD_EXCEPTION_INFO g_exception_info;
static WD_IPC_ENDPOINT g_ipc_endpoints[WD_IPC_MAX_ENDPOINTS];
static WD_IPC_MESSAGE g_ipc_messages[WD_IPC_MAX_MESSAGES];

static uint32_t g_ipc_endpoint_count = 0;
static uint32_t g_ipc_message_count = 0;
static WD_IPC_QUEUE g_ipc_queues[WD_IPC_MAX_QUEUES];
static uint32_t g_ipc_queue_count = 0;

static uint8_t g_ipc_initialized = 0;

static WD_MEMORY_REGION g_memory_regions[64];

static uint32_t g_memory_region_count = 0;
static uint64_t g_memory_total = 0;
static uint64_t g_memory_available = 0;
static uint32_t g_storage_device_count = 0;

static uint32_t g_kernel_status = WD_KRNL_SUCCESS;
static WD_KRNL_STATE g_kernel_state = WD_KRNL_STATE_INITIALIZING;

static void wd_console_initialize(WD_BOOT_INFO* boot_info)
{
    WD_EFI_SYSTEM_TABLE* system_table;

    if (boot_info == 0)
    {
        return;
    }

    if (boot_info->system_table == 0)
    {
        return;
    }

    system_table =
        (WD_EFI_SYSTEM_TABLE*)(uintptr_t)boot_info->system_table;

    g_wd_console = system_table->con_out;
}

static void wd_console_write(const char* text)
{
    WD_CHAR16 buffer[256];
    uint32_t i;
    void (*output_string)(
        void*,
        WD_CHAR16*
    );

    if (g_wd_console == 0)
    {
        return;
    }

    if (text == 0)
    {
        return;
    }

    i = 0;

    while (text[i] != '\0' && i < 254)
    {
        buffer[i] = (WD_CHAR16)(uint8_t)text[i];
        i++;
    }

    buffer[i] = 0;

    output_string =
        (void (*)(void*, WD_CHAR16*))
        g_wd_console->output_string;

    if (output_string == 0)
    {
        return;
    }

    output_string(g_wd_console, buffer);
}

int wdkrnl_init_handoff_initialize(WD_INIT_HANDOFF* handoff);

int wdkrnl_init_handoff_validate(const WD_INIT_HANDOFF* handoff)
{
    if (handoff == NULL)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (handoff->version == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (handoff->size < sizeof(WD_INIT_HANDOFF))
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (handoff->kernel_base == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (handoff->kernel_size == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (handoff->cpu_count == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_init_handoff_prepare(void);

int wdkrnl_init_handoff_get(WD_INIT_HANDOFF* handoff);

WD_INIT_HANDOFF_STATE wdkrnl_init_handoff_get_state(void);

int wdkrnl_init_launch(void);

static uint32_t g_init_process_id;

uint32_t wdkrnl_init_get_process_id(void);

int wdkrnl_init_is_running(void);

int wdinithost_main(WD_INIT_HANDOFF* handoff);

static WD_INIT_HANDOFF g_init_handoff;
static WD_INIT_STATUS g_init_status;

int wdinithost_initialize(WD_INIT_HANDOFF* handoff)
{
    int result;

    g_init_status.state = WD_INIT_STATE_STARTING;

    result = wdkrnl_init_handoff_validate(handoff);

    if (result != WD_KRNL_SUCCESS)
    {
        g_init_status.state = WD_INIT_STATE_FAILED;
        return result;
    }

    if (handoff == NULL)
    {
        return WD_KRNL_STATE_ERROR;
    }

    g_init_handoff = *handoff;

    g_init_status.version = WD_INIT_VERSION;
    g_init_status.initialized = 1;
    g_init_status.state = WD_INIT_STATE_READY;

    return WD_KRNL_SUCCESS;
}

int wdinithost_is_ready(void)
{
    return g_init_status.initialized && g_init_status.state == WD_INIT_STATE_READY;
}

int wdkrnl_init_comm_initialize(uint32_t process_id)
{
    if (process_id == 0)
    {
        return WD_KRNL_STATE_ERROR;
    }

    g_init_comm_status.initialized = 1;
    g_init_comm_status.connected = 1;
    g_init_comm_status.init_process_id = process_id;
    g_init_comm_status.message_count = 0;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_init_comm_request(const WD_INIT_REQUEST* request, WD_INIT_RESPONSE* response);

int wdkrnl_init_restart(void);

int wdkrnl_init_handoff_validate_system(void);

static uint8_t wdkrnl_device_type_is_valid(WD_HARDWARE_TYPE type)
{
    switch (type)
    {
        case WD_HARDWARE_TYPE_CPU:
        case WD_HARDWARE_TYPE_MEMORY:
        case WD_HARDWARE_TYPE_STORAGE:
        case WD_HARDWARE_TYPE_NETWORK:
        case WD_HARDWARE_TYPE_DISPLAY:
        case WD_HARDWARE_TYPE_USB:
        case WD_HARDWARE_TYPE_PCI:
        case WD_HARDWARE_TYPE_OTHER:
            return 1;

        default:
            return 0;
    }
}

static uint32_t wdkrnl_device_register(WD_HARDWARE_TYPE type, uint16_t vendor_id, uint16_t device_id, const char* name)
{
    if (!g_device_management_initialized)
    {  
        return WD_KRNL_INIT_FAILED;
    }

    if (name == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!wdkrnl_device_type_is_valid(type))
    {
        return UINT32_MAX;
    }

    if (g_device_count >= WD_DEVICE_MAX_DEVICES)
    {   
        return WD_KRNL_INIT_FAILED;
    }

    WD_DEVICE* device = 0;

    for (uint32_t i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        if (g_devices[i].state == WD_DEVICE_STATE_UNUSED)
        {
            device = &g_devices[i];
            break;
        }
    }

    if (device == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    device->id = (uint32_t)(device - g_devices);

    device->type = type;

    device->vendor_id = vendor_id;

    device->device_id = device_id;

    device->present = 1;
    device->enabled = 0;
    device->initialized = 0;

    device->state = WD_DEVICE_STATE_REGISTERED;

    device->resource_count = 0;

    for (uint32_t i = 0; i < WD_DEVICE_MAX_RESOURCES; i++)
    {
        device->resources[i].type = WD_DEVICE_RESOURCE_NONE;
        device->resources[i].start = 0;
        device->resources[i].length = 0;
        device->resources[i].flags = 0;
        device->resources[i].assigned = 0;
    }

    for (uint32_t i = 0; i < WD_DEVICE_MAX_NAME; i++)
    {
        device->name[i] = '\0';
    }

    uint32_t i = 0;

    while(name[i] != '\0' && i < WD_DEVICE_MAX_NAME - 1)
    {
        device->name[i] = name[i];
        i++;
    }

    device->name[i] = '\0';

    g_device_count++;

    return device->id;
}

static WD_DEVICE* wdkrnl_device_get(uint32_t device_id)
{
    if (!g_device_management_initialized)
    {   
        return 0;
    }

    if (device_id >= WD_DEVICE_MAX_DEVICES)
    {   
        return 0;
    }

    WD_DEVICE* device = &g_devices[device_id];

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {   
        return 0;
    }

    return device;
}

static uint32_t wdkrnl_device_get_count(void)
{
    if (!g_device_management_initialized)
    {
        return 0;
    }

    return g_device_count;
}

static uint32_t wdkrnl_device_validate_transition(WD_DEVICE_STATE current, WD_DEVICE_STATE next)
{
    switch (current)
    {
        case WD_DEVICE_STATE_REGISTERED:
            if (next == WD_DEVICE_STATE_INITIALIZING)
            {
                return WD_KRNL_SUCCESS;
            }

            break;

        case WD_DEVICE_STATE_INITIALIZING:
            if (next == WD_DEVICE_STATE_READY)
            {
                return WD_KRNL_SUCCESS;
            }

            if (next == WD_DEVICE_STATE_ERROR)
            {
                return WD_KRNL_SUCCESS;
            }

            break;

        case WD_DEVICE_STATE_READY:
            if (next == WD_DEVICE_STATE_DISABLED)
            {
                return WD_KRNL_SUCCESS;
            }

            if (next == WD_DEVICE_STATE_ERROR)
            {
                return WD_KRNL_SUCCESS;
            }

            break;

        case WD_DEVICE_STATE_DISABLED:
            if (next == WD_DEVICE_STATE_READY)
            {
                return WD_KRNL_SUCCESS;
            }

            if (next == WD_DEVICE_STATE_ERROR)
            {
                return WD_KRNL_SUCCESS;
            }

            break;

        case WD_DEVICE_STATE_ERROR:
            return next == WD_DEVICE_STATE_REGISTERED;

        case WD_DEVICE_STATE_UNUSED:
            break;

        default:
            break;
    }

    return WD_KRNL_INIT_FAILED;
}

int wdkrnl_recovery_initialize(void)
{
    g_recovery_status.state = WD_RECOVERY_STATE_NORMAL;
    g_recovery_status.initialized = 1;
    g_recovery_status.last_error = 0;
    g_recovery_status.error_count = 0;
    g_recovery_status.recovery_count = 0;
    uint8_t panic_active;
    uint32_t panic_error;
    g_recovery_status.panic_active = 0;
    g_recovery_status.panic_error = WD_RECOVERY_ERROR_NONE;

    if (g_recovery_status.state == WD_RECOVERY_STATE_RECOVERING)
    {
        return WD_KRNL_FATAL_ERROR;
    
    }
    g_recovery_status.recovery_count++;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_recovery_state_validate(WD_RECOVERY_STATE state)
{
    switch (state)
    {
        case WD_RECOVERY_STATE_NORMAL:
        case WD_RECOVERY_STATE_DEGRADED:
        case WD_RECOVERY_STATE_RECOVERING:
        case WD_RECOVERY_STATE_FAILED:
        case WD_RECOVERY_STATE_PANIC:
            return WD_KRNL_SUCCESS;

        default:
            return WD_KRNL_FATAL_ERROR;
    }
}

WD_RECOVERY_STATE wdkrnl_recovery_get_state(void)
{
    return g_recovery_status.state;
}

int wdkrnl_recovery_is_initialized(void)
{
    return g_recovery_status.initialized ? 1 : 0;
}

int wdkrnl_recovery_validate_transition(WD_RECOVERY_STATE current, WD_RECOVERY_STATE target)
{
    switch (current)
    {
        case WD_RECOVERY_STATE_NORMAL:
            return target == WD_RECOVERY_STATE_DEGRADED ? WD_KRNL_SUCCESS : WD_KRNL_FATAL_ERROR;

        case WD_RECOVERY_STATE_DEGRADED:
            if (target == WD_RECOVERY_STATE_NORMAL || target == WD_RECOVERY_STATE_RECOVERING)
            {
                return WD_KRNL_SUCCESS;
            }

            return WD_KRNL_FATAL_ERROR;

        case WD_RECOVERY_STATE_RECOVERING:
            if (target == WD_RECOVERY_STATE_NORMAL || target == WD_RECOVERY_STATE_FAILED)
            {
                return WD_KRNL_SUCCESS;
            }

            return WD_KRNL_FATAL_ERROR;

        case WD_RECOVERY_STATE_FAILED:
            return target == WD_RECOVERY_STATE_PANIC ? WD_KRNL_SUCCESS : WD_KRNL_FATAL_ERROR;

        case WD_RECOVERY_STATE_PANIC:
            return WD_KRNL_FATAL_ERROR;

        default:
            return WD_KRNL_FATAL_ERROR;
    }
}

int wdkrnl_health_initialize(void)
{
    g_health_status.state = WD_HEALTH_STATE_UNKNOWN;
    g_health_status.initialized = 1;
    g_health_status.heartbeat = 0;
    g_health_status.check_count = 0;
    g_health_status.failure_count = 0;

    return WD_KRNL_SUCCESS;
}

void wdkrnl_health_heartbeat(void)
{
    if (!g_health_status.initialized)
    {
        return;
    }

    g_health_status.heartbeat++;
}

uint64_t wdkrnl_health_get_heartbeat(void)
{
    return g_health_status.heartbeat;
}

int wdkrnl_health_check(void) // FUCKITGJGNFRJO;IFFKGMRIJGLTFVDJIOFUJFFUCKCKCK HYTRHUI IM GOING FUCKING INSANE IM THROWING SHIT WITH GRANDPA HELPPPP
{
    // check the health, sir
    // -- SBM4 (Weird Ferb O'Fletynn)
    if (!g_health_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    g_health_status.check_count++;

    if (g_kernel_status != WD_KRNL_SUCCESS)
    {
        g_health_status.state = WD_HEALTH_STATE_FAILED;

        g_health_status.failure_count++;

        return WD_KRNL_FATAL_ERROR;
    }

    // temporary placeholder for the validations

    g_health_status.state = WD_HEALTH_STATE_HEALTHY;

    return WD_KRNL_SUCCESS;
}

WD_HEALTH_STATE wdkrnl_health_get_state(void)
{
    return g_health_status.state;
}

int wdkrnl_health_is_healthy(void)
{
    return g_health_status.state == WD_HEALTH_STATE_HEALTHY;
}

int wdkrnl_health_is_failed(void)
{
    return g_health_status.state == WD_HEALTH_STATE_FAILED;
}

int wdkrnl_health_state_validate(WD_HEALTH_STATE state)
{
    switch (state)
    {
        case WD_HEALTH_STATE_UNKNOWN:
        case WD_HEALTH_STATE_HEALTHY:
        case WD_HEALTH_STATE_DEGRADED:
        case WD_HEALTH_STATE_FAILED:
            return WD_KRNL_SUCCESS;

        default:
            return WD_KRNL_FATAL_ERROR;
    }
}

// im pooing so hard, i have no idea why

int wdkrnl_health_validate(void)
{
    if (!g_health_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_health_state_validate(g_health_status.state) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_recovery_error_validate(WD_RECOVERY_ERROR error)
{
    switch (error)
    {
        case WD_RECOVERY_ERROR_NONE:
        case WD_RECOVERY_ERROR_MEMORY:
        case WD_RECOVERY_ERROR_PROCESS:
        case WD_RECOVERY_ERROR_THREAD:
        case WD_RECOVERY_ERROR_INTERRUPT:
        case WD_RECOVERY_ERROR_DEVICE:
        case WD_RECOVERY_ERROR_IPC:
        case WD_RECOVERY_ERROR_STORAGE:
        case WD_RECOVERY_ERROR_FILESYSTEM:
        case WD_RECOVERY_ERROR_KERNEL:
        case WD_RECOVERY_ERROR_HEALTH:
            return WD_KRNL_SUCCESS;

        default:
            return WD_KRNL_FATAL_ERROR;
    }
}

int wdkrnl_recovery_report_error(WD_RECOVERY_ERROR error)
{
    if (!g_recovery_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_recovery_error_validate(error) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (error == WD_RECOVERY_ERROR_NONE)
    {
        return WD_KRNL_SUCCESS;
    }

    g_recovery_status.last_error = error;
    g_recovery_status.error_count++;

    if (g_recovery_status.state == WD_RECOVERY_STATE_NORMAL)
    {
        g_recovery_status.state = WD_RECOVERY_STATE_DEGRADED;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_recovery_error_is_recoverable(WD_RECOVERY_ERROR error);

WD_RECOVERY_ERROR wdkrnl_recovery_get_last_error(void)
{
    return (WD_RECOVERY_ERROR) g_recovery_status.last_error;
}

uint32_t wdkrnl_recovery_get_error_count(void)
{
    return g_recovery_status.error_count;
}

int wdkrnl_recovery_detect_failure(void)
{
    if (!g_recovery_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!wdkrnl_health_is_healthy())
    {
        return wdkrnl_recovery_report_error(
            WD_RECOVERY_ERROR_HEALTH
        );
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_recovery_validate_errors(void)
{
    if (!g_recovery_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_recovery_error_validate((WD_RECOVERY_ERROR) g_recovery_status.last_error) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_recovery_action_validate(WD_RECOVERY_ACTION action)
{
    switch (action)
    {
        case WD_RECOVERY_ACTION_NONE:
        case WD_RECOVERY_ACTION_RETRY:
        case WD_RECOVERY_ACTION_RECOVER:
        case WD_RECOVERY_ACTION_DEGRADE:
        case WD_RECOVERY_ACTION_PANIC:
            return WD_KRNL_SUCCESS;

        default:
            return WD_KRNL_FATAL_ERROR;
    }
}

WD_RECOVERY_ACTION wdkrnl_recovery_get_action(WD_RECOVERY_ERROR error);

int wdkrnl_recovery_execute(WD_RECOVERY_ACTION action);

int wdkrnl_recovery_enter_degraded(void)
{
    if (!g_recovery_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_recovery_status.state == WD_RECOVERY_STATE_PANIC)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    g_recovery_status.state = WD_RECOVERY_STATE_DEGRADED;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_recovery_begin(void)
{
    if (!g_recovery_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_recovery_status.state == WD_RECOVERY_STATE_PANIC)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (g_recovery_status.state == WD_RECOVERY_STATE_RECOVERING)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    g_recovery_status.state = WD_RECOVERY_STATE_RECOVERING;

    g_recovery_status.recovery_count++;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_recovery_complete(void)
{
    if (!g_recovery_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_recovery_status.state != WD_RECOVERY_STATE_RECOVERING)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    g_recovery_status.state = WD_RECOVERY_STATE_NORMAL;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_recovery_fail(void)
{
    if (!g_recovery_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_recovery_status.state != WD_RECOVERY_STATE_RECOVERING)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    g_recovery_status.state = WD_RECOVERY_STATE_FAILED;

    return WD_KRNL_SUCCESS;
}

void wdkrnl_panic(WD_RECOVERY_ERROR error)
{
    g_recovery_status.panic_active = 1;
    g_recovery_status.panic_error = error;
    g_recovery_status.state = WD_RECOVERY_STATE_PANIC;

#if defined(__x86_64__) || defined(__i386__)
    __asm__ volatile ("cli");

    for (;;)
    {
        __asm__ volatile ("hlt");
    }
#else
    for (;;)
    {
    }
#endif
}

int wdkrnl_recovery_panic(WD_RECOVERY_ERROR error)
{
    if (!g_recovery_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_recovery_error_validate(error) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    wdkrnl_panic(error);

    return WD_KRNL_FATAL_ERROR;
}

int wdkrnl_recovery_is_panicking(void)
{
    return g_recovery_status.panic_active ? 1 : 0;
}

WD_RECOVERY_ERROR wdkrnl_recovery_get_panic_error(void)
{
    return (WD_RECOVERY_ERROR) g_recovery_status.panic_error;
}

int wdkrnl_watchdog_initialize(void)
{
    g_watchdog_status.initialized = 0;
    g_watchdog_status.enabled = 1;

    g_watchdog_status.heartbeat = 0;
    g_watchdog_status.last_checked_heartbeat = 0;

    g_watchdog_status.check_count = 0;
    g_watchdog_status.failure_count = 0;

    g_watchdog_status.initialized = 1;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_watchdog_check(void)
{
    uint64_t heartbeat;

    if (!g_watchdog_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_watchdog_status.enabled)
    {
        return WD_KRNL_SUCCESS;
    }

    g_watchdog_status.check_count++;

    heartbeat = wdkrnl_health_get_heartbeat();

    if (heartbeat == g_watchdog_status.last_checked_heartbeat)
    {
        g_watchdog_status.failure_count++;

        wdkrnl_recovery_report_error(WD_RECOVERY_ERROR_HEALTH);

        return WD_KRNL_FATAL_ERROR;
    }

    g_watchdog_status.last_checked_heartbeat =
        heartbeat;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_watchdog_supervise(void)
{
    int result;

    result = wdkrnl_health_check();

    if (result != WD_KRNL_SUCCESS)
    {
        wdkrnl_recovery_report_error(WD_RECOVERY_ERROR_HEALTH);

        return result;
    }

    return wdkrnl_watchdog_check();
}

int wdkrnl_watchdog_enable(void);
int wdkrnl_watchdog_disable(void);
int wdkrnl_watchdog_is_enabled(void);
uint64_t wdkrnl_watchdog_get_heartbeat(void);
uint64_t wdkrnl_watchdog_get_last_checked(void);
uint32_t wdkrnl_watchdog_get_check_count(void);
uint32_t wdkrnl_watchdog_get_failure_count(void);

int wdkrnl_recovery_validate(void);
int wdkrnl_recovery_supervision_validate(void);

static uint32_t wdkrnl_device_set_state(WD_DEVICE* device, WD_DEVICE_STATE state)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_device_validate_transition(device->state, state) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    device->state = state;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_device_begin_initialize(WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!device->present)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device->state != WD_DEVICE_STATE_REGISTERED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    device->initialized = 0;
    device->enabled = 0;

    return wdkrnl_device_set_state(device, WD_DEVICE_STATE_INITIALIZING);
}

static uint32_t wdkrnl_device_complete_initialize(WD_DEVICE* device, uint8_t success)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device->state != WD_DEVICE_STATE_INITIALIZING)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!device->present)
    {
        device->initialized = 0;
        device->enabled = 0;

        device->state = WD_DEVICE_STATE_ERROR;

        return WD_KRNL_INIT_FAILED;
    }

    if (!success)
    {
        device->initialized = 0;
        device->enabled = 0;

        device->state = WD_DEVICE_STATE_ERROR;

        return WD_KRNL_INIT_FAILED;
    }

    device->initialized = 1;
    device->enabled = 1;

    return wdkrnl_device_set_state(device, WD_DEVICE_STATE_READY);
}

static uint32_t wdkrnl_device_disable(WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device->state != WD_DEVICE_STATE_READY)
    {
        return WD_KRNL_INIT_FAILED;
    }

    device->enabled = 0;

    return wdkrnl_device_set_state(device, WD_DEVICE_STATE_DISABLED);
}

static uint32_t wdkrnl_device_enable(WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!device->present)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device->state != WD_DEVICE_STATE_DISABLED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!device->initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    device->enabled = 1;

    return wdkrnl_device_set_state(device, WD_DEVICE_STATE_READY);
}

static uint32_t wdkrnl_device_set_error(WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    device->initialized = 0;
    device->enabled = 0;

    return wdkrnl_device_set_state(device, WD_DEVICE_STATE_ERROR);
}

static WD_DEVICE_STATE wdkrnl_device_get_state(const WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return WD_DEVICE_STATE_UNUSED;
    }

    if (device == 0)
    {
        return WD_DEVICE_STATE_UNUSED;
    }

    return device->state;
}

static uint32_t wdkrnl_device_validate_lifecycle(const WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    switch (device->state)
    {
        case WD_DEVICE_STATE_REGISTERED:
            if (!device->present)
            {
                return WD_KRNL_INIT_FAILED;
            }

            if (device->initialized)
            {
                return WD_KRNL_INIT_FAILED;
            }

            if (device->enabled)
            {
                return WD_KRNL_INIT_FAILED;
            }

            break;

        case WD_DEVICE_STATE_INITIALIZING:
            if (!device->present)
            {
                return WD_KRNL_INIT_FAILED;
            }

            if (device->initialized)
            {
                return WD_KRNL_INIT_FAILED;
            }

            if (device->enabled)
            {
                return WD_KRNL_INIT_FAILED;
            }

            break;

        case WD_DEVICE_STATE_READY:
            if (!device->present)
            {
                return WD_KRNL_INIT_FAILED;
            }

            if (!device->initialized)
            {
                return WD_KRNL_INIT_FAILED;
            }

            if (!device->enabled)
            {
                return WD_KRNL_INIT_FAILED;
            }

            break;

        case WD_DEVICE_STATE_DISABLED:
            if (!device->present)
            {
                return WD_KRNL_INIT_FAILED;
            }

            if (!device->initialized)
            {
                return WD_KRNL_INIT_FAILED;
            }

            if (device->enabled)
            {
                return WD_KRNL_INIT_FAILED;
            }

            break;

        case WD_DEVICE_STATE_ERROR:
            if (device->enabled)
            {
                return WD_KRNL_INIT_FAILED;
            }

            if (device->initialized)
            {
                return WD_KRNL_INIT_FAILED;
            }

            break;

        case WD_DEVICE_STATE_UNUSED:
            return WD_KRNL_SUCCESS;

        default:
            return WD_KRNL_INIT_FAILED;
    }

    return WD_KRNL_SUCCESS;
}

static const char *wdkrnl_device_type_name(WD_HARDWARE_TYPE type)
{
    switch (type)
    {
        case WD_HARDWARE_TYPE_CPU:
            return "CPU";

        case WD_HARDWARE_TYPE_MEMORY:
            return "MEMORY";

        case WD_HARDWARE_TYPE_STORAGE:
            return "STORAGE";

        case WD_HARDWARE_TYPE_NETWORK:
            return "NETWORK";

        case WD_HARDWARE_TYPE_DISPLAY:
            return "DISPLAY";

        case WD_HARDWARE_TYPE_USB:
            return "USB";

        case WD_HARDWARE_TYPE_PCI:
            return "PCI";

        case WD_HARDWARE_TYPE_OTHER:
            return "OTHER";

        default:
            return "UNKNOWN";
    }
}

int wdkrnl_device_is_type (const WD_DEVICE *device, WD_HARDWARE_TYPE type)
{
    if (!g_device_management_initialized)
    {
        return 0;
    }

    if (device == NULL)
    {
        return 0;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return 0;
    }

    if (!wdkrnl_device_type_is_valid(type))
    {
        return 0;
    }

    return device->type == type;
}

WD_DEVICE *wdkrnl_device_get_by_type(WD_HARDWARE_TYPE type)
{
    uint32_t i;

    if (!g_device_management_initialized)
    {
        return NULL;
    }

    if (!wdkrnl_device_type_is_valid(type))
    {
        return NULL;
    }

    for (i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        if (g_devices[i].state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (g_devices[i].type == type)
        {
            return &g_devices[i];
        }
    }

    return NULL;
}

uint32_t wdkrnl_device_get_count_by_type(WD_HARDWARE_TYPE type)
{
    uint32_t i;
    uint32_t count = 0;

    if (!g_device_management_initialized)
    {
        return 0;
    }

    if (!wdkrnl_device_type_is_valid(type))
    {
        return 0;
    }

    for (i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        if (g_devices[i].state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (g_devices[i].type == type)
        {
            count++;
        }
    }

    return count;
}

int wdkrnl_device_validate_types(void)
{
    uint32_t i;

    if (!g_device_management_initialized)
    {
        return 0;
    }

    for (i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        if (g_devices[i].state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (!wdkrnl_device_type_is_valid(g_devices[i].type))
        {
            return 0;
        }
    }

    return 1;
}

const char *wdkrnl_device_get_type_name(const WD_DEVICE *device)
{
    if (!g_device_management_initialized)
    {
        return "UNKNOWN";
    }

    if (device == NULL)
    {
        return "UNKNOWN";
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return "UNKNOWN";
    }

    return wdkrnl_device_type_name(device->type);
}

int wdkrnl_device_validate_type_system(void)
{
    WD_HARDWARE_TYPE types[] =
    {
        WD_HARDWARE_TYPE_CPU,
        WD_HARDWARE_TYPE_MEMORY,
        WD_HARDWARE_TYPE_STORAGE,
        WD_HARDWARE_TYPE_NETWORK,
        WD_HARDWARE_TYPE_DISPLAY,
        WD_HARDWARE_TYPE_USB,
        WD_HARDWARE_TYPE_PCI,
        WD_HARDWARE_TYPE_OTHER
    };

    uint32_t i;

    if (!g_device_management_initialized)
    {
        return 0;
    }

    for (i = 0; i < 8; i++)
    {
        if (!wdkrnl_device_type_is_valid(types[i]))
        {
            return 0;
        }

        if (wdkrnl_device_type_name(types[i])[0] == '\0')
        {
            return 0;
        }
    }

    if (!wdkrnl_device_validate_types())
    {
        return 0;
    }

    return 1;
}

static int wdkrnl_device_resource_type_is_valid(WD_DEVICE_RESOURCE_TYPE type)
{
    switch (type)
    {
        case WD_DEVICE_RESOURCE_MEMORY:
        case WD_DEVICE_RESOURCE_IO:
        case WD_DEVICE_RESOURCE_INTERRUPT:
        case WD_DEVICE_RESOURCE_DMA:
            return 1;

        default:
            return 0;
    }
}

int wdkrnl_device_add_resource(
    WD_DEVICE *device,
    WD_DEVICE_RESOURCE_TYPE type,
    uint64_t start,
    uint64_t length,
    uint32_t flags
)
{
    uint32_t i;

    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!wdkrnl_device_resource_type_is_valid(type))
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (length == 0)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->resource_count >= WD_DEVICE_MAX_RESOURCES)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    for (i = 0; i < WD_DEVICE_MAX_RESOURCES; i++)
    {
        if (!device->resources[i].assigned)
        {
            device->resources[i].type = type;
            device->resources[i].start = start;
            device->resources[i].length = length;
            device->resources[i].flags = flags;
            device->resources[i].assigned = 1;

            device->resource_count++;

            return WD_KRNL_SUCCESS;
        }
    }

    return WD_KRNL_FATAL_ERROR;
}

int wdkrnl_device_remove_resource(WD_DEVICE *device, uint32_t resource_index)
{
    WD_DEVICE_RESOURCE *resource;

    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (resource_index >= WD_DEVICE_MAX_RESOURCES)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    resource = &device->resources[resource_index];

    if (!resource->assigned)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    resource->type = WD_DEVICE_RESOURCE_NONE;
    resource->start = 0;
    resource->length = 0;
    resource->flags = 0;
    resource->assigned = 0;

    if (device->resource_count > 0)
    {
        device->resource_count--;
    }

    return WD_KRNL_SUCCESS;
}

WD_DEVICE_RESOURCE *wdkrnl_device_get_resource(WD_DEVICE *device, uint32_t resource_index)
{
    if (!g_device_management_initialized)
    {
        return NULL;
    }

    if (device == NULL)
    {
        return NULL;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return NULL;
    }

    if (resource_index >= WD_DEVICE_MAX_RESOURCES)
    {
        return NULL;
    }

    if (!device->resources[resource_index].assigned)
    {
        return NULL;
    }

    return &device->resources[resource_index];
}

uint32_t wdkrnl_device_get_resource_count(const WD_DEVICE *device)
{
    if (!g_device_management_initialized)
    {
        return 0;
    }

    if (device == NULL)
    {
        return 0;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return 0;
    }

    return device->resource_count;
}

int wdkrnl_device_validate_resources(const WD_DEVICE *device)
{
    uint32_t i;
    uint32_t count = 0;

    if (!g_device_management_initialized)
    {
        return 0;
    }

    if (device == NULL)
    {
        return 0;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return 0;
    }

    if (device->resource_count > WD_DEVICE_MAX_RESOURCES)
    {
        return 0;
    }

    for (i = 0; i < WD_DEVICE_MAX_RESOURCES; i++)
    {
        const WD_DEVICE_RESOURCE *resource = &device->resources[i];

        if (!resource->assigned)
        {
            continue;
        }

        if (!wdkrnl_device_resource_type_is_valid(resource->type))
        {
            return 0;
        }

        if (resource->length == 0)
        {
            return 0;
        }

        count++;
    }

    if (count != device->resource_count)
    {
        return 0;
    }

    return 1;
}

int wdkrnl_device_validate_all_resources(void)
{
    uint32_t i;

    if (!g_device_management_initialized)
    {
        return 0;
    }

    for (i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        if (g_devices[i].state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (!wdkrnl_device_validate_resources(&g_devices[i]))
        {
            return 0;
        }
    }

    return 1;
}

const char *wdkrnl_device_resource_type_name(WD_DEVICE_RESOURCE_TYPE type)
{
    switch (type)
    {
        case WD_DEVICE_RESOURCE_MEMORY:
            return "MEMORY";

        case WD_DEVICE_RESOURCE_IO:
            return "IO";

        case WD_DEVICE_RESOURCE_INTERRUPT:
            return "INTERRUPT";

        case WD_DEVICE_RESOURCE_DMA:
            return "DMA";

        default:
            return "NONE";
    }
}

int wdkrnl_device_validate_resource_system(void)
{
    uint32_t i;

    if (!g_device_management_initialized)
    {
        return 0;
    }

    for (i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        if (g_devices[i].state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (!wdkrnl_device_validate_resources(&g_devices[i]))
        {
            return 0;
        }
    }

    return 1;
}

int wdkrnl_device_driver_initialize(void)
{
    uint32_t i;

    g_device_driver_count = 0;
    g_device_driver_management_initialized = 0;

    for (i = 0; i < WD_DEVICE_MAX_DRIVERS; i++)
    {
        g_device_drivers[i].id = 0;
        g_device_drivers[i].name[0] = '\0';
        g_device_drivers[i].supported_type = WD_HARDWARE_TYPE_OTHER;

        g_device_drivers[i].probe = NULL;
        g_device_drivers[i].remove = NULL;
        g_device_drivers[i].enable = NULL;
        g_device_drivers[i].disable = NULL;

        g_device_drivers[i].registered = 0;
        g_device_drivers[i].bound = 0;
        g_device_drivers[i].bound_device_id = 0;
    }

    g_device_driver_management_initialized = 1;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_driver_validate(const WD_DEVICE_DRIVER* driver)
{
    if (!g_device_driver_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (driver == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->registered)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!wdkrnl_device_type_is_valid(driver->supported_type))
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (driver->name[0] == '\0')
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (driver->probe == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (driver->remove == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (driver->enable == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }
    
    if (driver->disable == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (driver->bound && driver->bound_device_id >= WD_DEVICE_MAX_DEVICES)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_driver_register(
    const char* name,
    WD_HARDWARE_TYPE supported_type,
    WD_DEVICE_DRIVER_PROBE probe,
    WD_DEVICE_DRIVER_REMOVE remove,
    WD_DEVICE_DRIVER_ENABLE enable,
    WD_DEVICE_DRIVER_DISABLE disable,
    uint32_t* driver_id
)
{
    uint32_t i;

    if (!g_device_driver_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (name == NULL || probe == NULL || remove == NULL || enable == NULL || disable == NULL || driver_id == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!wdkrnl_device_type_is_valid(supported_type))
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (g_device_driver_count >= WD_DEVICE_MAX_DRIVERS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    for (i = 0; i < WD_DEVICE_MAX_DRIVERS; i++)
    {
        if (!g_device_drivers[i].registered)
        {
            WD_DEVICE_DRIVER* driver = &g_device_drivers[i];

            driver->id = i;

            driver->supported_type = supported_type;

            driver->probe = probe;
            driver->remove = remove;

            driver->registered = 1;
            driver->bound = 0;
            driver->bound_device_id = 0;

            driver->name[0] = '\0';
            

            for (uint32_t j = 0; j < WD_DEVICE_MAX_DRIVER_NAME - 1 && name[j] != '\0'; j++)
            {
                driver->name[j] = name[j];
                driver->name[j + 1] = '\0';
            }

            g_device_driver_count++;

            *driver_id = driver->id;

            return WD_KRNL_SUCCESS;
        }
    }

    return WD_KRNL_FATAL_ERROR;
}

WD_DEVICE_DRIVER* wdkrnl_device_driver_get(uint32_t driver_id)
{
    if (!g_device_driver_management_initialized)
    {
        return NULL;
    }

    if (driver_id >= WD_DEVICE_MAX_DRIVERS)
    {
        return NULL;
    }

    if (!g_device_drivers[driver_id].registered)
    {
        return NULL;
    }

    return &g_device_drivers[driver_id];
}

uint32_t wdkrnl_device_driver_get_count(void)
{
    if (!g_device_driver_management_initialized)
    {
        return 0;
    }

    return g_device_driver_count;
}

int wdkrnl_device_driver_is_compatible(const WD_DEVICE_DRIVER* driver, const WD_DEVICE* device)
{
    if (!g_device_driver_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (driver == NULL || device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->registered)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (driver->supported_type != device->type)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_driver_bind(WD_DEVICE_DRIVER* driver, WD_DEVICE* device)
{
    int result;

    if (!g_device_driver_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (driver == NULL || device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->registered)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (driver->bound)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    result = wdkrnl_device_driver_is_compatible(driver, device);

    if (result != WD_KRNL_SUCCESS)
    {
        return result;
    }

    result = driver->probe(device);

    if (result != WD_KRNL_SUCCESS)
    {
        return result;
    }

    driver->bound = 1;
    driver->bound_device_id = device->id;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_driver_unbind(WD_DEVICE_DRIVER* driver, WD_DEVICE* device)
{
    int result;

    if (!g_device_driver_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (driver == NULL || device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->registered)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->bound)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (driver->bound_device_id != device->id)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    result = driver->remove(device);

    if (result != WD_KRNL_SUCCESS)
    {
        return result;
    }

    driver->bound = 0;
    driver->bound_device_id = 0;

    return WD_KRNL_SUCCESS;
}

WD_DEVICE_DRIVER* wdkrnl_device_driver_get_for_type(WD_HARDWARE_TYPE type)
{
    uint32_t i;

    if (!g_device_driver_management_initialized)
    {
        return NULL;
    }

    if (!wdkrnl_device_type_is_valid(type))
    {
        return NULL;
    }

    for (i = 0; i < WD_DEVICE_MAX_DRIVERS; i++)
    {
        if (g_device_drivers[i].registered && g_device_drivers[i].supported_type == type && !g_device_drivers[i].bound)
        {
            return &g_device_drivers[i];
        }
    }

    return NULL;
}

int wdkrnl_device_driver_validate_all(void)
{
    uint32_t i;

    if (!g_device_driver_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    for (i = 0; i < WD_DEVICE_MAX_DRIVERS; i++)
    {
        if (!g_device_drivers[i].registered)
        {
            continue;
        }

        if (wdkrnl_device_driver_validate(&g_device_drivers[i]) != WD_KRNL_SUCCESS)
        {
            return WD_KRNL_FATAL_ERROR;
        }
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_validate_driver_system(void)
{
    uint32_t i;

    if (!g_device_driver_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_device_driver_count > WD_DEVICE_MAX_DRIVERS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    for (i = 0; i < WD_DEVICE_MAX_DRIVERS; i++)
    {
        WD_DEVICE_DRIVER* driver = &g_device_drivers[i];

        if (!driver->registered)
        {
            continue;
        }

        if (wdkrnl_device_driver_validate(driver) != WD_KRNL_SUCCESS)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (driver->bound)
        {
            WD_DEVICE* device = wdkrnl_device_get(driver->bound_device_id);

            if (device == NULL)
            {
                return WD_KRNL_FATAL_ERROR;
            }

            if (wdkrnl_device_driver_is_compatible(driver, device) != WD_KRNL_SUCCESS)
            {
                return WD_KRNL_FATAL_ERROR;
            }
        }
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_driver_enable(WD_DEVICE_DRIVER* driver, WD_DEVICE* device)
{
    int result;

    if (!g_device_driver_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (driver == NULL || device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->registered)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->bound)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (driver->bound_device_id != device->id)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state != WD_DEVICE_STATE_DISABLED)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    result = driver->enable(device);

    if (result != WD_KRNL_SUCCESS)
    {
        return result;
    }

    return wdkrnl_device_enable(device);
}

int wdkrnl_device_driver_disable(WD_DEVICE_DRIVER* driver, WD_DEVICE* device)
{
    int result;

    if (!g_device_driver_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (driver == NULL || device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->registered)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->bound)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (driver->bound_device_id != device->id)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state != WD_DEVICE_STATE_READY)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    result = driver->disable(device);

    if (result != WD_KRNL_SUCCESS)
    {
        return result;
    }

    return wdkrnl_device_disable(device);
}

int wdkrnl_device_enable_by_id(uint32_t device_id)
{
    WD_DEVICE* device;
    WD_DEVICE_DRIVER* driver;

    device = wdkrnl_device_get(device_id);

    if (device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    driver = wdkrnl_device_driver_get_for_type(device->type);

    if (driver == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->bound ||
        driver->bound_device_id != device_id)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return wdkrnl_device_driver_enable(driver, device);
}

int wdkrnl_device_disable_by_id(uint32_t device_id)
{
    WD_DEVICE* device;
    WD_DEVICE_DRIVER* driver;

    device = wdkrnl_device_get(device_id);

    if (device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    driver = wdkrnl_device_driver_get_for_type(device->type);

    if (driver == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->bound || driver->bound_device_id != device_id)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return wdkrnl_device_driver_disable(driver, device);
}

int wdkrnl_device_validate_enable_state(const WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state == WD_DEVICE_STATE_READY)
    {
        if (!device->enabled ||
            !device->initialized)
        {
            return WD_KRNL_FATAL_ERROR;
        }
    }

    if (device->state == WD_DEVICE_STATE_DISABLED)
    {
        if (device->enabled ||
            !device->initialized)
        {
            return WD_KRNL_FATAL_ERROR;
        }
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_validate_all_enable_states(void)
{
    uint32_t i;

    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    for (i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        if (g_devices[i].state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (wdkrnl_device_validate_enable_state(&g_devices[i]) != WD_KRNL_SUCCESS)
        {
            return WD_KRNL_FATAL_ERROR;
        }
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_validate_enable_system(void)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_device_validate_all_enable_states()
        != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_driver_validate_all() != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

WD_DEVICE* wdkrnl_device_enumerate(uint32_t index)
{
    uint32_t current_index = 0;

    if (!g_device_management_initialized)
    {
        return NULL;
    }

    for (uint32_t i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        WD_DEVICE* device = &g_devices[i];

        if (device->state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (current_index == index)
        {
            return device;
        }

        current_index++;
    }

    return NULL;
}

uint32_t wdkrnl_device_enumerate_count(void)
{
    uint32_t count = 0;

    if (!g_device_management_initialized)
    {
        return 0;
    }

    for (uint32_t i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        WD_DEVICE* device = &g_devices[i];

        if (device->state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        count++;
    }

    return count;
}

WD_DEVICE* wdkrnl_device_enumerate_type(WD_HARDWARE_TYPE type, uint32_t index)
{
    uint32_t current_index = 0;

    if (!g_device_management_initialized)
    {
        return NULL;
    }

    if (!wdkrnl_device_type_is_valid(type))
    {
        return NULL;
    }

    for (uint32_t i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        WD_DEVICE* device = &g_devices[i];

        if (device->state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (device->type != type)
        {
            continue;
        }

        if (current_index == index)
        {
            return device;
        }

        current_index++;
    }

    return NULL;
}

uint32_t wdkrnl_device_enumerate_count_type(WD_HARDWARE_TYPE type)
{
    uint32_t count = 0;

    if (!g_device_management_initialized)
    {
        return 0;
    }

    if (!wdkrnl_device_type_is_valid(type))
    {
        return 0;
    }

    for (uint32_t i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        WD_DEVICE* device = &g_devices[i];

        if (device->state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (device->type != type)
        {
            continue;
        }

        count++;
    }

    return count;
}

WD_DEVICE* wdkrnl_device_enumerate_state(WD_DEVICE_STATE state, uint32_t index)
{
    uint32_t current_index = 0;

    if (!g_device_management_initialized)
    {
        return NULL;
    }

    if (state == WD_DEVICE_STATE_UNUSED)
    {
        return NULL;
    }

    for (uint32_t i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        WD_DEVICE* device = &g_devices[i];

        if (device->state != state)
        {
            continue;
        }

        if (current_index == index)
        {
            return device;
        }

        current_index++;
    }

    return NULL;
}

uint32_t wdkrnl_device_enumerate_count_state(WD_DEVICE_STATE state)
{
    uint32_t count = 0;

    if (!g_device_management_initialized)
    {
        return 0;
    }

    if (state == WD_DEVICE_STATE_UNUSED)
    {
        return 0;
    }

    for (uint32_t i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        WD_DEVICE* device = &g_devices[i];

        if (device->state != state)
        {
            continue;
        }

        count++;
    }

    return count;
}

WD_DEVICE* wdkrnl_device_enumerate_ready(uint32_t index)
{
    return wdkrnl_device_enumerate_state(WD_DEVICE_STATE_READY, index);
}

uint32_t wdkrnl_device_enumerate_ready_count(void)
{
    return wdkrnl_device_enumerate_count_state(WD_DEVICE_STATE_READY);
}

int wdkrnl_device_validate_enumeration(void)
{
    uint32_t enumeration_count = 0;

    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    for (uint32_t i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        WD_DEVICE* device = &g_devices[i];

        if (device->state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (device->id != i)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (!wdkrnl_device_type_is_valid(device->type))
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (!wdkrnl_device_validate_lifecycle(device))
        {
            return WD_KRNL_FATAL_ERROR;
        }

        enumeration_count++;
    }

    if (enumeration_count != wdkrnl_device_enumerate_count())
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_validate_enumeration_system(void)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_device_validate_enumeration() != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_validate_all_resources() != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_validate_enable_system() != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_validate_driver_system() != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_error_is_valid(uint32_t error_code)
{
    switch (error_code)
    {
        case WD_DEVICE_ERROR_NONE:
        case WD_DEVICE_ERROR_GENERAL:
        case WD_DEVICE_ERROR_INITIALIZATION:
        case WD_DEVICE_ERROR_DRIVER:
        case WD_DEVICE_ERROR_RESOURCE:
        case WD_DEVICE_ERROR_HARDWARE:
        case WD_DEVICE_ERROR_TIMEOUT:
        case WD_DEVICE_ERROR_NOT_PRESENT:
        case WD_DEVICE_ERROR_UNSUPPORTED:
            return 1;

        default:
            return 0;
    }
}

const char* wdkrnl_device_error_name(uint32_t error_code)
{
    switch (error_code)
    {
        case WD_DEVICE_ERROR_NONE:
            return "NONE";

        case WD_DEVICE_ERROR_GENERAL:
            return "GENERAL";

        case WD_DEVICE_ERROR_INITIALIZATION:
            return "INITIALIZATION";

        case WD_DEVICE_ERROR_DRIVER:
            return "DRIVER";

        case WD_DEVICE_ERROR_RESOURCE:
            return "RESOURCE";

        case WD_DEVICE_ERROR_HARDWARE:
            return "HARDWARE";

        case WD_DEVICE_ERROR_TIMEOUT:
            return "TIMEOUT";

        case WD_DEVICE_ERROR_NOT_PRESENT:
            return "NOT_PRESENT";

        case WD_DEVICE_ERROR_UNSUPPORTED:
            return "UNSUPPORTED";

        default:
            return "UNKNOWN";
    }
}

int wdkrnl_device_record_error(WD_DEVICE* device, uint32_t error_code, uint8_t recoverable)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!wdkrnl_device_error_is_valid(error_code))
    {
        return WD_KRNL_FATAL_ERROR;
    }

    device->error_code = error_code;
    device->error_count++;
    device->error_recoverable = recoverable ? 1 : 0;

    device->initialized = 0;
    device->enabled = 0;

    if (wdkrnl_device_set_error(device) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

uint32_t wdkrnl_device_get_error(WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return WD_DEVICE_ERROR_GENERAL;
    }

    if (device == NULL)
    {
        return WD_DEVICE_ERROR_GENERAL;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return WD_DEVICE_ERROR_GENERAL;
    }

    return device->error_code;
}

uint32_t wdkrnl_device_get_error_count(WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return 0;
    }

    if (device == NULL)
    {
        return 0;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return 0;
    }

    return device->error_count;
}

uint8_t wdkrnl_device_is_recoverable(WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return 0;
    }

    if (device == NULL)
    {
        return 0;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return 0;
    }

    return device->error_recoverable;
}

int wdkrnl_device_clear_error(WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state != WD_DEVICE_STATE_ERROR)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    device->error_code = WD_DEVICE_ERROR_NONE;
    device->error_recoverable = 0;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_begin_recovery(WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state != WD_DEVICE_STATE_ERROR)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!device->error_recoverable)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    device->initialized = 0;
    device->enabled = 0;

    if (wdkrnl_device_clear_error(device) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!wdkrnl_device_validate_transition(WD_DEVICE_STATE_ERROR, WD_DEVICE_STATE_REGISTERED))
    {
        return WD_KRNL_FATAL_ERROR;
    }

    device->state = WD_DEVICE_STATE_REGISTERED;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_complete_recovery(WD_DEVICE* device, uint8_t success)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state != WD_DEVICE_STATE_REGISTERED)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!success)
    {
        return wdkrnl_device_record_error(device, WD_DEVICE_ERROR_HARDWARE, 0);
    }

    return wdkrnl_device_begin_initialize(device);
}

int wdkrnl_device_driver_report_error(
    WD_DEVICE_DRIVER* driver,
    WD_DEVICE* device,
    uint32_t error_code,
    uint8_t recoverable
)
{
    if (!g_device_driver_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (driver == NULL || device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->registered)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!driver->bound)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (driver->bound_device_id != device->id)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return wdkrnl_device_record_error(device, error_code, recoverable);
}

WD_DEVICE* wdkrnl_device_enumerate_error(uint32_t index)
{
    return wdkrnl_device_enumerate_state(WD_DEVICE_STATE_ERROR, index);
}

uint32_t wdkrnl_device_enumerate_error_count(void)
{
    return wdkrnl_device_enumerate_count_state(WD_DEVICE_STATE_ERROR);
}

int wdkrnl_device_validate_errors(WD_DEVICE* device)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state == WD_DEVICE_STATE_UNUSED)
    {
        return WD_KRNL_SUCCESS;
    }

    if (!wdkrnl_device_error_is_valid(device->error_code))
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (device->state == WD_DEVICE_STATE_ERROR)
    {
        if (device->enabled != 0)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (device->initialized != 0)
        {
            return WD_KRNL_FATAL_ERROR;
        }
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_validate_all_errors(void)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    for (uint32_t i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        WD_DEVICE* device = &g_devices[i];

        if (device->state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (wdkrnl_device_validate_errors(device)
            != WD_KRNL_SUCCESS)
        {
            return WD_KRNL_FATAL_ERROR;
        }
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_validate_error_system(void)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_device_validate_all_errors()
        != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_validate_enumeration_system()
        != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_operation_is_valid(WD_DEVICE_OPERATION operation)
{
    switch (operation)
    {
        case WD_DEVICE_OPERATION_GET:
        case WD_DEVICE_OPERATION_ENABLE:
        case WD_DEVICE_OPERATION_DISABLE:
        case WD_DEVICE_OPERATION_ENUMERATE:
        case WD_DEVICE_OPERATION_GET_STATE:
        case WD_DEVICE_OPERATION_GET_TYPE:
        case WD_DEVICE_OPERATION_GET_RESOURCE:
        case WD_DEVICE_OPERATION_GET_ERROR:
        case WD_DEVICE_OPERATION_RECOVER:
            return 1;

        default:
            return 0;
    }
}

int wdkrnl_device_validate_request(WD_DEVICE_REQUEST* request)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (request == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (!wdkrnl_device_operation_is_valid(
            request->operation))
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

WD_DEVICE* wdkrnl_device_interface_get(uint32_t device_id)
{
    if (!g_device_management_initialized)
    {
        return NULL;
    }

    return wdkrnl_device_get(device_id);
}

WD_DEVICE_STATE wdkrnl_device_interface_get_state(uint32_t device_id)
{
    WD_DEVICE* device;

    if (!g_device_management_initialized)
    {
        return WD_DEVICE_STATE_UNUSED;
    }

    device = wdkrnl_device_get(device_id);

    if (device == NULL)
    {
        return WD_DEVICE_STATE_UNUSED;
    }

    return wdkrnl_device_get_state(device);
}

WD_HARDWARE_TYPE wdkrnl_device_interface_get_type(uint32_t device_id)
{
    WD_DEVICE* device;

    if (!g_device_management_initialized)
    {
        return WD_HARDWARE_TYPE_OTHER;
    }

    device = wdkrnl_device_get(device_id);

    if (device == NULL)
    {
        return WD_HARDWARE_TYPE_OTHER;
    }

    return device->type;
}

int wdkrnl_device_interface_enable(uint32_t device_id)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return wdkrnl_device_enable_by_id(device_id);
}

int wdkrnl_device_interface_disable(uint32_t device_id)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return wdkrnl_device_disable_by_id(device_id);
}

WD_DEVICE* wdkrnl_device_interface_enumerate(uint32_t index)
{
    if (!g_device_management_initialized)
    {
        return NULL;
    }

    return wdkrnl_device_enumerate(index);
}

uint32_t wdkrnl_device_interface_get_count(void)
{
    if (!g_device_management_initialized)
    {
        return 0;
    }

    return wdkrnl_device_enumerate_count();
}

WD_DEVICE_RESOURCE* wdkrnl_device_interface_get_resource(uint32_t device_id, uint32_t resource_index)
{
    WD_DEVICE* device;

    if (!g_device_management_initialized)
    {
        return NULL;
    }

    device = wdkrnl_device_get(device_id);

    if (device == NULL)
    {
        return NULL;
    }

    return wdkrnl_device_get_resource(device, resource_index);
}

uint32_t wdkrnl_device_interface_get_error(uint32_t device_id)
{
    WD_DEVICE* device;

    if (!g_device_management_initialized)
    {
        return WD_DEVICE_ERROR_GENERAL;
    }

    device = wdkrnl_device_get(device_id);

    if (device == NULL)
    {
        return WD_DEVICE_ERROR_GENERAL;
    }

    return wdkrnl_device_get_error(device);
}

int wdkrnl_device_interface_recover(uint32_t device_id)
{
    WD_DEVICE* device;

    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    device = wdkrnl_device_get(device_id);

    if (device == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return wdkrnl_device_begin_recovery(device);
}

int wdkrnl_device_request(WD_DEVICE_REQUEST* request)
{
    if (wdkrnl_device_validate_request(request) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    switch (request->operation)
    {
        case WD_DEVICE_OPERATION_GET:
        {
            WD_DEVICE* device = wdkrnl_device_interface_get(request->device_id);

            if (device == NULL)
            {
                return WD_KRNL_FATAL_ERROR;
            }

            request->data = device;
            return WD_KRNL_SUCCESS;
        }

        case WD_DEVICE_OPERATION_ENABLE:
            return wdkrnl_device_interface_enable(request->device_id);

        case WD_DEVICE_OPERATION_DISABLE:
            return wdkrnl_device_interface_disable(request->device_id);

        case WD_DEVICE_OPERATION_ENUMERATE:
        {
            WD_DEVICE* device = wdkrnl_device_interface_enumerate(request->index);

            if (device == NULL)
            {
                return WD_KRNL_FATAL_ERROR;
            }

            request->data = device;
            return WD_KRNL_SUCCESS;
        }

        case WD_DEVICE_OPERATION_GET_STATE:
        {
            WD_DEVICE* device = wdkrnl_device_interface_get(request->device_id);

            if (device == NULL)
            {
                return WD_KRNL_FATAL_ERROR;
            }

            request->data = &device->state;
            return WD_KRNL_SUCCESS;
        }

        case WD_DEVICE_OPERATION_GET_TYPE:
        {
            WD_DEVICE* device = wdkrnl_device_interface_get(request->device_id);

            if (device == NULL)
            {
                return WD_KRNL_FATAL_ERROR;
            }

            request->data = &device->type;
            return WD_KRNL_SUCCESS;
        }

        case WD_DEVICE_OPERATION_GET_RESOURCE:
        {
            WD_DEVICE_RESOURCE* resource = wdkrnl_device_interface_get_resource(request->device_id, request->resource_index);

            if (resource == NULL)
            {
                return WD_KRNL_FATAL_ERROR;
            }

            request->data = resource;
            return WD_KRNL_SUCCESS;
        }

        case WD_DEVICE_OPERATION_GET_ERROR:
        {
            WD_DEVICE* device = wdkrnl_device_interface_get(request->device_id);

            if (device == NULL)
            {
                return WD_KRNL_FATAL_ERROR;
            }

            request->error_code = wdkrnl_device_get_error(device);

            return WD_KRNL_SUCCESS;
        }

        case WD_DEVICE_OPERATION_RECOVER:
            return wdkrnl_device_interface_recover(request->device_id);

        default:
            return WD_KRNL_FATAL_ERROR;
    }
}

int wdkrnl_device_validate_interface(void)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    for (uint32_t operation = 0; operation <= WD_DEVICE_OPERATION_RECOVER; operation++)
    {
        if (!wdkrnl_device_operation_is_valid((WD_DEVICE_OPERATION)operation))
        {
            return WD_KRNL_FATAL_ERROR;
        }
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_validate_lifecycle_system(void)
{
    uint32_t i;
    WD_DEVICE* device;

    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    for (i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        device = &g_devices[i];

        if (device->state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (!device->initialized &&
            device->state != WD_DEVICE_STATE_REGISTERED)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (device->state == WD_DEVICE_STATE_READY &&
            !device->initialized)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (device->state == WD_DEVICE_STATE_ERROR &&
            device->error_code == 0)
        {
            return WD_KRNL_FATAL_ERROR;
        }
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_device_validate_system(void)
{
    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_device_validate_lifecycle_system()
        != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_validate_type_system()
        != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_validate_resource_system()
        != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_validate_driver_system()
        != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_validate_enable_system()
        != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_validate_enumeration_system()
        != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_validate_error_system()
        != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_validate_interface()
        != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_state_validate(WD_POWER_STATE state)
{
    switch (state)
    {
        case WD_POWER_STATE_ON:
        case WD_POWER_STATE_IDLE:
        case WD_POWER_STATE_SLEEP:
        case WD_POWER_STATE_SHUTDOWN:
        case WD_POWER_STATE_REBOOT:
            return WD_KRNL_SUCCESS;

        default:
            return WD_KRNL_INIT_FAILED;
    }
}

int wdkrnl_device_power_state_validate(WD_DEVICE_POWER_STATE state)
{
    switch (state)
    {
        case WD_DEVICE_POWER_ON:
        case WD_DEVICE_POWER_IDLE:
        case WD_DEVICE_POWER_SLEEP:
        case WD_DEVICE_POWER_OFF:
            return WD_KRNL_SUCCESS;

        default:
            return WD_KRNL_INIT_FAILED;
    }
}

const char* wdkrnl_power_state_name(WD_POWER_STATE state)
{
    switch (state)
    {
        case WD_DEVICE_POWER_ON:
            return "ON";

        case WD_DEVICE_POWER_IDLE:
            return "IDLE";

        case WD_DEVICE_POWER_SLEEP:
            return "SLEEP";

        case WD_DEVICE_POWER_OFF:
            return "OFF";

        default:
            return "UNKNOWN";
    }
}

const char* wdkrnl_device_power_state_name(WD_DEVICE_POWER_STATE state)
{
    switch (state)
    {
        case WD_POWER_STATE_ON:
            return "ON";

        case WD_POWER_STATE_IDLE:
            return "IDLE";

        case WD_POWER_STATE_SLEEP:
            return "SLEEP";

        case WD_POWER_STATE_SHUTDOWN:
            return "SHUTDOWN";

        case WD_POWER_STATE_REBOOT:
            return "REBOOT";

        default:
            return "UNKNOWN";
    }
}

int wdkrnl_power_initialize(void)
{
    g_power_status.state = WD_POWER_STATE_ON;
    g_power_status.initialized = 1;
    g_power_status.charging_mode = 0;
    g_power_status.transition_active = 0;

    return WD_KRNL_SUCCESS;
}

WD_POWER_STATE wdkrnl_power_get_state(void)
{
    return g_power_status.state;
}

int wdkrnl_power_is_initialized(void)
{
    return g_power_status.initialized ? 1 : 0;
}

int wdkrnl_power_is_charging(void)
{
    return g_power_status.charging_mode ? 1 : 0;
}

int wdkrnl_power_validate(void)
{
    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_power_state_validate(g_power_status.state) != WD_KRNL_SUCCESS)
    {  
        return WD_KRNL_INIT_FAILED;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_validate_transition(WD_POWER_STATE current, WD_POWER_STATE target)
{
    if (wdkrnl_power_state_validate(current) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_power_state_validate(target) != WD_KRNL_SUCCESS)
    {    
        return WD_KRNL_INIT_FAILED;
    }

    if (current == target)
    { 
        return WD_KRNL_SUCCESS;
    }

    switch (current)
    {
        case WD_POWER_STATE_ON:
            if (target == WD_POWER_STATE_IDLE ||
                target == WD_POWER_STATE_SLEEP ||
                target == WD_POWER_STATE_SHUTDOWN ||
                target == WD_POWER_STATE_REBOOT)
                return WD_KRNL_SUCCESS;
            break;

        case WD_POWER_STATE_IDLE:
            if (target == WD_POWER_STATE_ON ||
                target == WD_POWER_STATE_SLEEP)
                return WD_KRNL_SUCCESS;
            break;

        case WD_POWER_STATE_SLEEP:
            if (target == WD_POWER_STATE_ON ||
                target == WD_POWER_STATE_SHUTDOWN ||
                target == WD_POWER_STATE_REBOOT)
                return WD_KRNL_SUCCESS;
            break;

        case WD_POWER_STATE_SHUTDOWN:
        case WD_POWER_STATE_REBOOT:
            break;

        default:
            break;
    }

    return WD_KRNL_INIT_FAILED;
}

int wdkrnl_power_transition(WD_POWER_STATE target)
{
    WD_POWER_STATE current;

    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    current = g_power_status.state;

    if (wdkrnl_power_validate_transition(current, target) != WD_KRNL_SUCCESS)
    {  
        return WD_KRNL_INIT_FAILED;
    }

    if (current == target)
    {
        return WD_KRNL_SUCCESS;
    }

    if (g_power_status.transition_active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    g_power_status.transition_active = 1;

    g_power_status.state = target;

    g_power_status.transition_active = 0;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_is_transitioning(void)
{
    return g_power_status.transition_active ? 1 : 0;
}

int wdkrnl_device_power_transition(
    WD_DEVICE* device,
    WD_DEVICE_POWER_STATE target)
{
    if (device == NULL)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!device->present)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!device->power_management_supported)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device->power_transition_active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (target < WD_DEVICE_POWER_ON ||
        target > WD_DEVICE_POWER_OFF)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device->power_state == target)
    {
        return WD_KRNL_SUCCESS;
    }

    if (target == WD_DEVICE_POWER_SLEEP &&
        !device->wake_capable)
    {
        return WD_KRNL_INIT_FAILED;
    }

    device->power_transition_active = 1;

    device->power_state = target;

    device->power_transition_active = 0;

    return WD_KRNL_SUCCESS;
}

WD_DEVICE_POWER_STATE wdkrnl_device_power_get(WD_DEVICE* device);
int wdkrnl_device_power_is_on(WD_DEVICE* device);
int wdkrnl_device_power_is_idle(WD_DEVICE* device);
int wdkrnl_device_power_is_sleeping(WD_DEVICE* device);
int wdkrnl_device_power_is_off(WD_DEVICE* device);

int wdkrnl_device_power_validate(WD_DEVICE* device);
int wdkrnl_device_power_validate_all(void)
{
    uint32_t i;
    WD_DEVICE* device;

    if (!g_device_management_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    for (i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        device = &g_devices[i];

        if (device->state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (!device->present)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (device->power_state < WD_DEVICE_POWER_ON ||
            device->power_state > WD_DEVICE_POWER_OFF)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (device->power_transition_active > 1)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (device->power_management_supported > 1)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (device->wake_capable > 1)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (device->power_state == WD_DEVICE_POWER_SLEEP &&
            device->power_management_supported &&
            !device->wake_capable)
        {
            return WD_KRNL_FATAL_ERROR;
        }
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_prepare_sleep(void)
{
    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_power_status.transition_active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    g_power_status.transition_active = 1;

    if (wdkrnl_device_power_validate_all() != WD_KRNL_SUCCESS)
    {
        g_power_status.transition_active = 0;
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_enter_sleep(void)
{
    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_power_status.transition_active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    g_power_status.state = WD_POWER_STATE_SLEEP;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_wake(void)
{
    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_power_status.transition_active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_power_status.state != WD_POWER_STATE_SLEEP)
    {
        return WD_KRNL_INIT_FAILED;
    }

    g_power_status.state = WD_POWER_STATE_ON;

    g_power_status.transition_active = 0;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_sleep(void)
{
    int result;

    result = wdkrnl_power_prepare_sleep();

    if (result != WD_KRNL_SUCCESS)
    {
        return result;
    }

    result = wdkrnl_power_enter_sleep();

    if (result != WD_KRNL_SUCCESS)
    {   
        return result;
    }

    return wdkrnl_power_wake();
}

int wdkrnl_power_transition(WD_POWER_STATE target);
WD_DEVICE_POWER_STATE wdkrnl_device_power_get(WD_DEVICE* device);
int wdkrnl_power_is_sleeping(void);

int wdkrnl_power_set_charging_mode(uint8_t enabled)
{
    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    g_power_status.charging_mode = enabled ? 1 : 0;

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_charging_sleep(void)
{
    uint32_t index;
    uint32_t count;

    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_power_status.charging_mode)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (g_power_status.state != WD_POWER_STATE_SLEEP)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    count = wdkrnl_device_enumerate_count();

    for (index = 0; index < count; index++)
    {
        WD_DEVICE* device = wdkrnl_device_enumerate(index);

        if (device == NULL)
        {
            continue;
        }

        wdkrnl_device_power_transition(device, WD_DEVICE_POWER_OFF);
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_exit_charging_sleep(void);
int wdkrnl_power_validate_charging_sleep(void);

int wdkrnl_power_is_charging(void);

void wdkrnl_power_halt(void)
{
#if defined(__x86_64__) || defined(__i386__)
    __asm__ volatile ("cli");

    for (;;)
    {
        __asm__ volatile ("hlt");
    }
#else
    for (;;)
    {
        for (volatile uint32_t i = 0; i < 1000000; ++i)
        {
        }
    }
#endif
}

int wdkrnl_power_shutdown(void)
{
    uint32_t index;
    uint32_t count;

    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_power_status.transition_active)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    g_power_status.transition_active = 1;

    // clean up clean up everybody clean the fuck up

    count = wdkrnl_device_enumerate_count();

    for (index = 0; index < count; index++)
    {
        WD_DEVICE* device = wdkrnl_device_enumerate(index);

        if (device == NULL)
        {
            continue;
        }

        wdkrnl_device_power_transition(device, WD_DEVICE_POWER_OFF);
    }

    if (wdkrnl_power_transition(WD_POWER_STATE_SHUTDOWN) != WD_KRNL_SUCCESS)
    {
        g_power_status.transition_active = 0;
        return WD_KRNL_FATAL_ERROR;
    }

    wdkrnl_power_halt();

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_reboot(void)
{
    uint32_t index;
    uint32_t count;

    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_power_status.transition_active)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    g_power_status.transition_active = 1;

    count = wdkrnl_device_enumerate_count();

    for (index = 0; index < count; index++)
    {
        WD_DEVICE* device = wdkrnl_device_enumerate(index);

        if (device == NULL)
        {
            continue;
        }

        wdkrnl_device_power_transition(device, WD_DEVICE_POWER_OFF);
    }

    if (wdkrnl_power_transition(WD_POWER_STATE_REBOOT) != WD_KRNL_SUCCESS)
    {
        g_power_status.transition_active = 0;
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_operation_validate(WD_POWER_OPERATION operation)
{
    switch (operation)
    {
        case WD_POWER_OPERATION_SLEEP:
        case WD_POWER_OPERATION_CHARGING_SLEEP:
        case WD_POWER_OPERATION_SHUTDOWN:
        case WD_POWER_OPERATION_REBOOT:
        case WD_POWER_OPERATION_GET_STATE:
        case WD_POWER_OPERATION_GET_STATUS:
            return WD_KRNL_SUCCESS;

        default:
            return WD_KRNL_FATAL_ERROR;
    }
}

int wdkrnl_power_request(WD_POWER_REQUEST* request)
{
    if (request == NULL)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_power_operation_validate(request->operation) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    switch (request->operation)
    {
        case WD_POWER_OPERATION_SLEEP:
            return wdkrnl_power_sleep();

        case WD_POWER_OPERATION_CHARGING_SLEEP:
            return wdkrnl_power_charging_sleep();

        case WD_POWER_OPERATION_SHUTDOWN:
            return wdkrnl_power_shutdown();

        case WD_POWER_OPERATION_REBOOT:
            return wdkrnl_power_reboot();

        case WD_POWER_OPERATION_GET_STATE:
            if (request->data == NULL)
            {
                return WD_KRNL_FATAL_ERROR;
            }

            *(WD_POWER_STATE*)request->data = wdkrnl_power_get_state();

            return WD_KRNL_SUCCESS;

        case WD_POWER_OPERATION_GET_STATUS:
            if (request->data == NULL)
            {
                return WD_KRNL_FATAL_ERROR;
            }

            *(WD_POWER_STATUS*)request->data = g_power_status;

            return WD_KRNL_SUCCESS;

        default:
            return WD_KRNL_FATAL_ERROR;
    }
}

int wdkrnl_power_validate_shutdown(void);
int wdkrnl_power_validate_reboot(void);

int wdkrnl_power_validate_interface(void)
{
    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_power_status.state < WD_POWER_STATE_ON ||
        g_power_status.state > WD_POWER_STATE_SLEEP)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (g_power_status.charging_mode > 1)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (g_power_status.transition_active > 1)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_validate_device_states(void)
{
    uint32_t i;
    WD_DEVICE* device;

    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    for (i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        device = &g_devices[i];

        if (device->state == WD_DEVICE_STATE_UNUSED)
        {
            continue;
        }

        if (!device->present)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (!device->power_management_supported &&
            device->power_state != WD_DEVICE_POWER_ON)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (device->power_state == WD_DEVICE_POWER_SLEEP &&
            !device->wake_capable)
        {
            return WD_KRNL_FATAL_ERROR;
        }

        if (device->state == WD_DEVICE_STATE_DISABLED &&
            device->power_state == WD_DEVICE_POWER_ON)
        {
            return WD_KRNL_FATAL_ERROR;
        }
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_validate_system(void)
{
    if (!g_power_status.initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_power_validate() != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_device_power_validate_all() != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_power_validate_interface() != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_power_validate_device_states() != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    if (wdkrnl_power_validate_charging_mode() != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

int wdkrnl_power_validate_charging_mode(void)
{
    if (g_power_status.charging_mode > 1)
    {
        return WD_KRNL_FATAL_ERROR;
    }

    return WD_KRNL_SUCCESS;
}

static void wdkrnl_ipc_initialize(void)
{
    g_ipc_endpoint_count = 0;
    g_ipc_message_count = 0;
    g_ipc_initialized = 0;

    for (uint32_t i = 0; i < WD_IPC_MAX_ENDPOINTS; i++)
    {
        g_ipc_endpoints[i].id = 0;
        g_ipc_endpoints[i].process_id = 0;
        g_ipc_endpoints[i].thread_id = 0;
        g_ipc_endpoints[i].active = 0;
    }

    for (uint32_t i = 0; i < WD_IPC_MAX_MESSAGES; i++)
    {
        g_ipc_messages[i].sender_id = 0;
        g_ipc_messages[i].receiver_id = 0;
        g_ipc_messages[i].type = WD_IPC_MESSAGE_NONE;
        g_ipc_messages[i].size = 0;
        g_ipc_messages[i].valid = 0;

        for (uint32_t j = 0; j < WD_IPC_MAX_MESSAGE_DATA; j++)
        {
            g_ipc_messages[i].data[j] = 0;
        }
    }

    g_ipc_queue_count = 0;

    for (uint32_t i = 0;
        i < WD_IPC_MAX_QUEUES;
        i++)
    {
        g_ipc_queues[i].id = 0;
        g_ipc_queues[i].endpoint_id = 0;

        g_ipc_queues[i].head = 0;
        g_ipc_queues[i].tail = 0;
        g_ipc_queues[i].count = 0;

        g_ipc_queues[i].active = 0;

        for (uint32_t j = 0; j < WD_IPC_QUEUE_SIZE; j++)
        {
            g_ipc_queues[i].messages[j].sender_id = 0;
            g_ipc_queues[i].messages[j].receiver_id = 0;
            g_ipc_queues[i].messages[j].type = WD_IPC_MESSAGE_NONE;
            g_ipc_queues[i].messages[j].size = 0;
            g_ipc_queues[i].messages[j].valid = 0;
        }
    }

    g_ipc_channel_count = 0;

    for (uint32_t i = 0; i < WD_IPC_MAX_CHANNELS; i++)
    {
        g_ipc_channels[i].id = 0;

        g_ipc_channels[i].source_endpoint = 0;
        g_ipc_channels[i].target_endpoint = 0;

        g_ipc_channels[i].queue_id = 0;

        g_ipc_channels[i].state = WD_IPC_CHANNEL_STATE_UNUSED;

        g_ipc_channels[i].active = 0;
    }

    g_ipc_permission_count = 0;

    for (uint32_t i = 0; i < WD_IPC_MAX_PERMISSION_SETS; i++)
    {
        g_ipc_permissions[i].endpoint_id = 0;

        g_ipc_permissions[i].send = 0;
        g_ipc_permissions[i].receive = 0;
        g_ipc_permissions[i].connect = 0;
        g_ipc_permissions[i].close = 0;

        g_ipc_permissions[i].active = 0;
    }

    g_ipc_initialized = 1;
}

static uint32_t wdkrnl_ipc_queue_create(uint32_t endpoint_id)
{
    if (!g_ipc_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (endpoint_id >= WD_IPC_MAX_ENDPOINTS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_ipc_endpoints[endpoint_id].active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_ipc_queue_count >= WD_IPC_MAX_QUEUES)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_IPC_QUEUE* queue = 0;

    for (uint32_t i = 0; i < WD_IPC_MAX_QUEUES; i++)
    {
        if (!g_ipc_queues[i].active)
        {
            queue = &g_ipc_queues[i];
            break;
        }
    }

    if (queue == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    queue->id = (uint32_t)(queue - g_ipc_queues);

    queue->endpoint_id = endpoint_id;

    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;

    queue->active = 1;

    g_ipc_queue_count++;

    return queue->id;
}

static uint32_t wdkrnl_ipc_queue_send(uint32_t queue_id, const WD_IPC_MESSAGE* message)
{
    if (!g_ipc_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (message == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (queue_id >= WD_IPC_MAX_QUEUES)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_IPC_QUEUE* queue = &g_ipc_queues[queue_id];

    if (!queue->active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (queue->count >= WD_IPC_QUEUE_SIZE)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (message->size > WD_IPC_MAX_MESSAGE_DATA)
    {
        return WD_KRNL_INIT_FAILED;
    }

    queue->messages[queue->tail] = *message;

    queue->messages[queue->tail].valid = 1;

    queue->tail = (queue->tail + 1) % WD_IPC_QUEUE_SIZE;

    queue->count++;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_ipc_queue_receive(uint32_t queue_id, WD_IPC_MESSAGE* message)
{
    if (!g_ipc_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (message == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (queue_id >= WD_IPC_MAX_QUEUES)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_IPC_QUEUE* queue = &g_ipc_queues[queue_id];

    if (!queue->active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (queue->count == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!queue->messages[queue->head].valid)
    {
        return WD_KRNL_INIT_FAILED;
    }

    *message = queue->messages[queue->head];

    queue->messages[queue->head].valid = 0;

    queue->head = (queue->head + 1) % WD_IPC_QUEUE_SIZE;

    queue->count--;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_ipc_queue_get_count(uint32_t queue_id)
{
    if (queue_id >= WD_IPC_MAX_QUEUES)
    {
        return 0;
    }

    if (!g_ipc_queues[queue_id].active)
    {
        return 0;
    }

    return g_ipc_queues[queue_id].count;
}

static uint32_t wdkrnl_ipc_channel_create(
    uint32_t source_endpoint,
    uint32_t target_endpoint
)
{
    if (!g_ipc_initialized)
    {   
        return WD_KRNL_INIT_FAILED;
    }

    if (source_endpoint >= WD_IPC_MAX_ENDPOINTS)
    {  
        return WD_KRNL_INIT_FAILED;
    }

    if (target_endpoint >= WD_IPC_MAX_ENDPOINTS)
    {    
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_ipc_endpoints[source_endpoint].active)
    {    
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_ipc_endpoints[target_endpoint].active)
    { 
        return WD_KRNL_INIT_FAILED;
    }

    if (g_ipc_channel_count >= WD_IPC_MAX_CHANNELS)
    { 
        return WD_KRNL_INIT_FAILED;
    }

    WD_IPC_CHANNEL* channel = 0;

    for (uint32_t i = 0; i < WD_IPC_MAX_CHANNELS; i++)
    {
        if (!g_ipc_channels[i].active)
        {
            channel = &g_ipc_channels[i];
            break;
        }
    }

    if (channel == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    uint32_t queue_id = wdkrnl_ipc_queue_create(target_endpoint);

    if (queue_id == WD_KRNL_INIT_FAILED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    channel->id = (uint32_t)(channel - g_ipc_channels);

    channel->source_endpoint = source_endpoint;

    channel->target_endpoint = target_endpoint;

    channel->queue_id = queue_id;

    channel->state = WD_IPC_CHANNEL_STATE_CREATED;

    channel->active = 1;

    g_ipc_channel_count++;

    return channel->id;
}

static uint32_t wdkrnl_ipc_channel_connect(uint32_t channel_id)
{
    if (!g_ipc_initialized)
    {  
        return WD_KRNL_INIT_FAILED;
    }

    if (channel_id >= WD_IPC_MAX_CHANNELS)
    { 
        return WD_KRNL_INIT_FAILED;
    }

    WD_IPC_CHANNEL* channel = &g_ipc_channels[channel_id];

    if (!channel->active)
    { 
        return WD_KRNL_INIT_FAILED;
    }

    if (channel->state != WD_IPC_CHANNEL_STATE_CREATED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    channel->state = WD_IPC_CHANNEL_STATE_CONNECTED;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_ipc_channel_close(uint32_t channel_id)
{
    if (!g_ipc_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (channel_id >= WD_IPC_MAX_CHANNELS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_IPC_CHANNEL* channel = &g_ipc_channels[channel_id];

    if (!channel->active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (channel->state == WD_IPC_CHANNEL_STATE_CLOSED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    channel->state = WD_IPC_CHANNEL_STATE_CLOSED;

    channel->active = 0;
    
    g_ipc_channel_count--;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_ipc_thread_wait(WD_THREAD* thread, WD_IPC_WAIT_TYPE wait_type, uint32_t wait_id)
{
    if (thread == 0)
    { 
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->initialized)
    { 
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->state == WD_THREAD_STATE_TERMINATED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->state == WD_THREAD_STATE_ERROR)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wait_type == WD_IPC_WAIT_NONE)
    { 
        return WD_KRNL_INIT_FAILED;
    }

    thread->ipc_wait_type = wait_type;

    thread->ipc_wait_id = wait_id;

    thread->ipc_waiting = 1;

    thread->state = WD_THREAD_STATE_BLOCKED;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_ipc_thread_wake(WD_THREAD* thread)
{
    if (thread == 0)
    {  
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->initialized)
    {    
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->ipc_waiting)
    {    
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->state != WD_THREAD_STATE_BLOCKED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    thread->ipc_wait_type = WD_IPC_WAIT_NONE;

    thread->ipc_wait_id = 0;

    thread->ipc_waiting = 0;

    thread->state = WD_THREAD_STATE_READY;

    return WD_KRNL_SUCCESS;
}

static WD_THREAD* wdkrnl_ipc_find_waiting_thread(WD_IPC_WAIT_TYPE wait_type, uint32_t wait_id)
{
    for (uint32_t i = 0; i < WD_THREAD_MAX_THREADS; i++)
    {
        WD_THREAD* thread = &g_threads[i];

        if (!thread->initialized)
        { 
            continue;
        }

        if (!thread->ipc_waiting)
        {   
            continue;
        }

        if (thread->ipc_wait_type != wait_type)
        {
            continue;
        }

        if (thread->ipc_wait_id != wait_id)
        {
            continue;
        }

        if (thread->state != WD_THREAD_STATE_BLOCKED)
        {
            continue;
        }

        return thread;
    }

    return 0;
}

static uint32_t wdkrnl_ipc_permission_create(
    uint32_t endpoint_id,
    uint8_t send,
    uint8_t receive,
    uint8_t connect,
    uint8_t close
)
{
    if (!g_ipc_initialized)
    {  
        return WD_KRNL_INIT_FAILED;
    }

    if (endpoint_id >= WD_IPC_MAX_ENDPOINTS)
    {   
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_ipc_endpoints[endpoint_id].active)
    {   
        return WD_KRNL_INIT_FAILED;
    }

    if (g_ipc_permission_count >= WD_IPC_MAX_PERMISSION_SETS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_IPC_PERMISSION_SET* permission = 0;

    for (uint32_t i = 0; i < WD_IPC_MAX_PERMISSION_SETS; i++)
    {
        if (!g_ipc_permissions[i].active)
        {
            permission = &g_ipc_permissions[i];
            break;
        }
    }

    if (permission == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    permission->endpoint_id = endpoint_id;

    permission->send = send;
    permission->receive = receive;
    permission->connect = connect;
    permission->close = close;

    permission->active = 1;

    g_ipc_permission_count++;

    return (uint32_t)(permission - g_ipc_permissions);
}

static uint32_t wdkrnl_ipc_permission_check(uint32_t endpoint_id, WD_IPC_PERMISSION permission_type)
{
    if (!g_ipc_initialized)
    {   
        return WD_KRNL_INIT_FAILED;
    }

    if (endpoint_id >= WD_IPC_MAX_ENDPOINTS)
    {   
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_ipc_endpoints[endpoint_id].active)
    { 
        return WD_KRNL_INIT_FAILED;
    }

    for (uint32_t i = 0; i < WD_IPC_MAX_PERMISSION_SETS; i++)
    {
        WD_IPC_PERMISSION_SET* permission = &g_ipc_permissions[i];

        if (!permission->active)
        {   
            continue;
        }

        if (permission->endpoint_id != endpoint_id)
        {
            continue;
        }

        switch (permission_type)
        {
            case WD_IPC_PERMISSION_SEND:
                return permission->send ? WD_KRNL_SUCCESS : WD_KRNL_INIT_FAILED;

            case WD_IPC_PERMISSION_RECEIVE:
                return permission->receive ? WD_KRNL_SUCCESS : WD_KRNL_INIT_FAILED;

            case WD_IPC_PERMISSION_CONNECT:
                return permission->connect ? WD_KRNL_SUCCESS : WD_KRNL_INIT_FAILED;

            case WD_IPC_PERMISSION_CLOSE:
                return permission->close ? WD_KRNL_SUCCESS : WD_KRNL_INIT_FAILED;

            default:
                return WD_KRNL_INIT_FAILED;
        }
    }

    return WD_KRNL_INIT_FAILED;
}

static uint32_t wdkrnl_ipc_channel_validate(uint32_t channel_id)
{
    if (!g_ipc_initialized)
    {  
        return WD_KRNL_INIT_FAILED;
    }

    if (channel_id >= WD_IPC_MAX_CHANNELS)
    {  
        return WD_KRNL_INIT_FAILED;
    }

    WD_IPC_CHANNEL* channel = &g_ipc_channels[channel_id];

    if (!channel->active)
    {   
        return WD_KRNL_INIT_FAILED;
    }

    if (channel->source_endpoint >= WD_IPC_MAX_ENDPOINTS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (channel->target_endpoint >= WD_IPC_MAX_ENDPOINTS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_ipc_endpoints[channel->source_endpoint].active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_ipc_endpoints[channel->target_endpoint].active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (channel->queue_id >= WD_IPC_MAX_QUEUES)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!g_ipc_queues[channel->queue_id].active)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_scheduler_wake_thread(WD_THREAD* thread)
{
    if (thread == 0)
    {    
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->initialized)
    {    
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->state != WD_THREAD_STATE_BLOCKED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->ipc_waiting)
    {   
        return WD_KRNL_INIT_FAILED;
    }

    return wdkrnl_ipc_thread_wake(thread);
}

static uint32_t wdkrnl_scheduler_wake_ipc(WD_IPC_WAIT_TYPE wait_type, uint32_t wait_id)
{
    WD_THREAD* thread = wdkrnl_ipc_find_waiting_thread(wait_type, wait_id);

    if (thread == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return wdkrnl_scheduler_wake_thread(thread);
}

static uint32_t wdkrnl_scheduler_current_valid(void)
{
    if (g_current_thread >= WD_THREAD_MAX_THREADS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_THREAD* thread = &g_threads[g_current_thread];

    if (!thread->initialized)
    {   
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->state == WD_THREAD_STATE_TERMINATED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->state == WD_THREAD_STATE_ERROR)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_scheduler_reschedule(void)
{
    if (wdkrnl_scheduler_current_valid() != WD_KRNL_SUCCESS)
    {
        g_current_thread = 0;
    }

    return wdkrnl_scheduler_select();
}

static WD_IPC_ENDPOINT* wdkrnl_ipc_get_endpoint(uint32_t endpoint_id)
{
    if (!g_ipc_initialized)
    {   
        return 0;
    }

    if (endpoint_id >= WD_IPC_MAX_ENDPOINTS)
    {   
        return 0;
    }

    WD_IPC_ENDPOINT* endpoint = &g_ipc_endpoints[endpoint_id];

    if (!endpoint->active)
    {   
        return 0;
    }

    return endpoint;
}

static WD_IPC_CHANNEL* wdkrnl_ipc_get_channel(uint32_t channel_id)
{
    if (!g_ipc_initialized)
    {   
        return 0;
    }

    if (channel_id >= WD_IPC_MAX_CHANNELS)
    {   
        return 0;
    }

    WD_IPC_CHANNEL* channel = &g_ipc_channels[channel_id];

    if (!channel->active)
    {  
        return 0;
    }

    return channel;
}

static uint32_t wdkrnl_ipc_channel_send(uint32_t channel_id, const WD_IPC_MESSAGE* message)
{
    WD_IPC_CHANNEL* channel = wdkrnl_ipc_get_channel(channel_id);

    if (channel == 0)
    {    
        return WD_KRNL_INIT_FAILED;
    }

    if (channel->state != WD_IPC_CHANNEL_STATE_CONNECTED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (message == 0)
    {    
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_ipc_channel_validate(channel_id) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_ipc_permission_check(channel->source_endpoint, WD_IPC_PERMISSION_SEND) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_IPC_MESSAGE outgoing = *message;

    outgoing.sender_id = channel->source_endpoint;

    outgoing.receiver_id = channel->target_endpoint;

    uint32_t result = wdkrnl_ipc_queue_send(channel->queue_id, &outgoing);

    if (result != WD_KRNL_SUCCESS)
    {  
        return result;
    }

    wdkrnl_scheduler_wake_ipc(WD_IPC_WAIT_MESSAGE, channel->queue_id);

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_ipc_channel_receive(uint32_t channel_id, WD_IPC_MESSAGE* message)
{
    WD_IPC_CHANNEL* channel = wdkrnl_ipc_get_channel(channel_id);

    if (channel == 0)
    {  
        return WD_KRNL_INIT_FAILED;
    }

    if (message == 0)
    {  
        return WD_KRNL_INIT_FAILED;
    }

    if (channel->state != WD_IPC_CHANNEL_STATE_CONNECTED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_ipc_channel_validate(channel_id) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_ipc_permission_check(channel->target_endpoint, WD_IPC_PERMISSION_RECEIVE) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return wdkrnl_ipc_queue_receive(channel->queue_id, message);
}

static uint8_t wdkrnl_ipc_is_initialized(void)
{
    return g_ipc_initialized;
}

static uint32_t wdkrnl_ipc_get_endpoint_count(void)
{
    return g_ipc_endpoint_count;
}

static uint32_t wdkrnl_ipc_get_channel_count(void)
{
    return g_ipc_channel_count;
}

static uint32_t wdkrnl_ipc_get_queue_count(void)
{
    return g_ipc_queue_count;
}



static uint32_t wdkrnl_process_create(
    const char* name,
    uint64_t image_base,
    uint64_t image_size,
    uint64_t entry_address
)
{
    if (name == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (image_base == 0 || image_size == 0 || entry_address == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_process_count >= WD_PROCESS_MAX_PROCESSES)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_PROCESS* process = 0;
    
    for (uint32_t i = 0; i < WD_PROCESS_MAX_PROCESSES; i++)
    {
        if (g_processes[i].state == WD_PROCESS_STATE_UNUSED)
        {
            process = &g_processes[i];
            break;
        }
    }

    if (process == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    process->id = (uint32_t)(process - g_processes);

    process->state = WD_PROCESS_STATE_CREATED;

    process->image_base = image_base;

    process->image_size = image_size;

    process->entry_address = entry_address;

    process->stack_base = 0;
    process->stack_size = 0;

    if (wdkrnl_process_create_stack(process) != WD_KRNL_SUCCESS)
    {
        process->state = WD_PROCESS_STATE_UNUSED;

        process->loaded = 0;

        return WD_KRNL_INIT_FAILED;
    }

    process->loaded = 1;

    process->context.rip =
    process->entry_address;

    process->context.rsp =
        process->stack_base +
        process->stack_size;

    process->context.rbp =
        process->context.rsp;

    process->context.rflags =
        0x202;


    for (uint32_t i = 0; i < WD_PROCESS_MAX_NAME; i++)
    {
        process->name[i] = '\0';
    }

    uint32_t i = 0;

    while(name[i] != '\0' && i < WD_PROCESS_MAX_NAME - 1)
    {
        process->name[i] = name[i];
        i++;
    }

    process->name[i] = '\0';

    g_process_count++;

    process->state = WD_PROCESS_STATE_READY;

    if (wdkrnl_process_prepare_context(process) != WD_KRNL_SUCCESS)
    {
        process->state = WD_PROCESS_STATE_ERROR;

        return WD_KRNL_INIT_FAILED;
    }

    return process->id;
}

static uint8_t wdkrnl_memory_is_page_aligned(uint64_t address)
{
    return (address % WD_MEMORY_PAGE_SIZE) == 0;
}

static uint64_t wdkrnl_memory_align_size(uint64_t size)
{
    uint64_t remainder = size % WD_MEMORY_PAGE_SIZE;

    if (remainder == 0)
    {
        return size;
    }

    return size + (WD_MEMORY_PAGE_SIZE - remainder);
}

static uint32_t wdkrnl_process_prepare_context(WD_PROCESS* process)
{
    if (process == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (process->state != WD_PROCESS_STATE_READY)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!process->loaded)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (process->entry_address == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (process->stack_base == 0 || process->stack_size == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    process->context.rip = process->entry_address;

    process->context.rsp = process->stack_base + process->stack_size;

    process->context.rbp = process->context.rsp;

    process->context.rax = 0;
    process->context.rbx = 0;
    process->context.rcx = 0;
    process->context.rdx = 0;

    process->context.rsi = 0;
    process->context.rdi = 0;

    process->context.r8 = 0;
    process->context.r9 = 0;
    process->context.r10 = 0;
    process->context.r11 = 0;
    process->context.r12 = 0;
    process->context.r13 = 0;
    process->context.r14 = 0;
    process->context.r15 = 0;

    process->context.rflags = 0x202;

    return WD_KRNL_SUCCESS;
}

static void wdkrnl_device_initialize(void)
{
    g_device_count = 0;
    g_device_management_initialized = 0;

    for (uint32_t i = 0; i < WD_DEVICE_MAX_DEVICES; i++)
    {
        g_devices[i].id = 0;

        g_devices[i].type = WD_HARDWARE_TYPE_UNKNOWN;

        g_devices[i].state = WD_DEVICE_STATE_UNUSED;

        g_devices[i].vendor_id = 0;
        g_devices[i].device_id = 0;

        g_devices[i].present = 0;
        g_devices[i].enabled = 0;
        g_devices[i].initialized = 0;

        g_devices[i].resource_count = 0;

        for (uint32_t j = 0; j < WD_DEVICE_MAX_RESOURCES; j++)
        {
            g_devices[i].resources[j].type = WD_DEVICE_RESOURCE_NONE;
            g_devices[i].resources[j].start = 0;
            g_devices[i].resources[j].length = 0;
            g_devices[i].resources[j].flags = 0;
            g_devices[i].resources[j].assigned = 0;
        }
        
        for (uint32_t j = 0; j < WD_DEVICE_MAX_NAME; j++)
        {
            g_devices[i].name[j] = '\0';
        }
    }

    g_device_management_initialized = 1;

    if (!wdkrnl_device_validate_types())
    {
        g_device_management_initialized = 0;
    }
}

static uint32_t wdkrnl_pe_validate_dos_header(const WD_PE_DOS_HEADER* header)
{
    if (header == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (header->e_magic != WD_PE_DOS_SIGNATURE)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_pe_validate_signature(
    const uint8_t* image,
    uint64_t image_size,
    uint32_t pe_offset
)
{
    if (image == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (image_size < pe_offset + 4)
    {
        return WD_KRNL_INIT_FAILED;
    }

    uint32_t signature = ((uint32_t)image[pe_offset]) | ((uint32_t)image[pe_offset + 1] << 8) | ((uint32_t)image[pe_offset + 2] << 16) | ((uint32_t)image[pe_offset + 3] << 24);

    if (signature != WD_PE_SIGNATURE)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_pe_validate_machine(uint16_t machine)
{
#if defined(__x86_64__)

    if (machine != WD_PE_MACHINE_X86_64)
    {
        return WD_KRNL_INIT_FAILED;
    }

#elif defined(__i386__)

    if (machine != WD_PE_MACHINE_X86)
    {
        return WD_KRNL_INIT_FAILED;
    }

#else

    return WD_KRNL_INIT_FAILED;

#endif

    return WD_KRNL_SUCCESS;
}

static volatile WD_KRNL_ERROR_CODE g_kernel_error = WD_KRNL_ERROR_NONE;

static void wdkrnl_process_initialize(void)
{
    g_process_count = 0;
    g_current_process = 0;

    for (uint32_t i = 0; i < WD_PROCESS_MAX_PROCESSES; i++)
    {
        g_processes[i].id = 0;

        g_processes[i].state =
            WD_PROCESS_STATE_UNUSED;

        g_processes[i].image_base = 0;
        g_processes[i].image_size = 0;
        g_processes[i].entry_address = 0;

        g_processes[i].stack_base = 0;
        g_processes[i].stack_size = 0;

        g_processes[i].context.rip = 0;
        g_processes[i].context.rsp = 0;
        g_processes[i].context.rbp = 0;

        g_processes[i].context.rax = 0;
        g_processes[i].context.rbx = 0;
        g_processes[i].context.rcx = 0;
        g_processes[i].context.rdx = 0;

        g_processes[i].context.rsi = 0;
        g_processes[i].context.rdi = 0;

        g_processes[i].context.r8 = 0;
        g_processes[i].context.r9 = 0;
        g_processes[i].context.r10 = 0;
        g_processes[i].context.r11 = 0;
        g_processes[i].context.r12 = 0;
        g_processes[i].context.r13 = 0;
        g_processes[i].context.r14 = 0;
        g_processes[i].context.r15 = 0;

        g_processes[i].context.rflags = 0;

        g_processes[i].loaded = 0;

        for (uint32_t j = 0; j < WD_PROCESS_MAX_NAME; j++)
        {
            g_processes[i].name[j] = '\0';
        }
    }
}

static void wdkrnl_filesystem_initialize(void)
{
    g_filesystem_entry_count = 0;
    g_filesystem_initialized = 0;
    g_filesystem_mounted = 0;

    for (uint32_t i = 0; i < WD_FS_MAX_FILES; i++)
    {
        g_filesystem_entries[i].id = 0;

        g_filesystem_entries[i].type = WD_FS_TYPE_UNKNOWN;

        g_filesystem_entries[i].size = 0;
        g_filesystem_entries[i].storage_offset = 0;

        g_filesystem_entries[i].exists = 0;
        g_filesystem_entries[i].readable = 0;
        g_filesystem_entries[i].writable = 0;

        for (uint32_t j = 0; j < WD_FS_MAX_NAME; j++)
        {
            g_filesystem_entries[i].name[j] = '\0';
        }

        for (uint32_t j = 0; j < WD_FS_MAX_PATH; j++)
        {
            g_filesystem_entries[i].path[j] = '\0';
        }
    }

    g_filesystem_initialized = 1;
}

static uint32_t wd_krnl_filesystem_register_entry(
    WD_FS_ENTRY_TYPE type,
    const char* name,
    const char* path,
    uint64_t size,
    uint64_t storage_offset,
    uint8_t readable,
    uint8_t writable
)
{
    if (!g_filesystem_initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_filesystem_entry_count >= WD_FS_MAX_FILES)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (name == 0 || path == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_FS_ENTRY* entry = &g_filesystem_entries[g_filesystem_entry_count];

    entry->id = g_filesystem_entry_count;
    entry->type = type;
    entry->size = size;
    entry->storage_offset = storage_offset;

    entry->exists = 1;
    entry->readable = readable;
    entry->writable = writable;

    uint32_t i = 0;

    while(name[i] != '\0' && i < WD_FS_MAX_NAME - 1)
    {
        entry->name[i] = name[i];
        i++;
    }

    entry->name[i] = '\0';

    i = 0;

    while(path[i] != '\0' && i < WD_FS_MAX_PATH - 1)
    {
        entry->path[i] = path[i];
        i++;
    }

    entry->path[i] = '\0';

    g_filesystem_entry_count++;

    return WD_KRNL_SUCCESS;
}

static WD_FS_ENTRY* wdkrnl_filesystem_find(const char* path)
{
    if (!g_filesystem_initialized)
    {
        return 0;
    }

    if (path == 0)
    {
        return 0;
    }

    for (uint32_t i = 0; i < g_filesystem_entry_count; i++)
    {
        WD_FS_ENTRY* entry = &g_filesystem_entries[i];

        if (!entry->exists)
        {
            continue;
        }

        uint32_t j = 0;

        while(path[j] != '\0' && entry->path[j] != '\0' && path[j] == entry->path[j])
        {
            j++;
        }

        if (path[j] == '\0' && entry->path[j] == '\0')
        {
            return entry;
        }
    }

    return 0;
}

static void wdkrnl_hardware_device_initialize(void)
{
    g_hardware_device_count = 0;

    for (uint32_t i = 0; i < WD_HARDWARE_MAX_DEVICES; i++)
    {
        g_hardware_devices[i].id = 0;

        g_hardware_devices[i].type = WD_HARDWARE_TYPE_UNKNOWN;

        g_hardware_devices[i].vendor_id = 0;
        g_hardware_devices[i].device_id = 0;

        g_hardware_devices[i].present = 0;
        g_hardware_devices[i].enabled = 0;

        // j murder drones???1!1!!! so fucking cool

        for (uint32_t j = 0; j < WD_HARDWARE_NAME_LENGTH; j++)
        {
            g_hardware_devices[i].name[j] = '\0';
        }
    }
}

static uint32_t wdkrnl_hardware_register_device(
    WD_HARDWARE_TYPE type,
    uint16_t vendor_id,
    uint16_t device_id,
    const char* name
)
{
    if (g_hardware_device_count >= WD_HARDWARE_MAX_DEVICES)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_HARDWARE_DEVICE* device = &g_hardware_devices[g_hardware_device_count];

    device->id = g_hardware_device_count;

    device->type = type;

    device->vendor_id = vendor_id;
    device->device_id = device_id;

    device->present = 1;
    device->enabled = 1;

    if (name != 0)
    {
        uint32_t i = 0;

        while(name[i] != '\0' && i < WD_HARDWARE_NAME_LENGTH - 1)
        {
            device->name[i] = name[i];
            i++;
        }

        device->name[i] = '\0';
    }

    g_hardware_device_count++;

    return WD_KRNL_SUCCESS;
}

static void wdkrnl_thread_initialize(void)
{
    g_thread_count = 0;
    g_current_thread = 0;

    for (uint32_t i = 0; i < WD_THREAD_MAX_THREADS; i++)
    {
        g_threads[i].id = 0;

        g_threads[i].process_id = 0;

        g_threads[i].state = WD_THREAD_STATE_UNUSED;

        g_threads[i].stack_base = 0;
        g_threads[i].stack_size = 0;

        g_threads[i].initialized = 0;

        g_threads[i].ipc_wait_type = WD_IPC_WAIT_NONE;

        g_threads[i].ipc_wait_id = 0;

        g_threads[i].ipc_waiting = 0;

        g_threads[i].context.rip = 0;
        g_threads[i].context.rsp = 0;
        g_threads[i].context.rbp = 0;

        g_threads[i].context.rax = 0;
        g_threads[i].context.rbx = 0;
        g_threads[i].context.rcx = 0;
        g_threads[i].context.rdx = 0;

        g_threads[i].context.rsi = 0;
        g_threads[i].context.rdi = 0;

        g_threads[i].context.r8 = 0;
        g_threads[i].context.r9 = 0;
        g_threads[i].context.r10 = 0;
        g_threads[i].context.r11 = 0;
        g_threads[i].context.r12 = 0;
        g_threads[i].context.r13 = 0;
        g_threads[i].context.r14 = 0;
        g_threads[i].context.r15 = 0;

        g_threads[i].context.rflags = 0;

        for (uint32_t j = 0; j < WD_THREAD_MAX_NAME; j++)
        {
            // im fucking pissing everywhere
            g_threads[i].name[j] = '\0';
        }
    }
}

static uint32_t wdkrnl_thread_create(
    uint32_t process_id,
    const char* name,
    uint64_t entry_address
)
{
    if (name == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (entry_address == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (process_id >= WD_PROCESS_MAX_PROCESSES)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_thread_count >= WD_THREAD_MAX_THREADS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_PROCESS* process = &g_processes[process_id];

    if (process->state == WD_PROCESS_STATE_UNUSED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_THREAD* thread = 0;

    for (uint32_t i = 0; i < WD_THREAD_MAX_THREADS; i++)
    {
        if (g_threads[i].state == WD_THREAD_STATE_UNUSED)
        {
            thread = &g_threads[i];
            break;
        }
    }

    if (thread == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    thread->id = (uint32_t)(thread - g_threads);

    thread->process_id = process_id;

    thread->state = WD_THREAD_STATE_CREATED;

    thread->context.rip = entry_address;

    thread->context.rax = 0;
    thread->context.rbx = 0;
    thread->context.rcx = 0;
    thread->context.rdx = 0;

    thread->context.rsi = 0;
    thread->context.rdi = 0;

    thread->context.r8 = 0;
    thread->context.r9 = 0;
    thread->context.r10 = 0;
    thread->context.r11 = 0;
    thread->context.r12 = 0;
    thread->context.r13 = 0;
    thread->context.r14 = 0;
    thread->context.r15 = 0;

    thread->context.rflags = 0x202;

    thread->initialized = 1;

    if (wdkrnl_thread_create_stack(thread) != WD_KRNL_SUCCESS)
    {
        thread->state = WD_THREAD_STATE_ERROR;

        thread->initialized = 0;

        return WD_KRNL_INIT_FAILED;
    }

    for (uint32_t i = 0; i < WD_THREAD_MAX_NAME; i++)
    {
        thread->name[i] = '\0';
    }

    uint32_t i = 0;

    while(name[i] != '\0' && i < WD_THREAD_MAX_NAME - 1)
    {
        thread->name[i] = name[i];
        i++;
    }

    thread->name[i] = '\0';

    g_thread_count++;

    thread->state = WD_THREAD_STATE_READY;

    return thread->id;
}

static uint32_t wdkrnl_thread_validate_context(const WD_THREAD* thread)
{
    if (thread == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->context.rip == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->stack_base == 0 || thread->stack_size == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->context.rsp < thread->stack_base)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->context.rsp > thread->stack_base + thread->stack_size)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_thread_save_context(
    WD_THREAD* thread,
    const WD_PROCESS_CONTEXT* context
)
{
    if (thread == 0 || context == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    thread->context = *context;

    return wdkrnl_thread_validate_context(thread);
}

static uint32_t wdkrnl_thread_load_context(
    const WD_THREAD* thread,
    WD_PROCESS_CONTEXT* context
)
{
    if (thread == 0 || context == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_thread_validate_context(thread) != WD_KRNL_SUCCESS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    *context = thread->context;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_thread_set_state(WD_THREAD* thread, WD_THREAD_STATE state)
{
    if (thread == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    switch (state)
    {
        case WD_THREAD_STATE_CREATED:
        case WD_THREAD_STATE_READY:
        case WD_THREAD_STATE_RUNNING:
        case WD_THREAD_STATE_BLOCKED:
        case WD_THREAD_STATE_TERMINATED:
        case WD_THREAD_STATE_ERROR:
            break;

        default:
            return WD_KRNL_INIT_FAILED;

    }

    thread->state = state;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_thread_ready(WD_THREAD* thread)
{
    if (thread == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->state == WD_THREAD_STATE_TERMINATED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->state == WD_THREAD_STATE_ERROR)
    {
        return WD_KRNL_INIT_FAILED;
    }

    thread->state = WD_THREAD_STATE_READY;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_thread_block(WD_THREAD* thread)
{
        if (thread == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->state == WD_THREAD_STATE_TERMINATED)
    {
        return WD_KRNL_INIT_FAILED;
    }

    thread->state = WD_THREAD_STATE_BLOCKED;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_thread_terminate(WD_THREAD* thread)
{
    if (thread == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    thread->state = WD_THREAD_STATE_TERMINATED;

    return WD_KRNL_SUCCESS;
}

static WD_THREAD* wdkrnl_scheduler_find_next(void)
{
    uint32_t start = g_current_thread;

    for (uint32_t offset = 1; offset <= WD_THREAD_MAX_THREADS; offset++)
    {
        uint32_t index = (start + offset) % WD_THREAD_MAX_THREADS;

        WD_THREAD* thread = &g_threads[index];

        if (!thread->initialized)
        {
            continue;
        }

        if (thread->state == WD_THREAD_STATE_READY)
        {
            return thread;
        }
    }

    return 0;
}

static uint32_t wdkrnl_scheduler_select(void)
{
    WD_THREAD* next = wdkrnl_scheduler_find_next();

    if (next == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (wdkrnl_thread_validate_context(next) != WD_KRNL_SUCCESS)
    {
        next->state = WD_THREAD_STATE_ERROR;

        return WD_KRNL_INIT_FAILED;
    }

    if (g_threads[g_current_thread].initialized && g_threads[g_current_thread].state == WD_THREAD_STATE_RUNNING)
    {
        g_threads[g_current_thread].state = WD_THREAD_STATE_READY;
    }

    next->state = WD_THREAD_STATE_RUNNING;

    g_current_thread = next->id;

    return WD_KRNL_SUCCESS;
}

static WD_THREAD* wdkrnl_thread_get_current(void)
{
    if (g_current_thread >= WD_THREAD_MAX_THREADS)
    {
        return 0;
    }

    WD_THREAD* thread = &g_threads[g_current_thread];

    if (!thread->initialized)
    {
        return 0;
    }

    return thread;
}

static void wdkrnl_hardware_identify(void)
{
    if (g_cpu_hardware_info.cpuid_supported)
    {
        wdkrnl_hardware_register_device(WD_HARDWARE_TYPE_CPU, 0, 0, g_cpu_hardware_info.vendor);
    }

    if (g_hardware_info.memory_size != 0)\
    {
        wdkrnl_hardware_register_device(WD_HARDWARE_TYPE_MEMORY, 0, 0, "System Memory");
    }
}

static void wdkrnl_cpuid(
    uint32_t leaf,
    uint32_t subleaf,
    uint32_t* eax,
    uint32_t* ebx,
    uint32_t* ecx,
    uint32_t* edx
)
{
#if defined(__x86_64__) || defined(__i386__)

    __asm__ volatile ("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "a"(leaf), "c"(subleaf));

#else

    *eax = 0;
    *ebx = 0;
    *ecx = 0;
    *edx = 0;

#endif
}

static void wdkrnl_hardware_cpu_discover(void)
{
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;

    g_cpu_hardware_info.cpuid_supported = 0;

    for (uint32_t i = 0; i < WD_CPU_VENDOR_MAX_LENGTH; i++)
    {
        g_cpu_hardware_info.vendor[i] = '\0';
    }

    for (uint32_t i = 0; i < WD_CPU_BRAND_MAX_LENGTH; i++)
    {
        g_cpu_hardware_info.brand[i] = '\0';
    }

#if defined(__x86_64__) || defined(__i386__)

    wdkrnl_cpuid(0, 0, &eax, &ebx, &ecx, &edx);

    g_cpu_hardware_info.maximum_basic_leaf = eax;

    ((uint32_t*)g_cpu_hardware_info.vendor)[0] = ebx;
    ((uint32_t*)g_cpu_hardware_info.vendor)[1] = edx;
    ((uint32_t*)g_cpu_hardware_info.vendor)[2] = ecx;

    g_cpu_hardware_info.vendor[WD_CPU_VENDOR_MAX_LENGTH - 1] = '\0';

    g_cpu_hardware_info.cpuid_supported = 1;

    wdkrnl_cpuid(1, 0, &eax, &ebx, &ecx, &edx);

    g_cpu_hardware_info.stepping = eax & 0xF;

    g_cpu_hardware_info.model = (eax >> 4) & 0xF;

    g_cpu_hardware_info.family = (eax >> 8) & 0xF;

    g_cpu_hardware_info.feature_ecx = ecx;
    g_cpu_hardware_info.feature_edx = edx;

    wdkrnl_cpuid(0x80000000, 0, &eax, &ebx, &ecx, &edx);

    g_cpu_hardware_info.maximum_extended_leaf = eax;

    if (eax >= 0x80000004)
    {
        uint32_t* brand = (uint32_t*)g_cpu_hardware_info.brand;

        wdkrnl_cpuid(
            0x80000002,
            0,
            &brand[0],
            &brand[1],
            &brand[2],
            &brand[3]
        );

        wdkrnl_cpuid(
            0x80000003,
            0,
            &brand[4],
            &brand[5],
            &brand[6],
            &brand[7]
        );

        wdkrnl_cpuid(
            0x80000004,
            0,
            &brand[8],
            &brand[9],
            &brand[10],
            &brand[11]
        );

        g_cpu_hardware_info.brand[WD_CPU_BRAND_MAX_LENGTH - 1] = '\0';
    }

#endif
}

static void wdkrnl_hardware_discovery_initialize(void)
{
    g_cpu_hardware_info.maximum_basic_leaf = 0;
    g_cpu_hardware_info.maximum_extended_leaf = 0;

    g_cpu_hardware_info.family = 0;
    g_cpu_hardware_info.model = 0;
    g_cpu_hardware_info.stepping = 0;

    g_cpu_hardware_info.feature_ecx = 0;
    g_cpu_hardware_info.feature_edx = 0;

    g_cpu_hardware_info.cpuid_supported = 0;

    for (uint32_t i = 0; i < WD_CPU_VENDOR_MAX_LENGTH; i++)
    {
        g_cpu_hardware_info.vendor[i] = '\0';
    }

    for (uint32_t i = 0; i < WD_CPU_BRAND_MAX_LENGTH; i++)
    {
        g_cpu_hardware_info.brand[i] = '\0';
    }
}

static void wdkrnl_idt_set_entry(
    uint8_t vector,
    uint64_t handler,
    uint16_t selector,
    uint8_t type_attributes
)
{
    WD_IDT_ENTRY* entry = &g_idt[vector];

    entry->offset_low = (uint16_t)(handler & 0xFFFF);

    entry->selector = selector;

    entry->list = 0;

    entry->type_attributes = type_attributes;

    entry->offset_middle = (uint16_t)((handler >> 16) & 0xFFFF);

    entry->offset_high = (uint32_t)((handler >> 32) & 0xFFFFFFFF);

    entry->reserved = 0;
}

static void wdkrnl_storage_driver_initialize(void)
{
    g_storage_driver_count = 0;

    for (uint32_t i = 0; i < WD_STORAGE_MAX_DRIVERS; i++)
    {
        g_storage_drivers[i].id = 0;

        g_storage_drivers[i].type = WD_STORAGE_TYPE_UNKNOWN;

        g_storage_drivers[i].initialized = 0;
        g_storage_drivers[i].available = 0;

        g_storage_drivers[i].sector_count = 0;
        g_storage_drivers[i].sector_size = WD_STORAGE_SECTOR_SIZE;

        g_storage_drivers[i].read = 0;
        g_storage_drivers[i].write = 0;

        for (uint32_t j = 0; j < WD_STORAGE_DRIVER_NAME_LENGTH; j++)
        {
            g_storage_drivers[i].name[j] = '\0';
        }
    }
}

static uint32_t wdkrnl_storage_register_driver(
    WD_STORAGE_TYPE type,
    uint64_t sector_count,
    uint32_t sector_size,
    WD_STORAGE_READ read,
    WD_STORAGE_WRITE write,
    const char* name
)
{
    if (g_storage_driver_count >= WD_STORAGE_MAX_DRIVERS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (sector_size == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_STORAGE_DRIVER* driver = &g_storage_drivers[g_storage_driver_count];

    driver->id = g_storage_driver_count;

    driver->type = type;

    driver->sector_count = sector_count;
    driver->sector_size = sector_size;

    driver->read = read;
    driver->write = write;

    driver->initialized = 1;
    driver->available = 1;

    if (name != 0)
    {
        uint32_t i = 0;

        while(name[i] != '\0' && i < WD_STORAGE_DRIVER_NAME_LENGTH - 1)
        {
            driver->name[i] = name[i];
            i++;
        }

        driver->name[i] = '\0';
    }

    g_storage_driver_count++;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_storage_read(
    uint32_t device_id,
    uint64_t lba,
    uint32_t sector_count,
    void* buffer
)
{
    if (buffer == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (sector_count == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device_id >= g_storage_driver_count)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_STORAGE_DRIVER* driver = &g_storage_drivers[device_id];

    if (!driver->initialized || !driver->available)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (driver->read == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (lba >= driver->sector_count)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (sector_count > driver->sector_count - lba)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return driver->read(device_id, lba, sector_count, buffer);
}

static uint32_t wdkrnl_storage_write(
    uint32_t device_id,
    uint64_t lba,
    uint32_t sector_count,
    const void* buffer
)
{
    if (buffer == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (sector_count == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (device_id >= g_storage_driver_count)
    {
        return WD_KRNL_INIT_FAILED;
    }

    WD_STORAGE_DRIVER* driver = &g_storage_drivers[device_id];

    if (!driver->initialized || !driver->available)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (driver->write == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (lba >= driver->sector_count)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (sector_count > driver->sector_count - lba)
    {
        return WD_KRNL_INIT_FAILED;
    }

    return driver->write(device_id, lba, sector_count, buffer);
}

static void wdkrnl_idt_initialize(void)
{
    for (uint32_t i = 0; i < WD_IDT_ENTRY_COUNT; i++)
    {
        g_idt[i].offset_low = 0;
        g_idt[i].selector = 0;
        g_idt[i].list = 0;
        g_idt[i].type_attributes = 0;
        g_idt[i].offset_middle = 0;
        g_idt[i].offset_high = 0;
        g_idt[i].reserved = 0;
    }

    g_idt_pointer.limit = sizeof(g_idt) - 1;

    g_idt_pointer.base = (uint64_t)&g_idt[0];
}

static void wdkrnl_idt_load(void)
{
#if defined(__x86_64__)

    __asm__ volatile ("lidt %0" : : "m"(g_idt_pointer));

#endif
}

static void wdkrnl_interrupt_enable(void)
{
#if defined(__x86_64__)

    __asm__ volatile ("sti");

    g_interrupts_enabled = 1;

#endif
}

static void wdkrnl_interrupt_disable(void)
{
#if defined(__x86_64__)

    __asm__ volatile ("cli");

    g_interrupts_enabled = 0;

#endif
}

static void wdkrnl_timer_initialize(uint32_t frequency)
{
    g_timer_ticks = 0;
    g_timer_frequency = frequency;
}

static void wdkrnl_exception_initialize(void)
{
    g_exception_info.code = WD_EXCEPTION_RESERVED;
    g_exception_info.instruction_pointer = 0;
    g_exception_info.stack_pointer = 0;
    g_exception_info.error_code = 0;
    g_exception_info.occurred = 0;
}

static void wdkrnl_halt(void)
{
    for (;;)
    {
#if defined(__x86_64__) || defined(__i386__)
        __asm__ volatile ("hlt");
#else
        // temporary fallback for unsupporated architectures
        for (volatile uint32_t i = 0; i < 1000000; ++i)
        {
        }
#endif
    }
}

static void wdkrnl_error(WD_KRNL_ERROR_CODE error)
{
    g_kernel_error = error;
    g_kernel_status = WD_KRNL_FATAL_ERROR;
    g_kernel_state = WD_KRNL_STATE_ERROR;

    wdkrnl_halt();
}

static void wd_krnl_exception_handler(
    WD_EXCEPTION_CODE code,
    uint64_t instruction_pointer,
    uint64_t stack_pointer,
    uint64_t error_code
)
{
    g_exception_info.code = code;
    g_exception_info.instruction_pointer = instruction_pointer;
    g_exception_info.stack_pointer = stack_pointer;
    g_exception_info.error_code = error_code;
    g_exception_info.occurred = 1;

    wdkrnl_error(WD_KRNL_ERROR_EXCEPTION);
}

static void wdkrnl_timer_tick(void)
{
    g_system_ticks++;
}

static void wdkrnl_timer_interrupt(void)
{
    g_timer_ticks++;
    g_interrupt_count++;

    wdkrnl_timer_tick();
}


static void wdkrnl_interrupt_initialize(void)
{
    for (uint32_t i = 0; i < WD_KRNL_MAX_INTERRUPTS; i++)
    {
        g_interrupt_handlers[i] = 0;
    }

    g_system_ticks = 0;
    g_timer_frequency = 0;
}

static void wdkrnl_memory_initialize(void)
{
    g_memory_region_count = 0;
    g_memory_total = 0;
    g_memory_available = 0;
    g_memory_allocation_count = 0;

    for (uint32_t i = 0; i < WD_MEMORY_MAX_REGIONS; i++)
    {
        g_memory_regions[i].base = 0;
        g_memory_regions[i].size = 0;
        g_memory_regions[i].available = 0;
    }

    for (uint32_t i = 0; i < WD_MEMORY_MAX_ALLOCATIONS; i++)
    {
        g_memory_allocations[i].base = 0;
        g_memory_allocations[i].size = 0;
        g_memory_allocations[i].active = 0;
    }
}

static uint32_t wdkrnl_memory_register_region(
    uint64_t base,
    uint64_t size,
    uint8_t available
)
{
    if (size == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (g_memory_region_count >= WD_MEMORY_MAX_REGIONS)
    {
        return WD_KRNL_INIT_FAILED;
    }

    g_memory_regions[g_memory_region_count].base = base;
    g_memory_regions[g_memory_region_count].size = size;
    g_memory_regions[g_memory_region_count].available = available;

    g_memory_total += size;

    if (available)
    {
        g_memory_available += size;
    }

    g_memory_region_count++;

    return WD_KRNL_SUCCESS;
}

static uint64_t wdkrnl_memory_allocate_pages(uint64_t page_count)
{
    if (page_count == 0)
    {
        return 0;
    }

    uint64_t allocation_size = page_count * WD_MEMORY_PAGE_SIZE;

    for (uint32_t i = 0; i < g_memory_region_count; i++)
    {
        WD_MEMORY_REGION* region = &g_memory_regions[i];

        if (!region->available)
        {
            continue;
        }

        if (region->size < allocation_size)
        {
            continue;
        }

        if (g_memory_allocation_count >= WD_MEMORY_MAX_ALLOCATIONS)
        {
            return 0;
        }

        uint64_t allocation_base = region->base;

        region->base += allocation_size;
        region->size -= allocation_size;

        g_memory_available -= allocation_size;

        g_memory_allocations[g_memory_allocation_count].base = allocation_base;

        g_memory_allocations[g_memory_allocation_count].size = allocation_size;

        g_memory_allocations[g_memory_allocation_count].active = 1;

        g_memory_allocation_count++;

        return allocation_base;
    }

    return 0;
}

static uint32_t wdkrnl_thread_create_stack(
    WD_THREAD* thread
)
{
    if (thread == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (!thread->initialized)
    {
        return WD_KRNL_INIT_FAILED;
    }

    if (thread->stack_base != 0 || thread->stack_size != 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    uint64_t stack_base = wdkrnl_memory_allocate_pages(16);

    if (stack_base == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    thread->stack_base = stack_base;

    thread->stack_size = 16 * WD_MEMORY_PAGE_SIZE;

    thread->context.rsp = thread->stack_base + thread->stack_size;

    thread->context.rbp = thread->context.rsp;

    return WD_KRNL_SUCCESS;
}

static uint32_t wdkrnl_process_create_stack(WD_PROCESS* process)
{
    if (process == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    uint64_t stack_base = wdkrnl_memory_allocate_pages(16);

    if (stack_base == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    process->stack_base = stack_base;
    process->stack_size = WD_PROCESS_STACK_SIZE;

    return WD_KRNL_SUCCESS;
}

// compiler please shut the fuck up

static uint32_t wdkrnl_memory_free_pages(uint64_t base, uint64_t page_count)
{
    if (page_count == 0)
    {
        return WD_KRNL_INIT_FAILED;
    }

    uint64_t allocation_size = page_count * WD_MEMORY_PAGE_SIZE;

    for (uint32_t i = 0; i < WD_MEMORY_MAX_ALLOCATIONS; i++)
    {
        WD_MEMORY_ALLOCATION* allocation = &g_memory_allocations[i];

        if (!allocation->active)
        {
            continue;
        }

        if (allocation->base != base || allocation->size != allocation_size)
        {
            continue;
        }

        allocation->active = 0;

        g_memory_available += allocation_size;

        if (g_memory_region_count >= WD_MEMORY_MAX_REGIONS)
        {
            return WD_KRNL_INIT_FAILED;
        }

        g_memory_regions[g_memory_region_count].base = allocation->base;

        g_memory_regions[g_memory_region_count].size = allocation->size;

        g_memory_regions[g_memory_region_count].available = 1;

        g_memory_region_count++;

        return WD_KRNL_SUCCESS;
    }

    return WD_KRNL_INIT_FAILED;
}

static void wdkrnl_hardware_initialize(void)
{
    g_hardware_info.cpu_id = 0;
    g_hardware_info.cpu_features = 0;
    g_hardware_info.memory_size = 0;
    g_hardware_info.hardware_detected = 0;
}

static void wdkrnl_storage_initialize(void)
{
    g_storage_device_count = 0;

    for (uint32_t i = 0; i < WD_STORAGE_MAX_DEVICES; i++)
    {
        g_storage_devices[i].id = 0;
        g_storage_devices[i].size = 0;
        g_storage_devices[i].available = 0;
    }
}

static void wdkrnl_executable_initialize(void)
{
    for (uint32_t i = 0; i < WD_EXEC_MAX_PATH; i++)
    {
        g_current_executable.path[i] = '\0';
    }

    g_current_executable.load_address = 0;
    g_current_executable.entry_address = 0;
    g_current_executable.image_size = 0;
    g_current_executable.loaded = 0;
}

static void wdkrnl_cpu_initialize(void)
{
#if defined(__x86_64__)

    g_cpu_info.architecture = WD_CPU_ARCH_X86_64;
    g_cpu_info.long_mode = 1;
    g_cpu_info.initialized = 1;

#else

    g_cpu_info.architecture = WD_CPU_ARCH_UNKNOWN;
    g_cpu_info.long_mode = 0;
    g_cpu_info.initialized = 0;

#endif
}

static uint32_t wdkrnl_initialize(WD_BOOT_INFO* boot_info)
{
    // future init will happen here
    wd_console_initialize(boot_info);

    g_kernel_state = WD_KRNL_STATE_INITIALIZING;
    wd_console_write("[WDKRNL] Starting initialzation.\r\n");

    wdkrnl_cpu_initialize();
    wd_console_write("[WDKRNL] Initializing CPU.\r\n");

    wdkrnl_hardware_discovery_initialize();
    wd_console_write("[WDKRNL] Discovering hardware.\r\n");

    wdkrnl_hardware_cpu_discover();
    wd_console_write("[WDKRNL] CPU hardwary discovery in progress.\r\n");

    wdkrnl_hardware_device_initialize();
    wd_console_write("[WDKRNL] Initializing devices.\r\n");

    wdkrnl_hardware_identify();
    wd_console_write("[WDKRNL] Identifying hardware.\r\n");

    wdkrnl_memory_initialize();
    wd_console_write("[WDKRNL] Initializing memory.\r\n");

    wdkrnl_exception_initialize();
    wd_console_write("[WDKRNL] Initializing bugcheckhandler.\r\n");

    wdkrnl_device_initialize();
    wd_console_write("[WDKRNL] Initializing expanded devices.\r\n");

    wdkrnl_device_driver_initialize();
    wd_console_write("[WDKRNL] Initializing drivers.\r\n");

    wdkrnl_idt_initialize();
    wd_console_write("[WDKRNL] Initializing IDT.\r\n");

    wdkrnl_timer_initialize(100);
    wd_console_write("[WDKRNL] Initializing timer.\r\n");

    wdkrnl_idt_load();
    wdkrnl_interrupt_initialize();

    wdkrnl_hardware_initialize();
    wd_console_write("[WDKRNL] Initializing hardware.\r\n");

    wdkrnl_storage_initialize();
    wd_console_write("[WDKRNL] Initializing storage.\r\n");

    wdkrnl_storage_driver_initialize();

    wdkrnl_filesystem_initialize();
    wd_console_write("[WDKRNL] Initializing filesystem.\r\n");

    wdkrnl_executable_initialize();
    wd_console_write("[WDKRNL] Initializing .exes.\r\n");

    wdkrnl_process_initialize();
    wd_console_write("[WDKRNL] Initializing processes.\r\n");

    wdkrnl_thread_initialize();
    wd_console_write("[WDKRNL] Initializing threads.\r\n");

    wdkrnl_ipc_initialize();
    wd_console_write("[WDKRNL] Initializing IPCs.\r\n");

    wdkrnl_power_initialize();
    wd_console_write("[WDKRNL] Initializing power.\r\n");

    wdkrnl_recovery_initialize();
    wd_console_write("[WDKRNL] Initializing recovery handler.\r\n");

    wdkrnl_health_initialize();
    wd_console_write("[WDKRNL] Initializing health checkers.\r\n");

    wdkrnl_watchdog_initialize();
    wd_console_write("[WDKRNL] Initializing watchdog.\r\n");

    g_kernel_status = WD_KRNL_SUCCESS;
    wd_console_write("[WDKRNL] KRNL boot success.\r\n");

    wdkrnl_health_check();

    return WD_KRNL_SUCCESS;
}

static volatile uint64_t g_kernel_ticks = 0;

static void wdkrnl_runtime_tick(void)
{
    g_kernel_ticks++;
}

static void wdkrnl_runtime(void)
{

    // YOU SHALL NOT RETURN MOTHERFUCKER
    g_kernel_state = WD_KRNL_STATE_RUNNING;

    wd_console_write("[WDKRNL] Entered runtime\r\n");

    for (;;)
    {
        wdkrnl_runtime_tick();

#if defined(WD_BARE_METAL)
#if defined(__x86_64__) || defined(__i386__)
        __asm__ volatile ("hlt");
#endif
#else
        /* Host-side kernel test loop. */
        for (volatile uint32_t i = 0; i < 1000000; i++)
        {
        }
#endif

#if defined(__x86_64__) || defined(__i386__)
        __asm__ volatile ("hlt");
#endif

    }
}

void wdkrnl_entry(WD_BOOT_INFO* boot_info)
{
    uint32_t result;

    wd_console_write("[WDKRNL] Entry point start\r\n");

    // krnl staats hea dumbass petah

    g_kernel_state = WD_KRNL_STATE_INITIALIZING;

    if (boot_info == 0)
    {
        g_kernel_status = WD_KRNL_INIT_FAILED;
        g_kernel_state = WD_KRNL_STATE_ERROR;

        wdkrnl_halt();
    }

    result = wdkrnl_initialize(boot_info);

    if (result != WD_KRNL_SUCCESS)
    {
        g_kernel_status = WD_KRNL_INIT_FAILED;
        g_kernel_state = WD_KRNL_STATE_ERROR;
        wdkrnl_halt();
    }

    // init succeed enter runtime

    wdkrnl_runtime();
} // September 11th, 2026. This currently is at 2001 lines. 43 kb of fucking source. coincidence? no.

int main(void)
{
    WD_BOOT_INFO boot_info;

    boot_info = (WD_BOOT_INFO){0};

    wdkrnl_entry(&boot_info);

    return 0;
}