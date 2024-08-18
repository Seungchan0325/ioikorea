#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXM = 200005;

int n, m, low[MAXN], order[MAXN], pv;
bool chk[MAXN];
int ans[MAXM];
vector<pair<int, int>> graph[MAXN];

void dfs(int u, int p)
{
    chk[u] = true;
    order[u] = low[u] = ++pv;
    for(auto [v, i] : graph[u]) {
        if(v == p) continue;

        if(!chk[v]) {
            dfs(v, u);
            if(low[v] > order[u]) ans[i] = 1;
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], order[v]);
        }
    }
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
    }

    dfs(1, -1);
    for(int i = 0; i < m; i++) cout << ans[i];
}