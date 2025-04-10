#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll compute(ll n)
{
    ll ans = 0;
    for(ll l = 1, r; l <= n; l = r + 1) {
        ll k = n / l;
        r = n / k;
        ans += k * (r - l + 1);
    }
    return ans;
}

int main()
{
    ll t; cin >> t;
    ll lo = 0;
    ll hi = 1080000000000;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(compute(mid) <= t) lo = mid;
        else hi = mid;
    }
    cout << lo;
}