#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, t;
vector<int> graph[MAXN];

int main()
{
    cin >> n >> m >> t;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        if(t) graph[v].push_back(u);
    }

    for(int i = 0; i < n; i++) {
        sort(graph[i].begin(), graph[i].end());
        cout << graph[i].size() << " ";
        for(auto j : graph[i]) cout << j << " ";
        cout << "\n";
    }
}