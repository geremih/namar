.PHONY : clean test

all: lex.yy.c grammar.tab.c main.c lisp.c emit.c utils.c convert.c
	gcc lex.yy.c grammar.tab.c main.c lisp.c emit.c utils.c convert.c -lfl -ly -o compile

lex.yy.c: lexer.l grammar.tab.c
	flex lexer.l

grammar.tab.c: grammar.y
	bison -d grammar.y

runtime: out.s runtime.c lisp.c convert.c utils.c 
	gcc runtime.c lisp.c convert.c utils.c out.s -o runtime 

test:
	python run_tests.py

clean:
	rm -rf grammar.tab.h grammar.tab.c lex.yy.c compile runtime
