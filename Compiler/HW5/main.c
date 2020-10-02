
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
extern FILE *yyin;
extern int syntax_err;
extern A_NODE *root;
FILE *fout;
void initialize();
extern FILE *yyin;

int main(int argc, char *argv[]) {
	if (argc<2) {
		printf("source file not given\n");
		exit(1);
	}
	if ((yyin=fopen(argv[argc-1],"r"))==NULL) {
		printf("cannot open input file: %s\n",argv[argc-1]);
		exit(1);
	}
	
	initialize();
	yyparse();
	if (syntax_err) exit(1);
	printf("\n");
	return 0;
}
