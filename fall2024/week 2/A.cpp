#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int N;

bool chk(ll w, vector<ll> a)
{
    a[0] += w;
    for(int i = 1; i < N; i++) {
        ll d = a[i-1] - a[i];
        if(d > 1) {
            a[i-1] -= d/2;
            a[i] += d/2;
        }
        if(a[i-1] < a[i]) return false;
    }

    return true;
}

int main()
{
    cin >> N;
    vector<ll> a(N);
    for(ll& i : a) cin >> i;

    ll lo = -1;
    ll hi = 1e18;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(chk(mid, a)) hi = mid;
        else lo = mid;
    }

    cout << hi;
}