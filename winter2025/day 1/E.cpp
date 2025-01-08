#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Rect {
    ll x1, x2, y1, y2;
};

const ll MAXN = 200050;

struct T
{
    ll tag;
    ll sum;
};

const ll INF = 2e9;

ll N;
ll sz[8*MAXN];
T tree[8*MAXN];
vector<ll> xs, ys;

ll Size;

void init(ll s = 0, ll e = Size - 1, ll idx = 1)
{
    if(s == e) {
        sz[idx] = ys[s+1] - ys[s];
        return;
    }

    ll m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    sz[idx] = sz[2*idx] + sz[2*idx+1];
}

void update(ll l, ll r, ll v, ll s = 0, ll e = Size - 1, ll idx = 1)
{
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        if(tree[idx].tag += v) {
            tree[idx].sum = sz[idx];
        } else {
            tree[idx].sum = tree[2*idx].sum + tree[2*idx+1].sum;
        }
        return;
    }

    ll m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    if(tree[idx].tag == 0) tree[idx].sum = tree[2*idx].sum + tree[2*idx+1].sum;
    else tree[idx].sum = sz[idx];
}

int main()
{
    cin >> N;
    vector<Rect> rects(N);
    for(ll i = 0; i < N; i++) {
        cin >> rects[i].x1 >> rects[i].x2 >> rects[i].y1 >> rects[i].y2;
        xs.push_back(rects[i].x1);
        xs.push_back(rects[i].x2);
        ys.push_back(rects[i].y1);
        ys.push_back(rects[i].y2);
    }
    ys.push_back(-INF);
    ys.push_back(INF);
    xs.push_back(-INF);
    xs.push_back(INF);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    vector<vector<tuple<ll, ll, ll>>> upds(xs.size());
    for(ll i = 0; i < N; i++) {
        ll s = lower_bound(xs.begin(), xs.end(), rects[i].x1) - xs.begin();
        ll e = lower_bound(xs.begin(), xs.end(), rects[i].x2) - xs.begin();
        ll top = lower_bound(ys.begin(), ys.end(), rects[i].y1) - ys.begin();
        ll bottom = lower_bound(ys.begin(), ys.end(), rects[i].y2) - ys.begin() - 1;
        upds[s].emplace_back(top, bottom, 1);
        upds[e].emplace_back(top, bottom, -1);
    }


    ll ans = 0;

    Size = ys.size() - 1;
    init();

    for(ll i = 0; i < xs.size(); i++) {
        for(auto [top, bottom, delta] : upds[i])
            update(top, bottom, delta);
        ans += (xs[i+1] - xs[i]) * tree[1].sum;
    }
    
    cout << ans;
}