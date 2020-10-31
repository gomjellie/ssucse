#include "3.h"

#include <stdio.h>
#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define N 8
#define INF 54321

static int w[N][N]; // w[i][j] i 부터 j까지의 weight
int d[N][N]; // i 에서 j로 갈때 최단경로
static int p[N][N]; // p[i][j] i ~ j 가는 중간 정점중에 가장 큰 인덱스

static void print_mat(const int arr[N][N]) {
    for (int i = 1; i < N; i++) {
        printf("%d: ", i);
        for (int j = 1; j < N; j++) {
            printf("%d\t", arr[i][j]);
        }puts("");
    }
}

static void print_path(int l, int r) {
    if (p[l][r] == 0) return;

    print_path(l, p[l][r]);
    printf("a%d -> ", p[l][r]);
    print_path(p[l][r], r);
}

static void floyd() {
    memcpy(d, w, sizeof(int) * N * N);
    
    for (int k = 1; k < N; k++)
        for (int i = 1; i < N; i++)
            for (int j = 1; j < N; j++) {
                if (d[i][k] + d[k][j] < d[i][j]) {
                    p[i][j] = k;
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
}

void q3() {
    for (int i = 1; i < N; i ++) for (int j = 1; j < N; j++) w[i][j] = i == j ? 0 : INF;
    w[N - 1][N - 2] = 4; w[N - 1][N - 6] = 10;
    w[N - 2][N - 1] = 3; w[N - 2][N - 4] = 18;
    w[N - 3][N - 2] = 6;
    w[N - 4][N - 3] = 15; w[N - 4][N - 5] = 2; w[N - 4][N - 6] = 19; w[N - 4][N - 7] = 5;
    w[N - 5][N - 4] = 1; w[N - 5][N - 3] = 12;
    w[N - 6][N - 7] = 10;
    w[N - 7][N - 4] = 8;

    floyd();

    printf("array D: \n"); print_mat(d);
    printf("array P: \n"); print_mat(p);

    int from = 5, to = 2;
    printf("a%d -> ", from);
    print_path(from, to);
    printf("a%d\n", to);
}

