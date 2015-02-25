%{
#include "lisp.h"
#include<stdlib.h>
#include<stdio.h>
%}

%union{
 char *sval;
 struct node* nval;
}

%token <sval> YID
%token <sval> YINTEGER
%token YOPEN_PAREN
%token YCLOSE_PAREN
%type <nval> list expr_list  expr
%parse-param {struct node **root}

%%

toplev: expr_list { *root = $1; YYACCEPT;}
        ;
expr: YINTEGER { $$ = node_int(atoi($1));}
      | YID {$$ = node_id($1);}
      | list  {$$ = $1;}
      ;
list: YOPEN_PAREN expr_list YCLOSE_PAREN  { $$ = $2;}
      ;
expr_list: expr expr_list { $$ = node_pair($1, $2);}
           | expr         { $$ = node_pair($1, NULL); }
           ;
%%
