#include "2.h"
#include <stdio.h>
#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define N 8
#define INF 54321

static int w[N][N]; // w[i][j] i 부터 j까지의 weight
static int d[N][N]; // i 에서 j로 갈때 최단경로
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
    printf("v%d -> ", p[l][r]);
    print_path(p[l][r], r);
}

static void floyd() {
    memcpy(d, w, sizeof(int) * N * N);
    
    for (int k = 1; k < N ; k++)
        for (int i = 1; i < N; i++)
            for (int j = 1; j < N; j++) {
                if (d[i][k] + d[k][j] < d[i][j]) {
                    p[i][j] = k;
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
}

void q2() {
    for (int i = 1; i < N; i ++) for (int j = 1; j < N; j++) w[i][j] = i == j ? 0 : INF;
    w[1][2] = 4; w[1][6] = 10;
    w[2][1] = 3; w[2][4] = 18;
    w[3][2] = 6;
    w[4][3] = 15; w[4][5] = 2; w[4][6] = 19; w[4][7] = 5;
    w[5][4] = 1; w[5][3] = 12;
    w[6][7] = 10;
    w[7][4] = 8;

    floyd();

    printf("array D: \n"); print_mat(d);
    printf("array P: \n"); print_mat(p);

    int from = 3, to = 6;
    printf("v%d -> ", from);
    print_path(from, to);
    printf("v%d\n", to);
}

