#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TREE_LEN 256

typedef struct element {
    int parent;
    int rank;
} element_t;

typedef struct _disjoint_set {
    struct element tree[TREE_LEN];
} disjoint_set_t;

disjoint_set_t *set_alloc();
struct element *set_find(disjoint_set_t *this, int elem);
int set_union(disjoint_set_t *this, int e1, int e2);
void set_print(disjoint_set_t *this);
void set_free(disjoint_set_t *this);

int main(int argc, char *argv[]) {
    int n;
    disjoint_set_t *djset = set_alloc();
    
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        char cmd, e1, e2;
        cmd = getchar(); getchar();
        if (cmd == 's') { // set
            e1 = getchar(); getchar();
            djset->tree[(int)e1].parent = e1;
            djset->tree[(int)e1].rank = 0;
            continue;
        }
        if (cmd == 'u') { // union
            e1 = getchar(); getchar();
            e2 = getchar(); getchar();
            element_t *p = set_find(djset, (int)e1);
            element_t *q = set_find(djset, (int)e2);
            set_union(djset, p->parent, q->parent);
        }
        if (cmd == 'p') {
            set_print(djset);
        }
    }    
}

// disjoint set 생성.
disjoint_set_t *set_alloc() {
    disjoint_set_t *this = malloc(sizeof(disjoint_set_t));
    for (int i = 0; i < TREE_LEN; i++) {
        this->tree[i].parent = 0;
        this->tree[i].rank = 0;
    }

    return this;    
}

struct element *set_find(disjoint_set_t *this, int elem) {
    if (this->tree[elem].parent == 0) return NULL;

    if (this->tree[elem].parent == elem)
        return &this->tree[elem];
    
    return set_find(this, this->tree[elem].parent);
}

int set_union(disjoint_set_t *this, int e1, int e2) {
    struct element *p = set_find(this, e1);
    struct element *q = set_find(this, e2);

    if (p->parent == q->parent) return -1; // 이미 같은 set

    if (p->rank < q->rank) {
        p->parent = q->parent;
        return 0;
    }

    if (p->rank == q->rank) {
        p->rank ++;
    }
    q->parent = p->parent;
    
    return 0;
}

void set_free(disjoint_set_t *this) {
    free(this);
}

void set_print(disjoint_set_t *this) {
    for (int i = (int)'a'; i <= (int)'z'; i++) {
        element_t *e = set_find(this, i);
        if (e == NULL) continue;

        printf("%c belongs to %c group\n", i, e->parent);
    }
    puts("");
}
