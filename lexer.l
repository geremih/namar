%{
#include "grammar.tab.h"
%}

DIGIT [0-9]
INTEGER {DIGIT}+
ID [a-zA-Z]+

%%

\(      { return YOPEN_PAREN;}
\)      { return YCLOSE_PAREN; }
nil     { return YNIL; }
false   { return YFALSE; }
true    { return YTRUE; }
{ID}    {  yylval.sval = strdup(yytext);  return YID;}
{INTEGER} {  yylval.sval = strdup(yytext); return YINTEGER;}
%%

