
void *function(int *a) {
    return a;
}

int main(int argc, char *argv[]) {
    int a;
    void *(*fptr[10 + 5]) (int *);
    fptr[0] = function;

    fptr[0](&a);
}
