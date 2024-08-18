#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<ll, ll>;

const ll INF = 2e18;

ll ans;
ll N, M;
vector<pii> A, B;

void DnC(ll l, ll r, ll optl, ll optr)
{
    if(l > r) return;

    ll m = (l + r) / 2;
    ll opt = -INF;
    ll opt_idx = optl;
    for(ll i = optl; i <= optr; i++) {
        if(B[m].first <= A[i].first && B[m].second <= A[i].second) continue;
        if((B[m].first - A[i].first) * (B[m].second - A[i].second) > opt) {
            opt = (B[m].first - A[i].first) * (B[m].second - A[i].second);
            opt_idx = i;
        }
    }
    ans = max(ans, opt);
    DnC(l, m-1, optl, opt_idx);
    DnC(m+1, r, opt_idx, optr);
}

int main()
{
    cin >> N >> M;
    A.resize(N);
    for(auto& [x, y] : A) cin >> x >> y;
    B.resize(M);
    for(auto& [x, y] : B) cin >> x >> y;


    // sort(A.begin(), A.end(), [](pii a, pii b) {
    //     if(a.second == b.second) return a.first < b.first;
    //     return a.second < b.second;
    // });

    sort(A.begin(), A.end());

    vector<pii> AA;
    // ll mn = INF;
    for(auto [x, y] : A) {
        // if(x >= mn) continue;
        // AA.emplace_back(x, y);
        // mn = x;
        if(!AA.empty() && AA.back().second <= y) continue;
        AA.emplace_back(x, y);
    }
    A = AA;
    N = A.size();

    // sort(B.begin(), B.end(), [](pii a, pii b) {
    //     if(a.second == b.second) return a.first > b.first;
    //     return a.second > b.second;
    // });
    sort(B.begin(), B.end());

    vector<pii> BB;
    // ll mx = -1;
    for(auto [x, y] : B) {
        // if(x <= mx) continue;
        // BB.emplace_back(x, y);
        // mx = x;
        while(!BB.empty() && BB.back().second <= y) BB.pop_back();
        BB.emplace_back(x, y);
    }
    B = BB;
    M = B.size();

    DnC(0, M-1, 0, N-1);
    cout << ans;
}