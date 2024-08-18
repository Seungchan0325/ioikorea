#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;
const ll INF = 1e18;

struct T {
    ll v;
    ll idx;
};

ll N, M, K, segsz;
T tree[4*MAXN];

T merge(T a, T b)
{
    if(a.v <= b.v) return {a.v, a.idx};
    return {b.v, b.idx};
}

void update(ll x, T v, ll s = 0, ll e = N-1, ll idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] = v;
        return;
    }

    ll m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(ll l, ll r, ll s = 0, ll e = N-1, ll idx = 1)
{
    if(e < l || r < s) return {INF, -1};
    if(l <= s && e <= r) return tree[idx];
    ll m = (s + e) / 2;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    cin >> N >> M >> K;
    vector<pair<ll, ll>> cpu(N);
    for(auto& [e, p] : cpu) cin >> p >> e;
    vector<pair<ll, ll>> cus(M);
    for(auto& [t, b] : cus) cin >> b >> t;

    sort(cpu.begin(), cpu.end());
    sort(cus.begin(), cus.end(), [](pair<ll, ll>a, pair<ll, ll>b)
    {
        if(a.second == b.second) return a.first < b.first;
        return a.second > b.second;
    });

    for(ll i = 0; i < N; i++) {
        auto [e, p] = cpu[i];
        update(i, {p, i});
    }

    vector<ll> v;
    for(auto [e, p] : cpu) v.push_back(e);
    sort(v.begin(), v.end());

    priority_queue<ll> pq;
    for(auto [t, b] : cus) {
        ll u = lower_bound(v.begin(), v.end(), t) - v.begin();
        auto [val, idx] = query(u, N-1);
        if(val == INF) continue;
        update(idx, T{INF, idx});
        pq.push(b - val);
    }

    ll sum = 0;
    for(ll i = 0; i < K; i++) {
        if(pq.empty() || pq.top() < 0) break;
        sum += pq.top(); pq.pop();
    }
    cout << sum; 
}