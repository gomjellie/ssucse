int fun() {

}

int main(int argc, char *argv[]) { 
	int a;
	int *b =&a; 
	int **p = &b; 
	*b;
	**p;
	fun();
	return 0;
}
