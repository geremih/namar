#include<stdlib.h>
#include<stdio.h>
#include "lisp.h"

struct node* node_int(int value){
        struct node* nd = malloc(sizeof(struct node));
        nd->type = INTEGER;
        nd->integer = value;
        return nd;
}

struct node *node_id(char* str){
        struct node* nd = malloc(sizeof(struct node));
        nd->type = ID;
        nd->id = str;
        return nd;
}
struct node *node_pair(struct node* car, struct node* cdr){
        struct pair *pair = malloc(sizeof(struct pair));
        struct node *node = malloc(sizeof(struct node));
        node->type = PAIR;
        node->pair = pair;
        pair->car = car;
        pair->cdr = cdr;
        return node;
}

void print_ast(struct node* node, int depth){
        int i;
        for(i=0;i<depth;i++){
                printf("\t");
        }
        if(!node){
                printf("NULL");
        }
        else if(node->type == INTEGER){
                printf("%d", node->integer);
        }
        else if(node->type == ID){
                printf("%s", node->id);
        }
        else{
                printf("(");
                printf("\n");
                print_ast(node->pair->car, depth+1);
                print_ast(node->pair->cdr, depth+1);
                for(i=0;i<depth;i++){
                        printf("\t");
                }
                printf(")");
        }
        printf("\n");

               
}

        
