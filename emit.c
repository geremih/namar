#include "includes.h"

void emit_expr(struct node *nd){

        if(IS_NUM((nd)))
                fprintf(stdout, "movl $%d, %%eax\n", nd->integer);
        else if(IS_PAIR(nd)){
                //TODO: eval first arg and then call it
                //How are we planning to implement higher order functions
                if(!IS_ID(nth(nd,0))){
                        die("Calling a non-function");
                }
                if(strcmp(nth(nd, 0)->id, "inc") == 0){
                        emit_expr(nth(nd, 1))  ;
                        fprintf(stdout, "addl $1, %%eax\n");
                }
        }

}

void emit(struct node* nd){

        fprintf(stdout, ".globl entry\n");
        fprintf(stdout, ".type entry, @function\n");
        fprintf(stdout, "entry:\n");
        emit_expr(nd);
        fprintf(stdout, "ret\n");
        
}
