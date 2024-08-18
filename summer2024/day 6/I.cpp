#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, low[MAXN], order[MAXN], pv;
bool chk[MAXN];
int ans[MAXN];
vector<int> graph[MAXN];

void dfs(int u, int p)
{
    chk[u] = true;
    order[u] = low[u] = ++pv;
    for(auto v : graph[u]) {
        if(v == p) continue;

        if(!chk[v]) {
            dfs(v, u);
            if(low[v] >= order[u]) ans[u] = 1;
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
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    chk[1] = true;
    int cnt = 0;
    for(auto u : graph[1]) {
        if(!chk[u]) {
            dfs(u, 1);
            cnt++;
        }
    }
    if(cnt >= 2) ans[1] = 1;
    for(int i = 1; i <= n; i++) cout << ans[i];
}