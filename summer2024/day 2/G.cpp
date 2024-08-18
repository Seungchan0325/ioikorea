#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, sz[MAXN], chk[MAXN], erased[MAXN], ans[MAXN];
vector<int> graph[MAXN];

void get_sz(int u, int p)
{
    sz[u] = 1;
    for(auto v : graph[u]) {
        if(erased[v] || v == p) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int u, int p, int ssz)
{
    for(auto v : graph[u]) {
        if(erased[v] || v == p) continue;
        if(sz[v] > ssz/2) return get_cent(v, u, ssz);
    }
    return u;
}

int DnC(int u)
{
    get_sz(u, -1);
    int cent = get_cent(u, -1, sz[u]);
    erased[cent] = true;

    int mn = 18;
    for(auto v : graph[cent]) {
        if(erased[v]) continue;
        mn = min(mn, DnC(v));
    }

    return ans[cent] = mn - 1;
}

int main()
{
    cin >> N;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int res = DnC(1);
    if(res < 1) {
        cout << "-1";
        return 0;
    }
    for(int i = 1; i <= N; i++) {
        cout << ans[i] << "\n";
    }
}