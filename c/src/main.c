#include "token.h"
#include <stdio.h>

#define FILENAME "../docs/example-file-harder.k91"

// scanner
extern FILE *yyin;
extern int yylex();
extern char *yytext;

// parser
extern int yyparse();

int main()
{
    yyin = fopen(FILENAME, "r");

    if (!yyin) {
        printf("Couldn't open file\n");
        return 1;
    }

    if (yyparse() == 0) {
        printf("Parse succesful :)\n");
    } else {
        printf("Parse failed\n");
        return 1;
    }

    return 0;
}
