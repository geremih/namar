#include "emit.h"

void emit(struct node* nd){
        printf(".globl entry\n");
        printf(".type entry, @function\n");
        printf("entry:\n");
        printf("movl $%d, %%eax\n", nd->integer);
        printf("ret\n");
        
}
