#include "includes.h"


int word_size = 4;
FILE * out;

char *unique_label(){
        static int count = 0;
        count++;
        char *s = NULL;
        asprintf(&s,"l%d", count);
        return s;
}

void emit_expr(struct node *nd, struct env* env, int stack_index){
        if(is_integer((nd)))
                fprintf(out, "movl $%d, %%eax\n", h_l_integer(nd->integer));
        else if(is_boolean(nd)){
                fprintf(out, "movl $%d, %%eax\n", h_l_boolean(nd->integer));
        }
        else if(is_nil(nd)){
                fprintf(out, "movl $%d, %%eax\n", h_l_nil());
        }
        else if(is_symbol(nd)){
                int id = find_env_stack_index(env, nd->symbol);
                fprintf(out, "movl %d(%%rbp), %%eax\n", id);
        }
        else if(is_pair(nd)){
                //TODO: eval first arg and then call it
                //How are we planning to implement higher order functions
                if(!is_symbol(nth(nd,0))){
                        die("Calling a non-function");
                }
                if(strcmp(nth(nd, 0)->symbol, "inc") == 0){
                        emit_expr(nth(nd, 1), env, stack_index)  ;
                        fprintf(out, "addl $%d, %%eax\n", h_l_integer(1));
                }
                if(strcmp(nth(nd, 0)->symbol, "add") == 0){

                        emit_expr(nth(nd, 1), env, stack_index);
                        fprintf(out, "movl %%eax, %d(%%rbp)\n", stack_index);
                        emit_expr(nth(nd, 2), env, stack_index);
                        fprintf(out, "movl %d(%%rbp), %%edx\n", stack_index);
                        fprintf(out, "addl %%edx, %%eax\n");
                }
                if(strcmp(nth(nd, 0)->symbol, "grt") == 0){
                        char *label1, *label2;
                        label1 = unique_label();
                        label2 = unique_label();
                        emit_expr(nth(nd, 1), env, stack_index);
                        fprintf(out, "movl %%eax, %d(%%rbp)\n", stack_index);
                        emit_expr(nth(nd, 2), env, stack_index);
                        fprintf(out, "movl %d(%%rbp), %%edx\n", stack_index);
                        fprintf(out, "cmpl %%eax, %%edx\n");
                        fprintf(out, "jg %s\n", label1);
                        fprintf(out, "movl $%d, %%eax\n", h_l_boolean(0));
                        fprintf(out, "jmp %s\n", label2);
                        fprintf(out, "%s:\n", label1);
                        fprintf(out, "movl $%d, %%eax\n", h_l_boolean(1));
                        fprintf(out, "%s:\n", label2);
                        free(label1);
                        free(label2);
                }

                if(strcmp(nth(nd, 0)->symbol, "if") == 0){
                        char *label1, *label2;
                        label1 = unique_label();
                        label2 = unique_label();
                        struct node *test = nth(nd, 1);
                        struct node *conseq = nth(nd, 2);
                        struct node *altern = nth(nd, 3);
                        
                        emit_expr(test, env, stack_index);
                        emit_expr(altern, env, stack_index);


                        free(label1);
                        free(label2);
                }

                if(strcmp(nth(nd, 0)->symbol, "let") == 0){
                        //(let ((a 1) (b 2)))
                        env = add_env(env);
                        struct node * bindings = nth(nd, 1);
                        
                        int length = len(bindings);
                        int i;
                        for(i = 0; i < length; i++){
                                struct node *binding, *lhs, *rhs;
                                binding = nth(bindings, i);
                                if(len(binding)!= 2){
                                        die("Let binding doesn't have two elements");
                                }
                                lhs = nth(binding,0);
                                rhs = nth(binding, 1);
                                if(!is_symbol(lhs)){
                                        die("let: lhs is not symbol");
                                }
                                emit_expr(rhs, env, stack_index);
                                fprintf(out,"movl %%eax, %d(%%rbp)\n",stack_index);
                                add_env_symbol(env, lhs->symbol, stack_index);
                                stack_index -= word_size;
                        }
                        emit_expr(nth(nd, 2), env, stack_index);
                        env = remove_env(env);
                }

        }


}


void emit(struct node* nd){
        if(!out){
                out = fopen("out.s", "w");
        }
        struct env* env  = add_env(NULL);
        fprintf(out, ".globl entry\n");
        fprintf(out, ".type entry, @function\n");
        fprintf(out, "entry:\n");
        emit_expr(nd, env, -4);
        fprintf(out, "ret\n");
        fclose(out);
        remove_env(env);
}

