#include "includes.h"

FILE * out;
void emit_expr(struct node *nd){

        if(is_integer((nd)))
                fprintf(out, "movl $%d, %%eax\n", h_l_integer(nd->integer));
        else if(is_pair(nd)){
                //TODO: eval first arg and then call it
                //How are we planning to implement higher order functions
                if(!is_id(nth(nd,0))){
                        die("Calling a non-function");
                }
                if(strcmp(nth(nd, 0)->id, "inc") == 0){
                        emit_expr(nth(nd, 1))  ;
                        fprintf(out, "addl $1, %%eax\n");
                }
        }

}


void emit(struct node* nd){
        if(!out){
                out = fopen("out.s", "w");
        }
        fprintf(out, ".globl entry\n");
        fprintf(out, ".type entry, @function\n");
        fprintf(out, "entry:\n");
        emit_expr(nd);
        fprintf(out, "ret\n");
        
}
