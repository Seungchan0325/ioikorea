#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;
const ll INF = 1e18;

int n, m, s, t, done[MAXN];
ll dist[MAXN];
vector<pair<int, ll>> graph[MAXN];

int main()
{
    cin >> n >> m;
    cin >> s >> t;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    for(int i = 1; i <= n; i++) dist[i] = INF;
    priority_queue<pair<ll, int>> pq;
    pq.emplace(0, s);
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        d = -d;

        dist[u] = min(d, dist[u]);
        if(dist[u] < d) {
            dist[u] = d;
            done[u] = true;
            if(u == t) break;
        }
        for(auto [v, w] : graph[u]) {
            if(!done[v]) pq.emplace(-d-w, v);
        }
    }

    cout << dist[t];
}