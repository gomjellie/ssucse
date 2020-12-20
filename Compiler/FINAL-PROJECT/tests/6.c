
int fibo(int n)
{
	if (n < 2) return n;
	if (n == 1)
		return 1;
	return fibo(n - 1) + fibo(n - 2);
}

int main()
{
	int i = 0;
	for (i = 1; i < 10; i ++) {
		printf("%d\n", fibo(i));
	}

	return 0;
}
