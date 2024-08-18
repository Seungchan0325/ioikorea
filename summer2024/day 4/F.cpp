#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;
const ll MAXS = 1e6 + 5;

struct T {
    ll sum;
};

ll N, lazy[4*MAXS];
T tree[4*MAXS];

T merge(T a, T b)
{
    return T{a.sum + b.sum};
}

void propagate(ll s, ll e, ll idx)
{
    if(lazy[idx]) {
        tree[idx].sum = (e - s + 1) * lazy[idx];
        if(s != e) {
            lazy[2*idx] = lazy[idx];
            lazy[2*idx+1] = lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(ll l, ll r, ll v, ll s = 1, ll e = MAXS, ll idx = 1)
{
    propagate(s, e, idx);
    if(r < s || e < l) return;

    if(l <= s && e <= r) {
        lazy[idx] = v;
        propagate(s, e, idx);
        return;
    }

    ll m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

ll query(ll x, ll s = 1, ll e = MAXS, ll idx = 1)
{
    propagate(s, e, idx);
    if(e < x || x < s) return 0;

    if(s == e) return tree[idx].sum;

    ll m = (s + e) / 2;
    return query(x, s, m, 2*idx) + query(x, m+1, e, 2*idx+1);
}

int main()
{
    cin >> N;
    vector<tuple<ll, ll, ll>> v(N);
    for(auto& [x, y, z] : v) cin >> x >> y >> z;

    vector<vector<pair<ll, ll>>> updates(MAXS);
    for(auto [x, y, z] : v) {
        updates[x].emplace_back(y, z);
    }

    ll sum = 0;
    for(ll i = MAXS-1; i >= 1; i--) {
        for(auto [y, z] : updates[i]) {
            ll lo = 0, hi = MAXS;
            while(lo + 1 < hi) {
                ll mid = (lo + hi) / 2;
                if(query(mid) < z) hi = mid;
                else lo = mid;
            }
            if(y < hi) continue;
            update(hi, y, z);
        }
        sum += tree[1].sum;
    }

    cout << sum;
}