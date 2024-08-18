#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, root[MAXN];
vector<tuple<int, int, int>> edges;

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

bool merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return false;
    root[y] = x;
    return true;
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(w, u, v);
    }
    iota(root, root + n + 1, 0);

    long long ans = 0;
    sort(edges.begin(), edges.end());
    for(auto [w, u, v] : edges) {
        if(merge(u, v)) {
            ans += w;
        }
    }
    cout << ans;
}