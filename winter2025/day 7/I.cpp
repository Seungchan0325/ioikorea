#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> edges;
    vector<vector<int>> graph(N+1);
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
    }
    sort(edges.begin(), edges.end());
    set<pair<int, int>> s;
    vector<array<int, 3>> ans;
    vector<vector<pair<int, int>>> c(N+1);
    for(int i = 0; i < M; i++) {
        auto [u, v] = edges[i];
        while(c[u].size() && s.count(c[u].back())) {
            c[u].pop_back();
        }
        while(c[v].size() && s.count(c[v].back())) {
            c[v].pop_back();
        }
        if(c[u].size()) {
            ans.push_back({c[u].back().first + c[u].back().second - u, u, v});
            s.insert(c[u].back());
            c[u].pop_back();
        } else if(c[v].size()) {
            ans.push_back({c[v].back().first + c[v].back().second - v, v, u});
            s.insert(c[v].back());
            c[v].pop_back();
        } else {
            c[v].push_back(edges[i]);
            c[u].push_back(edges[i]);
        }
    }
    cout << ans.size() << "\n";
    for(auto [u, v, w] : ans) {
        cout << u << " " << v << " " << w << "\n";
    }
}