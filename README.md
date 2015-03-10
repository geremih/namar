# Namar 
A whacky and impulsive Lisp compiler.


## Implementation
All top-level expressions can be thought be as a list of expressions.
As the language does not support side-affects as of now, having more
than one expression in the top-level will lead to only the value of the
last expression being returned and the values of the other expressions
being discarded.

Each expression can be [the definitions are in lisp.h]  
1. an integer, identifier - the atoms of the language
2. or a list - which is formed by consing together atoms and lists.  

eg. (cons a b)  
A cons is represented as a pair in C.


\---------------  
|  a   |  b   |  
\---------------

(list a b c) := '(a b c) = (cons a (cons b (cons c nil)))


\---------------      ---------------       ---------------  
|  a   |  -   |----> |  b   |      | ----->|  c   |  nil |  
\---------------      ---------------       ---------------





## Running tests
`  make test`

