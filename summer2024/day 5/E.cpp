#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

using ll = long long;

ll N, A[MAXN], cache[MAXN][MAXN];

ll dp(ll i, ll j)
{
    if(j - i + 1 <= 2) return 0;
    ll& ret = cache[i][j];
    if(ret != -1) return ret;
    
    ret = 1e18;
    for(int k = i+1; k < j; k++) {
        ret = min(ret, dp(i, k) + dp(k, j) + A[i] * A[k] * A[j]);
    }
    return ret;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N+1; i++) cin >> A[i];

    memset(cache, -1, sizeof(cache));
    ll ans = dp(1, N+1);
    cout << ans;
}