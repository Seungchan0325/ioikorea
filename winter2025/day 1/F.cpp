#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct fenwick {
    vector<ll> v, tree;
    void init() {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        tree.resize(v.size()+1);
    }
    void update(ll x, ll delta) {
        ll p = upper_bound(v.begin(), v.end(), x) - v.begin();
        p = min(p, (ll)v.size());
        while(p <= v.size()) {
            tree[p] += delta;
            p += p&-p;
        }
    }
    ll query(ll x) {
        if(x < v[0]) return 0;
        ll ret = 0;
        ll p = upper_bound(v.begin(), v.end(), x) - v.begin();
        p = min(p, (ll)v.size());

        while(p > 0) {
            ret += tree[p];
            p -= p&-p;
        }
        return ret;
    }
};

struct T {
    fenwick tree;
    vector<pair<ll, ll>> v;
};

const ll MAXN = 100050;

ll N, Q;
T tree[4*MAXN];
vector<ll> xs;
vector<vector<pair<ll, ll>>> ys;

void init(ll s = 0, ll e = xs.size()-1, ll idx = 1)
{
    if(s == e) {
        tree[idx].v = ys[s];
        for(auto [y, c] : ys[s]) {
            tree[idx].tree.v.push_back(y);
        }
        tree[idx].tree.init();
        for(auto [y, c] : ys[s]) {
            tree[idx].tree.update(y, c);
        }
        return;
    }
    ll m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    tree[idx].v = tree[2*idx].v;
    tree[idx].v.insert(tree[idx].v.end(), tree[2*idx+1].v.begin(), tree[2*idx+1].v.end());
    for(auto [y, c] : tree[idx].v) {
        tree[idx].tree.v.push_back(y);
    }
    tree[idx].tree.init();
    for(auto [y, c] : tree[idx].v) {
        tree[idx].tree.update(y, c);
    }
}

ll query(ll l, ll r, ll x, ll y, ll s = 0, ll e = xs.size()-1, ll idx = 1)
{
    if(r < s || e < l) return 0;

    if(l <= s && e <= r) {
        return tree[idx].tree.query(y) - tree[idx].tree.query(x-1);
    }

    ll m = (s + e) / 2;
    return query(l, r, x, y, s, m, 2*idx) + query(l, r, x, y, m+1, e, 2*idx+1);
}

const ll MOD = 1e9;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> Q;
    vector<tuple<ll, ll, ll>> v(N);
    for(auto& [x, y, c] : v) {
        cin >> x >> y >> c;
        xs.push_back(x);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.resize(xs.size());
    for(auto [x, y, c] : v) {
        ll idx = lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        ys[idx].emplace_back(y, c);
    }
    init();
    ll prv = 0;
    while(Q--) {
        ll _a, _b, _c, _d;
        cin >> _a >> _b >> _c >> _d;
        _a = (_a ^ prv) % MOD + 1;
        _b = (_b ^ prv) % MOD + 1;
        _c = (_c ^ prv) % MOD + 1;
        _d = (_d ^ prv) % MOD + 1;
        ll a = min(_a, _b);
        ll b = max(_a, _b);
        ll c = min(_c, _d);
        ll d = max(_c, _d);
        a = lower_bound(xs.begin(), xs.end(), a) - xs.begin();
        b = upper_bound(xs.begin(), xs.end(), b) - xs.begin() - 1;
        ll result = query(a, b, c, d);
        cout << result << "\n";
        prv = result;
    }
}