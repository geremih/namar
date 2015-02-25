
all: lex.yy.c grammar.tab.c main.c lisp.c
	gcc lex.yy.c grammar.tab.c main.c lisp.c emit.c -lfl -ly -o compile

lex.yy.c: lexer.l grammar.tab.c
	flex lexer.l

grammar.tab.c: grammar.y
	bison -d grammar.y

clean:
	rm -rf grammar.tab.h grammar.tab.c lex.yy.c a.out
