#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXL = 3030;
const ll MOD = 1e9 + 7;

ll L, n, m, a[MAXL], b[MAXL], nCr[MAXL][MAXL], cache[MAXL][3], linked[MAXL], linked1[MAXL];

ll dp(ll N, ll d)
{
    assert((N+d-1)%2 == 0);
    ll n = (N+d-1) / 2;
    ll m = N - n;
    if(n == 0 && m == 0) return 1;
    if(n == 0 && m == 1) return 1;
    if(n == 1 && m == 0) return 1;
    if(n == 1 && m == 0) return 1;
    if(n == 0 && m == 1) return 1;
    if(n == 0 && m == 0) return 1;
    if(n == 1 && m == 1) return 1;
    if(n == 1 && m == 2) return 2;
    assert(0 <= d && d <= 2);
    assert(abs(n-m) <= 1);
    ll& ret = cache[N][d];
    if(ret != -1) return ret;

    ll c1 = 0, c2 = 0;
    if(d == 0) c2 = 1;
    ret = 0;
    for(int i = 0; i < n; i++) {
        ll cand = dp(c1+c2, c1-c2+1) * dp(N-c1-c2-1, (n-c1-1)-(m-c2)+1) % MOD;
        cand = cand * nCr[N-1][c1+c2] % MOD;
        ret = (ret + cand) % MOD;
        c1++;
        c2++;
    }

    return ret;
}

int main()
{
    cin >> L;
    cin >> n;
    for(ll i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    for(ll i = 1; i <= m; i++) cin >> b[i];

    nCr[0][0] = 1;
    for(ll i = 1; i < MAXL; i++) {
        nCr[i][0] = nCr[i][i] = 1;
        for(ll j = 1; j < i; j++) {
            nCr[i][j] = (nCr[i-1][j] + nCr[i-1][j-1]) % MOD;
        }
    }

    ll idx = 1;
    for(ll i = 1; i <= n; i++) {
        if(a[i] == 2) {
            linked[idx] = 1;
            idx++;
        }
        idx++;
    }

    idx = 1;
    for(ll i = 1; i <= m; i++) {
        if(b[i] == 2) {
            linked1[idx] = 1;
            idx++;
        }
        idx++;
    }

    memset(cache, -1, sizeof(cache));

    ll ans = 1;
    ll acc = 0;
    ll c1 = 0, c2 = 0;
    for(ll i = 1; i <= L; i++) {
        if(linked[i] && !linked1[i]) c2++;
        else if(!linked[i] && linked1[i]) c1++;
        else {
            assert(abs(c1-c2) <= 1);
            ans = ans * dp(c1+c2, c1-c2+1) % MOD * nCr[c1+c2+acc][acc] % MOD;
            acc += c1+c2;
            c1 = c2 = 0;
        }
    }
    cout << acc << " " << ans;
}