#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXA = 8010;
const int MAXN = 200005;
const ll MOD = 1e9 + 7;

int N, A[MAXN], B[MAXN];
ll DP[MAXA][MAXA], fac[MAXA], inv[MAXA];

ll pw(ll x, ll n)
{
    if(n == 0) return 1;
    if(n&1) return pw(x, n-1) * x % MOD;
    ll half = pw(x, n/2);
    return half * half % MOD;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i] >> B[i];
        DP[2005-A[i]][2005-B[i]]++;
    }

    fac[0] = 1;
    for(int i = 1; i < MAXA; i++) {
        fac[i] = fac[i-1] * i % MOD;
    }

    inv[MAXA-1] = pw(fac[MAXA-1], MOD - 2);
    for(int i = MAXA-2; i >= 0; i--) {
        inv[i] = inv[i+1] * (i+1) % MOD;
    }

    for(int i = 1; i < MAXA; i++) {
        for(int j = 1; j < MAXA; j++) {
            DP[i][j] = (DP[i][j] + DP[i-1][j] + DP[i][j-1]) % MOD;
        }
    }

    ll ans = 0;
    for(int i = 1; i <= N; i++) {
        ans = (ans + DP[A[i]+2005][B[i]+2005]) % MOD;
        ll nCr = fac[A[i]+A[i]+B[i]+B[i]] * inv[A[i]+A[i]] % MOD * inv[B[i]+B[i]] % MOD;
        ans = (ans - nCr + MOD) % MOD;
    }

    ans = ans * pw(2, MOD-2) % MOD;

    cout << ans;
}