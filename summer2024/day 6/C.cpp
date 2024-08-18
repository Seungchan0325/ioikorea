#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m;
bool chk[MAXN];
vector<int> graph[MAXN];

void dfs(int u)
{
    cout << u << " ";
    chk[u] = true;
    for(auto v : graph[u]) {
        if(chk[v]) continue;
        dfs(v);
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
    dfs(1);
}