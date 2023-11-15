; global print, print_nl
; Taken from https://github.com/cfenollosa/os-tutorial/tree/master/05-bootsector-functions-strings

; real mode print using BIOS interrupt
; print at current cursor location
; start address of null terminated string stored in bx before call
print:
    pusha

; keep this in mind:
; while (string[i] != 0) { print string[i]; i++ }

; the comparison for string end (null byte)
start:
    mov al, [bx] ; 'bx' is the base address for the string
    cmp al, 0 
    je done

    ; the part where we print with the BIOS help
    mov ah, 0x0e
    int 0x10 ; 'al' already contains the char

    ; increment pointer and do next loop
    add bx, 1
    jmp start

done:
    popa
    ret

; print cx characters from bx
print_cx:
    pusha
    
.print_cx_start:
    mov ah, 0x0e
    mov al, [bx] ; newline char
    int 0x10
    add bx, 1
    loop .print_cx_start

    popa
    ret

; real mode print newline using BIOS interrupt
; print at current cursor location
print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret