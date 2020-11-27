#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
#include "type.h"
#include "semantic.h"

extern FILE *yyin;
extern int syntax_err;
extern int semantic_err;
extern A_NODE *root;
extern FILE *yyin;

void initialize();
void print_ast();
void print_sem_ast(A_NODE *);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("source file not given\n");
        exit(1);
    }
    
    if ((yyin = fopen(argv[argc-1], "r")) == NULL) {
        printf("can not open input file: %s\n", argv[argc-1]);
        exit(1);
    }
    
    puts("\nstart syntax analysis");
    initialize();
    yyparse();
    
    if (syntax_err) {
        puts("syntax_err");
        return 1;
    }
    print_ast(root);
    
    puts("\nstart semantic analysis");
    semantic_analysis(root);
    
    if (semantic_err) {
        puts("semantic_err");
        return 1;
    }
    
    print_sem_ast(root);
    return 0;
}
