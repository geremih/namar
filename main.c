#include"lisp.h"
#include"emit.h"
#include<stdio.h>

extern FILE *yyin;
int yyparse(struct node**);

int main(){
        do{
                struct node* root = NULL;
                yyparse(&root);

        
                while(root!=NULL)
                        {
                                emit(root->pair->car);
                                //print_ast(root->pair->car, 0);
                                root = root->pair->cdr;
                        }

        } while(!feof(yyin));
}

