; WDSYS UEFI x86-64 boot entry
; NASM syntax

BITS 64

default rel

section .bss

align 8
wd_boot_info:
    resq 7


section .text

global efi_main
extern wdkrnl_entry


efi_main:

    ; UEFI x64 entry:
    ; RCX = EFI_HANDLE ImageHandle
    ; RDX = EFI_SYSTEM_TABLE *SystemTable

    ; Reserve Microsoft x64 shadow space
    ; and maintain 16-byte stack alignment.
    sub rsp, 40

    ; ------------------------------------------------
    ; Build WD_BOOT_INFO
    ; ------------------------------------------------

    ; system_table
    mov [wd_boot_info + 0x00], rdx

    ; memory_map
    mov qword [wd_boot_info + 0x08], 0

    ; memory_map_size
    mov qword [wd_boot_info + 0x10], 0

    ; memory_descriptor_size
    mov qword [wd_boot_info + 0x18], 0

    ; kernel_base
    mov qword [wd_boot_info + 0x20], 0

    ; kernel_size
    mov qword [wd_boot_info + 0x28], 0

    ; uefi_boot = 1
    mov byte [wd_boot_info + 0x30], 1

    ; ------------------------------------------------
    ; Kernel handoff
    ; ------------------------------------------------

    ; wdkrnl_entry(WD_BOOT_INFO*)
    lea rcx, [wd_boot_info]

    call wdkrnl_entry

    ; ------------------------------------------------
    ; The kernel should NEVER return.
    ; ------------------------------------------------

    add rsp, 40

.halt:
    cli
    hlt
    jmp .halt