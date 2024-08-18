#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1005;

ll n, m, d, a[MAXN][MAXN], DP[MAXN][MAXN], b[MAXN][MAXN];

int main()
{
    cin >> n >> m >> d;

    for(ll i = 1; i <= n; i++) {
        for(ll j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    DP[1][1] = d-1;
    for(ll i = 1; i <= n; i++) {
        for(ll j = 1; j <= m; j++) {
            b[i][j] = (a[i][j] + DP[i][j]) % 2;
            DP[i+1][j] += (DP[i][j] + 1 - a[i][j]) / 2;
            DP[i][j+1] += (DP[i][j] + a[i][j]) / 2;
        }
    }

    ll i, j;
    i = j = 1;
    while(i != n+1 && j != m+1) {
        i = i+1-b[i][j];
        j = j+b[i][j];
    }
    cout << i << " " << j;
}