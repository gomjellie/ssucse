#include <stdio.h>
#include <math.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

const long long INF = 987654321;
int W[10][10];
int D[10][1 << 5];
int N;

int tsp(int cur, int visited) {
    if (visited == (1 << N) - 1) {
        if (W[cur][0] == 0) return INF;
        return W[cur][0];
    }

    int *ret = &D[cur][visited];
    if (*ret != 0) return *ret;
    *ret = INF;
    for (int next = 0; next <= N; next++) {
        if (visited & (1 << next)) continue;
        if (W[cur][next] == 0) continue;
        *ret = MIN(*ret, tsp(next, visited | (1 << next)) + W[cur][next]);
    }
    return *ret;
}

int main() {
    scanf("%d\n", &N);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &W[i][j]);
        }
    }

    int ans = tsp(0, 1);

    printf("%d\n", ans);
}
