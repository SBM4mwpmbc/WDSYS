; WDSYS UEFI x86-64 boot entry
;
; MASM / ml64 syntax

PUBLIC efi_main
EXTERN wdkrnl_entry:PROC

.data

ALIGN 8

wd_boot_info QWORD 7 DUP(0)

.code

efi_main PROC

; UEFI x64 entry:
; RCX = EFI_HANDLE ImageHandle
; RDX = EFI_SYSTEM_TABLE *SystemTable
;
; Reserve Microsoft x64 shadow space
; and maintain 16-byte stack alignment.

sub rsp, 40

; ------------------------------------------------
; Build WD_BOOT_INFO
; ------------------------------------------------

; system_table
mov QWORD PTR [wd_boot_info + 00h], rdx

; memory_map
mov QWORD PTR [wd_boot_info + 08h], 0

; memory_map_size
mov QWORD PTR [wd_boot_info + 10h], 0

; memory_descriptor_size
mov QWORD PTR [wd_boot_info + 18h], 0

; kernel_base
mov QWORD PTR [wd_boot_info + 20h], 0

; kernel_size
mov QWORD PTR [wd_boot_info + 28h], 0

; uefi_boot = 1
mov BYTE PTR [wd_boot_info + 30h], 1

; ------------------------------------------------
; Kernel handoff
; ------------------------------------------------

; wdkrnl_entry(WD_BOOT_INFO*)
lea rcx, wd_boot_info
call wdkrnl_entry

; ------------------------------------------------
; The kernel should NEVER return.
; ------------------------------------------------

add rsp, 40

halt_loop:
cli
hlt
jmp halt_loop

efi_main ENDP

END
