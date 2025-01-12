#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;

struct T {
    ll count;
    ll area;
    ll width;
};

ll N, lazy[4*MAXN], sz;
T tree[4*MAXN];
vector<ll> ys, xs;

void merge(T& t, T a, T b)
{
    t.width = a.width + b.width;
    if(t.count == 0) {
        t.area = a.area + b.area;
    }
}

void build(ll s = 1, ll e = sz, ll idx = 1)
{
    if(s == e) {
        tree[idx].width = xs[s] - xs[s-1];
        return;
    }

    ll m = (s + e) / 2;
    build(s, m, 2*idx);
    build(m+1, e, 2*idx+1);
    merge(tree[idx], tree[2*idx], tree[2*idx+1]);
}

void update(ll l, ll r, ll v, ll s = 1, ll e = sz, ll idx = 1)
{
    if(r < s || e < l) return;

    if(l <= s && e <= r) {
        tree[idx].count += v;
        if(tree[idx].count) tree[idx].area = tree[idx].width;
        else if(s != e) tree[idx].area = tree[2*idx].area + tree[2*idx+1].area;
        else tree[idx].area = 0;
        return;
    }

    ll m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    merge(tree[idx], tree[2*idx], tree[2*idx+1]);
}

int main()
{
    cin >> N;
    vector<tuple<ll, ll, ll, ll>> rect(N);
    for(auto& [x1, x2, y1, y2] : rect) {
        cin >> x1 >> x2 >> y1 >> y2;
        xs.push_back(x1);
        xs.push_back(x2);
        ys.push_back(y1);
        ys.push_back(y2);
    }

    xs.push_back(-1);

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    sz = xs.size() - 1;
    build();

    vector<vector<tuple<ll, ll, ll>>> updates(ys.size() + 1);
    for(auto [x1, x2, y1, y2] : rect) {
        ll l = upper_bound(xs.begin(), xs.end(), x1) - xs.begin();
        ll r = lower_bound(xs.begin(), xs.end(), x2) - xs.begin();
        ll s = lower_bound(ys.begin(), ys.end(), y1) - ys.begin();
        ll e = lower_bound(ys.begin(), ys.end(), y2) - ys.begin();
        updates[s].emplace_back(l, r, 1);
        updates[e].emplace_back(l, r, -1);
    }

    ll ans = 0;
    for(auto [l, r, w] : updates[0]) update(l, r, w);
    for(ll i = 1; i < ys.size(); i++) {
        ans += tree[1].area * (ys[i] - ys[i-1]);
        for(auto [l, r, w] : updates[i])
            update(l, r, w);
    }
    cout << ans;
}