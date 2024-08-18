#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, M, deg[MAXN];
vector<int> graph[MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        deg[v]++;
    }

    priority_queue<int> pq;
    for(int i = 1; i <= N; i++) {
        if(deg[i] == 0) {
            pq.push(-i);
        }
    }
    while(!pq.empty()) {
        auto u = pq.top(); pq.pop();
        u = -u;
        cout << u << " ";
        for(auto v : graph[u]) {
            if(--deg[v] == 0) {
                pq.push(-v);
            }
        }
    }
}