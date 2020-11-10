#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define N 128
#define INF 7654321
#define MIN(a,b) (((a)<(b))?(a):(b))

typedef struct pair {
    int first;
    int second;
} pair_t;

typedef struct vector {
    pair_t body[256];
    size_t head;
    size_t rear;
} vector_t;

void vector_init(vector_t *this) {
    this->head = 0;
    this->rear = 0;
}

void vector_push_back(vector_t *this, pair_t elem) {
    this->body[this->rear ++] = elem;
}


vector_t ad[N];  // ad[i] : i 노드가 출발지인 간선들, first = 목적지, second = 비용
int dist[N];        // dist[i] : 선택된 노드들과 i 노드가 연결되어 있는 간선의 비용 중 최소비용
bool selected[N];   // selected[i] : i 가 이전에 선택된 노드인가?

int prim(int pn){
    int ret = 0;
    for(int i = 1; i <= pn; i++){ // 초기화
        dist[i] = INF;
        selected[pn] = false;
    }
    dist[1] = 0;              // 1번 노드부터 선택
    for(int i = 1; i <= pn; i++){
        int now = -1, min_dist = INF;
        for(int j = 1; j <= pn; j++){
            if(!selected[j] && min_dist > dist[j]){
                min_dist = dist[j];
                now = j;
            }
        }
        if (now < 0) return INF; // 연결 그래프가 아님
        ret += min_dist;
        selected[now] = true;
        for (int i = ad[now].head; i < ad[now].rear; i ++) {
            pair_t edge = ad[now].body[i];
            dist[edge.first] = MIN(dist[edge.first], edge.second);
        }
    }
    return ret;
}

void q1() {
    int n,m; // n: vertex 개수, m: edge개수
    scanf("%d %d", &n, &m);
    while(m--){
        int v1,v2,c;
        scanf("%d %d %d",&v1,&v2,&c);
        vector_push_back(&ad[v1], (pair_t) {v2, c});
        vector_push_back(&ad[v2], (pair_t) {v1, c});
    }
    printf("%d", prim(n));
    return;
}
