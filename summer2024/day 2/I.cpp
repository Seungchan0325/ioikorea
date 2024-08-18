#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 100005;

ll N, D, T[MAXN], V[MAXN];

ll DnC(ll lo, ll hi, ll l, ll r)
{
    if(hi < lo) return 0;
    ll m = (lo + hi) / 2;
    ll opt = 0;
    ll opt_idx = 0;
    for(ll i = max(l, m); i <= min(r, m+D); i++) {
        if(V[m] + T[i] * (i - m) > opt) {
            opt = V[m] + T[i] * (i - m);
            opt_idx = i;
        }
    }
    return max({opt, DnC(lo, m-1, l, opt_idx), DnC(m+1, hi, opt_idx, r)});
}

int main()
{
    cin >> N >> D;
    for(int i = 1; i <= N; i++) cin >> T[i];
    for(int i = 1; i <= N; i++) cin >> V[i];
    ll result = DnC(1, N, 1, N);
    cout << result;
}