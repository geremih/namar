#ifndef _LISP_H
#define _LISP_H

#define IS_NUM(node) ((node)->type == INTEGER)
#define IS_PAIR(node) ((node)->type == PAIR)
#define IS_ID(node) ((node)->type == ID)

enum node_type {
        INTEGER, ID, PAIR
};

struct node;
struct pair{
        struct node *cdr;
        struct node *car;
};

struct node{
        enum node_type type;
        union {
                struct pair *pair;
                int integer;
                char * id;
        };
};


struct node* node_id(char *);
struct node* node_int(int);
void print_ast(struct node*, int);
struct node * node_pair(struct node* car, struct node* cdr);
#endif
