
void sort(int a[ ], int n) {

	int i, j, x;

	for (i=0; i<n; i++)
		for (j=i+1; j<n; j=j+1)
			if (a[i]<a[j]) {
				x=a[i]; a[i]=a[j]; a[j]=x;}

}

int main() {
	int a[3];
	int i;
	a[0] = 1;
	a[1] = 3;
	a[2] = 2;
	sort(a, 3);
	for (i = 0; i < 3; i++) {
		printf("%d ", a[i]);
	}

	return 0;
}
