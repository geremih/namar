#include"lisp.h"
#include<stdio.h>

extern FILE *yyin;
int yyparse(struct node**);

int main(){
        do{
                struct node* root = NULL;
                yyparse(&root);
                print_ast(root, 0);
        } while(!feof(yyin));
}
