# TTK-91 Compiler
This is my implementation of the TTK-91 Compiler in C. 

## Overview
First the soucre file is read and then fed into `scanner.c` produced by `scanner.flex` and 
lexing is done. After lexing the tokens are parsed by `parser.c` given by `parser.bison`. 
The parser will output an AST (Abstract Syntax Tree) which will be then transformed into an IR
(Intermediate Representation).


## Scanner
The scanner reads through the whole file and splits it up into tokens according to the rules
defined in `scanner.flex`. The rules are made up of mostly regular expressions. Few notable
mentions are the `comment` token which matches everything after `;` until the EOF (End Of File)
and `label` token which matches all words made up of letters in the Finnish alphabet + numbers + `_`
starting with a letter.

## Parser
The parser matches the tokens given by `scanner.c` to rules given in `parser.bison`. The left side
represents a single non-terminal token and the right side represents all decompositions the
non-terminal can be. For example if we had rule `expr: value TOKEN_PLUS value;`, and 
`value: TOKEN_NUM;` we could match all strings (assuming the scanner is normal) that have the from
`x + y`. We then could say that `expr: value TOKEN_PLUS value { /* do C things */}` and
feed the tokens to a function that creates a C representation of the same expression.
In the C block `$n` means the n-th tokens of the rule and $$ means the left side of the rule.
Example: `value: TOKEN_NUM { $$ = $1; }` means that that rule is equal to the first token of the 
rule. Adding to that `expr: value TOKEN_PLUS value { $$ = $1 + $3; }` means that expr is equal to
both of the numbers added together. Read more about this from:
`Introduction to Compilers and Language Design, Prof. Douglas Thain, Second Edition`.

## Types
TODO

### Expr
`expr` represents basically a line. It can contain a normal instruction, compiler definition or
a comment. 

### Value
