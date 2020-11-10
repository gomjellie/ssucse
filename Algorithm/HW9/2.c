#include <stdio.h>
#include <stdbool.h>

typedef struct tuple {
    int e1;
    int e2;
    int e3;
} tuple_t;

bool cmp_tuple(tuple_t t1, tuple_t t2) {
    if (t1.e1 < t2.e1) {
        return true;
    } else if (t1.e1 == t2.e1) {
        if (t1.e2 < t2.e2)
            return true;
    }
    return false;
}

int v[256];

typedef bool (*cmp_f) (tuple_t, tuple_t);

typedef struct priority_queue {
    tuple_t body[256];
    int length;
    cmp_f cmp;
} pq_t;

void pq_init(pq_t *this, cmp_f cmp) {
    this->length = 0;
    this->cmp = cmp;
}

tuple_t pq_top(pq_t *this) {
    if (this->length == 0) return (tuple_t) {.e1 = -9, .e2 = -9, .e3 = -9};

    return this->body[1];
}

int pq_empty(pq_t *this) {
    return this->length == 0;
}

void pq_push(pq_t *this, tuple_t elem) {
    int cur = ++this->length;
    
    while (cur != 1 && this->cmp(this->body[cur / 2], elem)) {
        this->body[cur] = this->body[cur / 2];
        cur /= 2;
    }
    this->body[cur] = elem;
}

void pq_pop(pq_t *this) {
    if (pq_empty(this)) return;

    tuple_t last_elem = this->body[this->length --];
    
    size_t cur = 1;
    size_t child = 2;

    while (child <= this->length) {
        if (child < this->length && this->cmp(this->body[child + 1], this->body[child]) != 1)
            child ++;
        if (this->cmp(last_elem, this->body[child]) != 1) break;

        this->body[cur] = this->body[child];
        cur = child; child *= 2;
    }
    this->body[cur] = last_elem;
}

int find(int p) {
    if (v[p] == p) return p;
    return v[p] = find(v[p]);
}

void merge(int p, int q) {
    v[p] = v[q];
}

void q2() {
    int N, M;
    pq_t pq; pq_init(&pq, cmp_tuple);
    scanf("%d %d", &N, &M);
    int ans = 0;
    for (int i = 0; i <= N; i++) {
        v[i] = i;
    }

    for (int i = 0; i < M; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        pq_push(&pq, (tuple_t) {-c, a, b});
    }

    while (!pq_empty(&pq)) {
        tuple_t top = pq_top(&pq);
        int a = top.e2, b = top.e3, cost = -top.e1;
        int p = find(a), q = find(b);
        if (p != q) {
            merge(p, q);
            ans += cost;
        }
        pq_pop(&pq);
    }

    printf("%d", ans);
}

