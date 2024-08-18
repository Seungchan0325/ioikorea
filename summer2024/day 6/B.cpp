#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m;
bool chk[MAXN];
vector<int> graph[MAXN];

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    queue<int> q;
    chk[1] = true;
    q.push(1);
    while(!q.empty()) {
        auto u = q.front(); q.pop();
        cout << u << " ";
        for(auto v : graph[u]) {
            if(chk[v]) continue;
            chk[v] = true;
            q.push(v);
        }
    }
}