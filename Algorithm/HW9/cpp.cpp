// #include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <utility>

#define PII pair<int,int>
 
using namespace std;
 
const int N = 1005, INF = 2140000000;
 
vector<PII> ad[N];  // ad[i] : i 노드가 출발지인 간선들, first = 목적지, second = 비용
int dist[N];        // dist[i] : 선택된 노드들과 i 노드가 연결되어 있는 간선의 비용 중 최소비용
bool selected[N];   // selected[i] : i 가 이전에 선택된 노드인가?
 
long long prim(int pn){
    long long ret = 0;
    for(int i=1; i<=pn; i++){ // 초기화
        dist[i] = INF;
        selected[pn] = false;
    }
    dist[1] = 0;              // 1번 노드부터 선택
    for(int i=1; i<=pn; i++){
        int now=-1, min_dist = INF;
        for(int j=1; j<=pn; j++){
            if(!selected[j] && min_dist > dist[j]){
                min_dist = dist[j];
                now = j;
            }
        }
        if(now<0) return (long long)INF; // 연결 그래프가 아님
        ret+=min_dist;
        selected[now] = true;
        for(auto edge: ad[now])
            dist[edge.first] = min(dist[edge.first], edge.second);
    }
    return ret;
}
 
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    while(m--){
        int v1,v2,c;
        scanf("%d %d %d",&v1,&v2,&c);
        ad[v1].push_back(PII(v2,c));
        ad[v2].push_back(PII(v1,c));
    }
    printf("%lld",prim(n));
    return 0;
}
