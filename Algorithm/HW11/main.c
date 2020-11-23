#include <stdio.h>
#include <stdbool.h>

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
        printf("include %d ", products[i + 1].weight);
        dfs(i + 1, profit + products[i + 1].price, weight + products[i + 1].weight);
        printf("exclude %d ", products[i + 1].weight);
        dfs(i + 1, profit, weight);
    }
}


int main() {
    dfs(-1, 0, 0);

    printf("%d", maxprofit);

    return 0;
}

