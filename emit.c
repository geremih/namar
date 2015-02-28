#include "includes.h"

FILE * out;
void emit_expr(struct node *nd){

        if(is_integer((nd)))
                fprintf(out, "movl $%d, %%eax\n", h_l_integer(nd->integer));
        else if(is_boolean(nd)){
                fprintf(out, "movl $%d, %%eax\n", h_l_boolean(nd->integer));
        }
        else if(is_nil(nd)){
                fprintf(out, "movl $%d, %%eax\n", h_l_nil());
        }
        else if(is_pair(nd)){
                //TODO: eval first arg and then call it
                //How are we planning to implement higher order functions
                int stack_index = -4;
                if(!is_id(nth(nd,0))){
                        die("Calling a non-function");
                }
                if(strcmp(nth(nd, 0)->id, "inc") == 0){
                        emit_expr(nth(nd, 1))  ;
                        fprintf(out, "addl $%d, %%eax\n", h_l_integer(1));
                }
                if(strcmp(nth(nd, 0)->id, "add") == 0){

                        emit_expr(nth(nd, 1));
                        fprintf(out, "movl %%eax, %d(%%rbp)\n", stack_index);
                        emit_expr(nth(nd, 2));
                        fprintf(out, "movl %d(%%rbp), %%edx\n", stack_index);
                        fprintf(out, "addl %%edx, %%eax\n");
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
        fclose(out);
        
}
