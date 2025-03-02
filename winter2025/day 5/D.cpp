#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100;

bool erased[MAXN];
ll N, w[MAXN][MAXN], root[MAXN], sz[MAXN];
vector<pair<ll, ll>> graph[MAXN];
vector<pair<ll, ll>> mst;
ll ans;

ll find(ll x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(ll x, ll y)
{
    x = find(x);
    y = find(y);
    root[y] = x;
}

void dfs(ll u, ll p)
{
    sz[u] = 1;
    for(auto [v, w] : graph[u]) {
        if(v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
    for(auto [v, w] : graph[u]) {
        if(v == p) continue;
        ans += (ll)2 * min(sz[v], N-sz[v]) * w;
    }
}

ll get_cent(ll u, ll p)
{
    for(auto [v, w] : graph[u]) {
        if(v == p || erased[v]) continue;
        if(2*sz[v] > N) return get_cent(v, u);
    }
    return u;
}

vector<int> get_order(ll u, ll p)
{
    vector<int> s;
    queue<pair<ll, ll>> q;
    q.emplace(u, p);
    while(q.size()) {
        auto [now, par] = q.front(); q.pop();
        s.push_back(now);
        for(auto [nxt, w] : graph[now]) {
            if(nxt == par) continue;
            q.emplace(nxt, now);
        }
    }
    return s;
}

int main()
{
    cin >> N;
    vector<tuple<ll, ll, ll>> edges;
    for(ll i = 0; i < N; i++) {
        for(ll j = 0; j < N; j++) {
            cin >> w[i][j];
            edges.emplace_back(w[i][j], i, j);
        }
    }

    sort(edges.begin(), edges.end());
    iota(root, root + N, 0);
    for(auto [w, u, v] : edges) {
        if(find(u) != find(v)) {
            merge(u, v);
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
            // mst.emplace_back(u, v);
        }
    }

    dfs(0, -1);
    cout << ans << "\n";

    ll cent = get_cent(0, -1);
    vector<vector<int>> ss;
    priority_queue<pair<int, int>> pq;
    for(auto [nxt, w] : graph[cent]) {
        ss.push_back(get_order(nxt, cent));
        pq.emplace(ss.back().size(), ss.size()-1);
    }
    vector<ll> order;
    order.push_back(cent);
    while(pq.size()) {
        assert(pq.size());
        auto [sz, idx] = pq.top(); pq.pop();
        order.push_back(ss[idx].back()); ss[idx].pop_back();

        if(pq.empty()) {
            if(sz-1) pq.emplace(sz-1, idx);
            continue;
        }

        auto [sz2, idx2] = pq.top(); pq.pop();
        order.push_back(ss[idx2].back()); ss[idx2].pop_back();
        if(sz-1) pq.emplace(sz-1, idx);
        if(sz2-1) pq.emplace(sz2-1, idx2);
    }
    order.push_back(cent);
    for(auto i : order) cout << i+1 << " ";
}