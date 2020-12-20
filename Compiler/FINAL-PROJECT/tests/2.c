typedef struct node {
    char *name;
} node_t;

void* func1(node_t *n, char *name) {
    // this is comment
    n->name = name;

    return n;
}

int main() {
    node_t n;
    node_t *ptr = func1(&n, "name1");
    printf("%s\n", ptr->name);
    n.name = "name2";
    printf("%s\n", ptr->name);

    return 0;
}
