
int main() { 
	int a = 919;
	int *b =&a; 
	int **p = &b;
	printf("%d, %d", *b, **p);
	return 0;
}
