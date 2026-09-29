    .text
    .globl sum_array
    .type sum_array, @function
sum_array:
    xorl %eax, %eax
    xorl %ecx, %ecx
.Lsum_loop:
    cmpl %esi, %ecx
    jge .Lsum_done
    addl (%rdi,%rcx,4), %eax
    incl %ecx
    jmp .Lsum_loop
.Lsum_done:
    ret
    .size sum_array, .-sum_array

    .section .note.GNU-stack,"",@progbits