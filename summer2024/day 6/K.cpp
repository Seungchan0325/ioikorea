#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;

bool chk[MAXN];
int x, y, N, M;
vector<int> graph[2][MAXN];

int dfs(int u, vector<int> g[MAXN])
{
    chk[u] = true;
    int ret = 1;
    for(auto v : g[u]) {
        if(chk[v]) continue;
        ret += dfs(v, g);
    }
    return ret;
}

int main()
{
    cin >> x >> y >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        graph[0][v].push_back(u);
        graph[1][u].push_back(v);
    }

    int a, b, c;
    a = b = c = 0;
    for(int i = 0; i < N; i++) {
        memset(chk, 0, sizeof(chk));
        int sz = dfs(i, graph[1]);
        if(N - sz < x) a++;
        if(N - sz < y) b++;
        memset(chk, 0, sizeof(chk));
        sz = dfs(i, graph[0]);
        if(sz > y) c++;
    }
    cout << a << "\n" << b << "\n"<< c << "\n";
}