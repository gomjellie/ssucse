
int main(int argc, char *argv[]) { 
	int integer = 10;
	int *int_ptr =&integer; 
	int **int_double_ptr = &int_ptr; 
	*int_ptr;
	**int_double_ptr;
}
