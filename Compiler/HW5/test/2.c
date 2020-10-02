void func1() {
    // 12: redeclaration of identifier
    int asdf = 10;
    int asdf = 20;
    struct node *n;
}

typedef struct node {
    char *name;
} node_t;

struct nope {
    char *name;
};
