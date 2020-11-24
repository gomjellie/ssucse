#include "queue.h"
#include "priority_queue.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct pair {
    int price;
    int weight;
};

struct pair products[] = {
    {20, 2},
    {30, 5},
    {35, 7},
    {12, 3},
    {3, 1},
};

int N = 4;
int W = 9;

int maxprofit;

bool is_promising(int i, int profit, int weight) {
    if (weight > W) return false;

    int totweight;
    int k, j;
    double bound;
    struct pair *iter;

    j = i + 1;
    bound = profit;
    totweight = weight;

    while ((j <= N) && (totweight + products[j].weight <= W)) {
        iter = &products[j];
        totweight += iter->weight;
        bound += iter->price;
        j++;
    }
    k = j;
    if (k <= N)
        bound = bound + (W - totweight) * products[k].price / products[k].weight;
    
    return bound > maxprofit;
}

void dfs(int i, int profit, int weight) {
    if (weight <= W && profit > maxprofit) {
        maxprofit = profit;
    }

    if (is_promising(i, profit, weight)) {
        printf("(%d, %d, %d)\n", i, profit, weight);
        dfs(i + 1, profit + products[i + 1].price, weight + products[i + 1].weight);
        dfs(i + 1, profit, weight);
    }
}

struct node {
    int level;
    int profit;
    int weight;
};

struct node *node_new(int level, int profit, int weight) {
    struct node *this = malloc(sizeof(struct node));

    this->level = level;
    this->profit = profit;
    this->weight = weight;

    return this;
}

struct node *node_dup(struct node *u) {
    struct node *this = malloc(sizeof(struct node));

    // memcpy(this, u, sizeof(struct node));
    this->level = u->level;
    this->profit = u->profit;
    this->weight = u->weight;
    return this;
}

// branch and bound for breadh_first & best_first search
double bound(struct node *u) {
    int j, k;
    int totweight; double result;
    if (u->weight >= W)
        return 0;
    if (u->level >= N)
        return 0;
    
    result = u->profit;
    j = u->level + 1;
    totweight = u->weight;

    while ((j <= N) && (totweight + products[j].weight <= W)) {
        totweight = totweight + products[j].weight;
        result = result + products[j].price;
        j ++;
    }
    k = j;
    if (k <= N)
        result = result + (W - totweight) * products[k].price / products[k].weight;
    
    return result;
}

void breadth_first_search() {
    queue *q = queue_new(sizeof(struct node));
    struct node *u, *v;

    u = node_new(0, 0, 0);
    v = node_new(-1, 0, 0); maxprofit = 0;
    queue_push(q, v);
    while (!queue_empty(q)) {
        v = queue_front(q); queue_pop(q);
        printf("(%d, %d, %d)\n", v->level, v->profit, v->weight);
        u->level = v->level + 1;
        u->profit = v->profit + products[u->level].price;
        u->weight = v->weight + products[u->level].weight;

        if ((u->weight <= W) && (u->profit > maxprofit))
            maxprofit = u->profit;
        if (bound(u) > maxprofit) queue_push(q, u);
        u->weight = v->weight;
        u->profit = v->profit;
        if (bound(u) > maxprofit) queue_push(q, u);
    }
}

int cmp_node(const void *a, const void *b) {
    // put highest profit on top of PQ
    struct node e1 = *(struct node *)a;
    struct node e2 = *(struct node *)b;
    if (e1.profit > e2.profit) return -1;
    if (e1.profit == e2.profit) return 0;
    return 1;
}

void best_first_search() {
    priority_queue *pq = pq_new(128, sizeof(struct node), cmp_node);
    struct node *u, *v, *_v;

    u = node_new(0, 0, 0);
    v = node_new(-1, 0, 0); maxprofit = 0;
    pq_push(pq, v);
    while (!pq_empty(pq)) {
        v = node_dup(pq_top(pq)); pq_pop(pq);
        _v = node_dup(v);
        printf("(%d, %d, %d)\n", v->level, v->profit, v->weight);
        if (bound(v) <= maxprofit)
            continue;
        
        u->level = v->level + 1;
        u->profit = v->profit + products[u->level].price;
        u->weight = v->weight + products[u->level].weight;

        if ((u->weight <= W) && (u->profit > maxprofit))
            maxprofit = u->profit;
        if (bound(u) > maxprofit)
            pq_push(pq, u);
        u->weight = _v->weight;
        u->profit = _v->profit;
        if (bound(u) > maxprofit)
            pq_push(pq, u);
    }
}

int main() {
    dfs(-1, 0, 0);
    printf("Depth First Search: %d\n", maxprofit);
    maxprofit = 0;

    breadth_first_search();
    printf("Breadth First Search: %d\n", maxprofit);
    maxprofit = 0;

    best_first_search();
    printf("Best First Search: %d\n", maxprofit);
    maxprofit = 0;

    return 0;
}
