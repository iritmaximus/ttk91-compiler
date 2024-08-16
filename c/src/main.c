#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "expr.h"

#define FILENAME "../docs/example-file-harder.k91"
//#define FILENAME "../docs/example-file.k91"
//#define FILENAME "../docs/example-file-simple.k91"

// scanner
extern FILE *yyin;
extern int yylex();
extern char *yytext;

// parser
extern int yyparse();


int program_print(struct expr *program)
{
    struct expr *current = program;

    do
    {
        if (expr_print(current)!=0)
            return 1;
        current = current->next;
    }
    while (current->next != NULL);

    return 0;

}

int main()
{
    yyin = fopen(FILENAME, "r");

    if (!yyin) {
        printf("Couldn't open file\n");
        return 1;
    }

    struct expr *parse_result = malloc(sizeof(*parse_result));
    if (!parse_result)
    {
        printf("ERROR: Failed to allocate memory for parse_result.\n");
        return 1;
    }


    if (yyparse(parse_result) == 0) {
        printf("Parse succesful :)\n");
    } else {
        printf("Parse failed\n");
        return 1;
    }

    if (program_print(parse_result)!=0)
        return 1;
    // TODO handle all frees

    return 0;
}
