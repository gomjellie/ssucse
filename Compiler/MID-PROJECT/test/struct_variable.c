typedef struct node {
    char *name;
} node_t;

typedef struct nope {
    char *name;
} nope_t;

void func1() {
    nope_t k;
    k.name = "asdf";
    printf(k.name);
}
