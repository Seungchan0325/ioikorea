#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 20005;

ll N, A[MAXN], B[MAXN], C[MAXN];

ll cnt(ll L)
{
    ll sum = 0;
    for(int i = 1; i <= N; i++) {
        if(L >= A[i]) sum += (min(L, C[i]) - A[i]) / B[i] + 1;
    }
    return sum;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i] >> C[i] >> B[i];

    ll lo = 0;
    ll hi = 3e9 + 100;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(~cnt(mid)&1) lo = mid;
        else hi = mid;
    }

    if(hi > 3e9) cout << "NOTHING";
    else {
        cout << hi << " " << cnt(hi) - cnt(hi-1);
    }
}