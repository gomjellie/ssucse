#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include "type.h"

extern FILE *yyin;
extern int syntax_err;
extern A_NODE *root;
extern FILE *yyin;

void initialize();
void print_ast();

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("source file not given\n");
        exit(1);
    }
    
    if ((yyin = fopen(argv[argc-1], "r")) == NULL) {
        printf("can not open input file: %s\n", argv[argc-1]);
        exit(1);
    }
    
    initialize();
    yyparse();
    
    if (syntax_err)
        return 1;
    
    print_ast(root);
    return 0;
}
