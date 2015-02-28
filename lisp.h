#ifndef _LISP_H
#define _LISP_H

enum node_type {
        INTEGER, SYMBOL, PAIR, BOOLEAN, NIL
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
                char * symbol;
        };
};


int is_integer(struct node *);
int is_pair(struct node *); 
int is_symbol(struct node *);
int is_nil(struct node *);
int is_boolean(struct node *);

struct node* node_symbol(char *);
struct node* node_int(int);
struct node* node_false();
struct node* node_true();
struct node* node_nil();



void print_ast(struct node*, int);
void pprint(struct node*);
struct node * node_pair(struct node* car, struct node* cdr);


struct node* nth(struct node*, int);
int len(struct node*);
#endif
