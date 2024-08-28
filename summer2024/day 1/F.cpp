#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 250005;

int N, P, C[MAXN];
ll DP[MAXN];
vector<int> graph[MAXN];
vector<ll> tree[MAXN];

void update(int x, ll v, vector<ll>& t, int s, int e, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        t[idx] = v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, t, s, m, 2*idx);
    update(x, v, t, m+1, e, 2*idx+1);
    t[idx] = t[2*idx] * t[2*idx+1] % P;
}

ll query(int l, int r, vector<ll>& t, int s, int e, int idx = 1)
{
    if(r < s || e < l) return 1;
    if(l <= s && e <= r) return t[idx];

    int m = (s + e) / 2;
    return query(l, r, t, s, m, 2*idx) * query(l, r, t, m+1, e, 2*idx+1) % P;
}

void dfs(int u, int p)
{
    vector<ll>& t = tree[u];
    int n = graph[u].size();

    DP[u] = 1;
    t.resize(4*n, 1);
    for(int i = 0; i < n; i++) {
        int v = graph[u][i];
        if(v == p) continue;
        dfs(v, u);
        DP[u] *= DP[v];
        DP[u] %= P;
        update(i, DP[v], t, 0, n-1);
    }
    DP[u] = (DP[u] + 1) % P;
}

void redfs(int u, int p, ll parDP)
{
    vector<ll>& t = tree[u];
    int n = graph[u].size();

    C[u] = query(0, n-1, t, 0, n-1) * parDP % P;

    for(int i = 0; i < n; i++) {
        int v = graph[u][i];
        if(v == p) continue;
        ll nparDP = parDP;
        nparDP *= query(0, i-1, t, 0, n-1) * query(i+1, n-1, t, 0, n-1) % P;
        nparDP %= P;

        nparDP = (nparDP+1) % P;

        redfs(v, u, nparDP);
    }
}

int main()
{
    cin >> N >> P;
    for(int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1, -1);
    redfs(1, -1, 1);

    for(int i = 1; i <= N; i++) {
        cout << C[i] << "\n";
    }
}