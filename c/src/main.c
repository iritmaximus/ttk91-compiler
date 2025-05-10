#include <stdlib.h>
#include <stdio.h>
#include "error.h"
#include "token.h"
#include "program.h"

// #define FILENAME "../docs/example-file-harder.k91"
#define FILENAME "../../docs/example-file.k91"
// #define FILENAME "../docs/example-file-simple.k91"

// scanner
extern FILE *yyin;
extern int yylex();
extern char *yytext;

// parser
extern int yyparse(struct expr*);



int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        printf("Using default file %s\n", FILENAME);
        yyin = fopen(FILENAME, "r");
    }
    else
        yyin = fopen(argv[1], "r");

    if (!yyin) {
        printf("Couldn't open file\n");
        return FILE_ERROR;
    }

    struct expr *parse_result = malloc(sizeof(*parse_result));
    if (!parse_result)
    {
        fclose(yyin);
        printf("ERROR: Failed to allocate memory for parse_result.\n");
        return ALLOC_FAILED;
    }


    if (yyparse(parse_result) != 0) 
    {
        fclose(yyin);
        program_free(parse_result);
        printf("Error parsing the file\n");
        return PARSE_ERROR;
    }
    printf("Parse successful\n");

    fclose(yyin);

    int err = program_print(parse_result);
    if (err!=0)
    {
        printf("Error printing program\n");
        return err;
    }

    printf("\n");
    err = program_print_intel_asm(parse_result);
    if (err!=0)
    {
        printf("Error printing program in intel asm.\n");
        return err;
    }

    program_free(parse_result);
    // TODO handle errors with assertions

    return 0;
}
