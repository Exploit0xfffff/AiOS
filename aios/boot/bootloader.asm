; bootloader.asm - Example bootloader code for x86 architecture

org 0x7c00  ; Set the origin to the default boot sector location

start:
    ; Set up segment registers
    xor ax, ax  ; Clear AX register
    mov ds, ax  ; Set DS segment register to 0
    mov es, ax  ; Set ES segment register to 0
    mov ss, ax  ; Set SS segment register to 0
    mov sp, 0x7c00  ; Set stack pointer

    ; Load kernel from disk
    mov ah, 0x02    ; BIOS read sector function
    mov al, 0x01    ; Number of sectors to read
    mov ch, 0x00    ; Cylinder number
    mov dh, 0x00    ; Head number
    mov dl, 0x80    ; Drive number (adjust as per your system)
    mov bx, 0x8000  ; Destination address in memory (where the kernel will be loaded)
    int 0x13        ; BIOS interrupt for disk I/O

    ; Jump to the loaded kernel
    jmp 0x8000      ; Jump to the memory location where the kernel is loaded

times 510-($-$$) db 0  ; Pad the bootloader to occupy 510 bytes
dw 0xAA55              ; Boot signature
