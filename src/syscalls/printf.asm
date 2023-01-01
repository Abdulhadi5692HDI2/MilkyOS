

SECTION .text
    extern scrprint
    global printf

    printf:
        push rbp
        mov rbp, rsp

        push qword [rbp+8]
        call scrprint

        mov rsp, rbp
        pop rbp
        retq