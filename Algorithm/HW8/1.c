#include "1.h"

#include <stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define N 8
#define INF 54321
static int w[N][N]; // w[i][j] i 부터 j까지의 weight
static int d[N][N]; // d[i][j] i 부터 j까지 가는 최단 거리
static int p[N][N]; // p[i][j] i ~ j 가는 중간 정점중에 가장 큰 인덱스 (중간에 껴있는 voltex)

static void simpleShortPath() {
    for (int i = 1; i < N; i++)
        for (int j = 1; j < N; j++)
            d[i][j] = w[i][j];
    
    for (int m = 2; m < N - 1; m++)
        for (int i = 1; i < N; i++)
            for (int j = 1; j < N; j++)
                for (int k = 1; k < N; k++) {
                    if (d[i][k] + w[k][j] < d[i][j]) {
                        d[i][j] = d[i][k] + w[k][j];
                        p[i][j] = k;
                    }
                }
}

static void print_path(int l, int r) {
    if (p[l][r] == 0) return;

    print_path(l, p[l][r]);
    printf("v%d -> ", p[l][r]);
    print_path(p[l][r], r);
}

void q1() {
    for (int i = 1; i < N; i ++) for (int j = 1; j < N; j++) w[i][j] = i == j ? 0 : INF;
    w[1][2] = 4; w[1][6] = 10;
    w[2][1] = 3; w[2][4] = 18;
    w[3][2] = 6;
    w[4][3] = 15; w[4][5] = 2; w[4][6] = 19; w[4][7] = 5;
    w[5][4] = 1; w[5][3] = 12;
    w[6][7] = 10;
    w[7][4] = 8;

    simpleShortPath();

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (d[i][j] >= INF) continue;
            // printf("shortest length from %d to %d = %d\n", i, j, d[i][j]);
            printf("v%d -> ", i);
            print_path(i, j);
            printf("v%d\n", j);
        }
    }
}

