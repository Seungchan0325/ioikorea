#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

int N, M, root[MAXN];
vector<tuple<int, int, int>> edges;

int find(int x)
{
    if(x == root[x]) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    root[y] = x;
}

using ll = long long;

int main()
{
    cin >> N >> M;
    iota(root, root + N + 1, 0);
    ll s = 0;
    for(int i = 0; i < M; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(w, u, v);
        s += w;
    }

    sort(edges.begin(), edges.end());

    for(auto [w, u, v] : edges) {
        if(find(u) != find(v)) {
            merge(u, v);
            s -= w;
        } else if(w < 0) {
            s -= w;
        }
    }

    cout << s;
}