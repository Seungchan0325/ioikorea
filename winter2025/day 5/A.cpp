#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 17;

ll N, cache[1<<MAXN];
ll g[MAXN][MAXN];

ll dp(ll taken)
{
    if(taken == (1<<N)-1) return 0;

    ll& ret = cache[taken];
    if(ret != -1) return ret;
    
    ret = -1e18;
    for(ll i = 0; i < N; i++) {
        if(taken&(1<<i)) continue;
        for(ll j = i+1; j < N; j++) {
            if(taken&(1<<j)) continue;
            ret = max(ret, dp(taken|(1<<i)|(1<<j)) + g[i][j]);
        }
    }

    return ret;
}

int main()
{
    cin >> N;
    for(ll i = 0; i < N*(N-1)/2; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        g[u][v] = g[v][u] = w;
    }

    memset(cache, -1, sizeof(cache));
    ll result = dp(0);
    cout << result;
}