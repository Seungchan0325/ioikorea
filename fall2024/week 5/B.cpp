#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<pair<int, int>> edges;
vector<int> graph[500];

set<pair<int, int>> bfs(pair<int, int> forbidden)
{
    vector<int> par(N+1, -1);
    vector<bool> vst(N+1);
    queue<int> q;
    q.push(1);
    par[1] = -1;
    vst[1] = true;
    while(!q.empty()) {
        auto u = q.front(); q.pop();
        for(auto v : graph[u]) {
            if(forbidden == make_pair(u, v) || vst[v]) continue;
            q.push(v);
            vst[v] = true;
            par[v] = u;
        }
    }

    set<pair<int, int>> ret;
    for(int i = N; i != -1; i = par[i]) {
        if(par[i] != -1) ret.emplace(par[i], i);
    }

    return ret;
}

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
        graph[u].push_back(v);
    }

    auto s = bfs({-1, -1});

    for(int i = 0; i < M; i++) {
        auto [u, v] = edges[i];
        if(s.count({u, v})) {
            auto t = bfs(edges[i]);
            if(t.empty()) cout << "-1\n";
            else cout << t.size() << "\n";
        } else {
            if(s.empty()) cout << "-1\n";
            else cout << s.size() << "\n";
        }
    }
}