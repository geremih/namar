#include "includes.h"

struct node* node_int(int value){
        struct node* nd = malloc(sizeof(struct node));
        nd->type = INTEGER;
        nd->integer = value;
        return nd;
}

struct node *node_symbol(char* str){
        struct node* nd = malloc(sizeof(struct node));
        nd->type = SYMBOL;
        nd->symbol = str;
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

struct node* node_nil(){
        struct node* nd = malloc(sizeof(struct node));
        nd->type = NIL;
        return nd;
}

struct node* node_true(){
        struct node* nd = malloc(sizeof(struct node));
        nd->type = BOOLEAN;
        nd->integer = 1;
        return nd;
}

struct node* node_false(){
        struct node* nd = malloc(sizeof(struct node));
        nd->type = BOOLEAN;
        nd->integer = 0;
        return nd;
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
        else if(node->type == SYMBOL){
                printf("%s", node->symbol);
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

        
struct node* nth(struct node* nd, int n){
        if(!is_pair(nd)){
                die("Given node is not a pair");
        }
        while(n--){
                nd = nd->pair->cdr;
                if(!is_pair(nd)){
                        die("Given node is not a pair");
                }
        }

        return nd->pair->car;
}

int len(struct node* nd){

        /* if(!is_pair(nd)){ */
        /*         die("Given node is not a pair"); */
        /* }                  */
        int length = 0;
        while(!is_nil(nd)){
                if(!is_pair(nd)){
                        die("Given node is not a pair");
                }
                nd = nd->pair->cdr;
                length++;
        }

        return length;
        
}

int is_integer(struct node* nd){
        return nd->type == INTEGER;
} 
int is_pair(struct node* nd){
        return nd->type == PAIR;
}
int  is_symbol(struct node* nd){
        return nd->type == SYMBOL;
}

int is_nil(struct node* nd){
        return nd->type == NIL;
}

int is_boolean(struct node* nd){
        return nd->type == BOOLEAN;
}

void pprint(struct node* nd){
        fflush(stdout);
        if(is_integer(nd)){
                fprintf(stdout, "%d", nd->integer);
        }
        else if(is_symbol(nd)){
                fprintf(stdout, "%s", nd->symbol);
        }
        else if(is_nil(nd)){
                fprintf(stdout, "nil");
        }
        else if(is_boolean(nd)){
                if(nd->integer)
                        fprintf(stdout, "true ");
                else{
                        fprintf(stdout, "false ");
                }
        }
        else if(is_pair(nd)){
                fprintf(stdout, "(");
                while(!is_nil(nd)){
                        pprint(nd->pair->car);
                        nd = nd->pair->cdr;
                        if(!is_nil(nd))
                                fprintf(stdout, " ");
                }
                fprintf(stdout, ")");

        }
        
}



