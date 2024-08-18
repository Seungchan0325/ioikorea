#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, dep[MAXN];
bool chk[MAXN];
vector<int> graph[MAXN];

int bfs(int s)
{
    memset(chk, 0, sizeof(chk));
    queue<tuple<int, int, int>> q;
    chk[s] = true;
    dep[s] = 0;
    q.emplace(s, 0, -1);
    while(!q.empty()) {
        auto [u, depth, p] = q.front(); q.pop();
        for(auto v : graph[u]) {
            if(v == p) continue;
            if(chk[v]) {
                return dep[v] + dep[u] + 1;
            }
            dep[v] = depth+1;
            chk[v] = true;
            q.emplace(v, depth+1, u);
        }
    }
    assert(0);
    return -1;
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

    int ret = 1e9;
    for(int i = 1; i <= n; i++) {
        ret = min(ret, bfs(i));
    }
    cout << ret;
}