section	.data
    words dw -1, 2, 3, 4, 5, 6, 7, 8, 9, -10
    temp dd 0
    sum dw 0
    index db 10
    s dw 0
section .text
    global _start
_start:
main:
mov ecx, [index]    ; Помещаем в счетчик 
lea esi, [words]    ; Загрузка эффективного адреса данных, esi cодержит указатель на текущий элемент-источник
mov bx, [esi]       ; Помещаем указатель для обращения к памяти по адресу, хранящемуся в регистре
for:
    test bx, bx     ; Проверяем значение в регистре bx
    jns cont        ; Переход на count, если SF = 0 (sign flag)
        not bx      ; Меняет значение всех битов переменной на противоположное
        add bx, 1       
    cont:
    add ax, bx          
    add esi, 2
    mov bx, [esi]
    dec ecx
    jnz for
    mov ecx, 0
    mov [temp], ax
fin:
cmp ax, 10
jb small            ; Пока ax < 10 – выполнять
big:
    xor edx, edx    ; Обнуляем регистр EDX
    mov ebx, 10     ; Заносим в регистр EBX 10
    mov eax, [temp] ; Заносим в регистр EAX текущий символ
    div ebx         ; Беззнаковое деление EDX:EAX, частное помещается в регистр EAX, а остаток – в регистр EDX.
    mov [temp], ax  ; Заносим в текущий символ
    push dx
    mov bx, 10
    inc ecx
    cmp eax, 10
    jg big          ; Eсли EAX > 10, то переход
    add ax, '0'
    mov [sum], ax
    mov [index], cx
    mov edx, 1
    mov ecx, sum
    mov eax, 4      ; номер системного вызова sys_write
    mov ebx, 1      ; файловый декскриптоп stdout
    int 0x80
    mov cx, [index]
    output:
        pop ax
        add ax, '0'
        mov [sum], ax 
        mov [index], cx
        mov edx, 1
        mov ecx, sum 
        mov eax, 4     ; номер системного вызова sys_write
        int 0x80
        mov cx, [index]
        dec cx         ; Уменьшаем CX на 1
        jnz output     ; Если CX не равно 0, продолжаем цикл
        mov eax, 1     ; номер системного вызова sys_exit
        mov ebx, 0     ; код ошибки
        int 0x80
small:
    add ax, '0'
    mov [sum], ax
    mov edx, 1
    mov ecx, sum
    mov eax, 4      ; номер системного вызова sys_write
    mov ebx, 0      ; код ошибки
    mov eax, 1      ; номер системного вызова sys_exit
    int 0x80
