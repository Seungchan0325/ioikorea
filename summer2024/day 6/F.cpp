#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;
const ll INF = 1e18;

int n, m, s, root[MAXN];
ll dist[MAXN];
vector<pair<int, ll>> graph[MAXN];

int main()
{
    cin >> n >> m;
    cin >> s;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        // graph[v].emplace_back(u, w);
    }

    for(int i = 1; i <= n; i++) dist[i] = INF;
    priority_queue<pair<ll, int>> pq;
    dist[s] = 0;
    pq.emplace(0, s);
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;
        if(d > dist[u]) continue;
        for(auto [v, w] : graph[u]) {
            if(d + w < dist[v]) {
                dist[v] = d + w;
                pq.emplace(-dist[v], v);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(dist[i] == INF) cout << "-1\n";
        else cout << dist[i] << "\n";
    }
}