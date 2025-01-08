#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100505;
const ll LOGN = 20;

ll N, sparse[MAXN][LOGN+1], sparse2[MAXN][LOGN+1], depth[MAXN];
vector<pair<ll, ll>> graph[MAXN];

void dfs(ll u, ll p)
{
    for(ll i = 1; i <= LOGN; i++) {
        sparse[u][i] = sparse[sparse[u][i-1]][i-1];
        sparse2[u][i] = sparse2[sparse[u][i-1]][i-1] + sparse2[u][i-1];
    }
    for(auto [v, d] : graph[u]) {
        if(v == p) continue;
        depth[v]  = depth[u] + 1;
        sparse[v][0] = u;
        sparse2[v][0] = d;
        dfs(v, u);
    }
}

ll lca(ll u, ll v)
{
    ll ret = 0;
    if(depth[u] < depth[v]) swap(u, v);
    ll diff = depth[u] - depth[v];
    for(ll i = 0; i <= LOGN; i++) {
        if(diff&(1<<i)) {
            ret += sparse2[u][i];
            u = sparse[u][i];
        }
    }

    if(u == v) return ret;

    for(ll i = LOGN; i >= 0; i--) {
        if(sparse[u][i] != sparse[v][i]) {
            ret += sparse2[u][i] + sparse2[v][i];
            u = sparse[u][i];
            v = sparse[v][i];
        }
    }

    ret += sparse2[u][0] + sparse2[v][0];

    return ret;
}

int main()
{
    cin >> N;
    for(ll i = 1; i < N; i++) {
        ll u, v, d;
        cin >> u >> v >> d;
        graph[u].emplace_back(v, d);
        graph[v].emplace_back(u, d);
    }
    dfs(1, -1);
    ll Q;
    cin >> Q;
    while(Q--) {
        ll u, v;
        cin >> u >> v;
        ll result = lca(u, v);
        cout << result << "\n";
    }
}