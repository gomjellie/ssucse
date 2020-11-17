#include <stdbool.h>
#include <stdio.h>

static int w[6] = { 2, 10, 13, 17, 22, 42};
static int W = 0;
static int include[6];
static double monte_promising[6];
static double monte_non_promising[6];

#define PRINT_MONTE_CARLO

bool is_promising(int i, int weight, int total) {
    if (weight + total >= W && (weight == W || weight + w[i + 1] <= W))
        return true;

    return false;
}

void sum_of_subset(int i, int weight, int total) {
    if (is_promising(i, weight, total)) {
        monte_promising[i] ++;
        if (W == weight) {
            for (int j = 0; j < 6; j++)
                printf("%d ", include[j]);
            puts("");
            return;
        }
        
        include[i + 1] = w[i + 1];
        sum_of_subset(i + 1, weight + w[i + 1], total - w[i + 1]);
        include[i + 1] = 0;
        sum_of_subset(i + 1, weight, total - w[i + 1]);
        return;
    }
    monte_non_promising[i] ++;
}

int main() {
    int total = 0;
    for (int i = 0; i < 6; i++)
        total += w[i];
    W = 52;
    sum_of_subset(-1, 0, total);

#ifdef PRINT_MONTE_CARLO
    double probs[6];
    int nnodes[6];
    for (int i = 0; i < 6; i++) {
        nnodes[i] = monte_promising[i] + monte_non_promising[i];
        probs[i] = monte_promising[i] / nnodes[i];
    }

    double nnode = 1;
    double sum = 1;
    for (int i = 0; i < 6; i++) {
        printf("%.2f%s", nnode, i == 5 ? "\n" : " + ");
        nnode = nnodes[i] * probs[i];
        sum += nnode;
    }

    printf("sum : %f", sum);
#endif
}
