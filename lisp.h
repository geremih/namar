#ifndef _LISP_H
#define _LISP_H

enum node_type {
        INTEGER, ID, PAIR, BOOLEAN, NIL
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


int is_integer(struct node *);
int is_pair(struct node *); 
int is_id(struct node *);
int is_nil(struct node *);
int is_boolean(struct node *);

struct node* node_id(char *);
struct node* node_int(int);
void print_ast(struct node*, int);
void pprint(struct node*);
struct node * node_pair(struct node* car, struct node* cdr);
struct node* nth(struct node*, int);
#endif
