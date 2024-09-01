// #include <bits/stdc++.h>
#include <iostream>

using namespace std;

using ll = long long;

const int MAXN = 2005;
const int MOD = 1e9 + 7;
const int MAXC = MAXN * MAXN;

int N, K;
ll fac[MAXC], inv[MAXC], DP[MAXN][MAXN];

ll pw(ll x, ll n)
{
    if(n == 0) return 1;
    if(n&1) return pw(x, n-1) * x % MOD;
    ll half = pw(x, n/2);
    return half * half % MOD;
}

ll bino(ll n, ll r)
{
    return fac[n] * inv[r] % MOD * inv[n-r] % MOD;
}

int main()
{
    cin >> N >> K;

    if(K == 1) {
        cout << "1";
        return 0;
    }

    fac[0] = 1;
    for(int i = 1; i < MAXC; i++) {
        fac[i] = fac[i-1] * i % MOD;
    }

    inv[MAXC-1] = pw(fac[MAXC-1], MOD-2);
    for(int i = MAXC - 2; i >= 0; i--) {
        inv[i] = inv[i+1] * (i+1) % MOD;
    }

    DP[0][0] = 1;
    for(int i = 1; i <= N; i++) {
        DP[0][i] = DP[0][i-1] * bino(i*(K-1)-1, K-2) % MOD;
    }
    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j++) {
            DP[i][j] = (DP[i-1][j] + bino(i+j*(K-1)-1, K-2) * DP[i][j-1] % MOD) % MOD;
        }
    }

    for(int j = 0; j <= N; j++) {
        for(int i = 0; i <= N; i++) {
            cout << DP[i][j] << " ";
        }
        cout << "\n";
    }

    cout << fac[N] * DP[N][N] % MOD;
}