#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using pii = pair<ll, ll>;

const ll INF = LLONG_MAX;

ll N;
vector<pii> v;

pair<ll, vector<pii>> DnC(ll lo, ll hi)
{
    if(lo == hi) return make_pair(INF, vector<pii>{v[lo]});

    ll m = (lo + hi) / 2;
    auto [min1, v2] = DnC(lo, m);
    auto [min2, v3] = DnC(m+1, hi);

    ll mn = min(min1, min2);
    vector<pii> v1(v2.size() + v3.size());
    merge(v2.begin(), v2.end(), v3.begin(), v3.end(), v1.begin(), [](pii a, pii b) {
        return a.second < b.second;
    });

    vector<pii> p;
    ll mx = v[m].first;
    for(auto [x, y] : v1) {
        if((x-mx)*(x-mx) < mn) {
            p.emplace_back(x, y);
        }
    }

    for(ll i = 0; i < p.size(); i++) {
        for(ll j = i+1; j < p.size(); j++) {
            if((p[i].second - p[j].second)*(p[i].second - p[j].second) > mn) break;
            mn = min(mn, (p[i].first - p[j].first)*(p[i].first - p[j].first) + (p[i].second - p[j].second)*(p[i].second - p[j].second));
        }
    }

    return make_pair(mn, v1);
}

int main()
{
    cin >> N;
    v.resize(N);
    for(auto& [x, y] : v) cin >> x >> y;
    sort(v.begin(), v.end());
    auto [mn, v1] = DnC(0, N-1);
    cout << mn << "\n";
}