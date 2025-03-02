#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 20;
const ll INF = 1e18;

ll N, w[MAXN][MAXN], cache[1<<MAXN][MAXN];

ll dp(ll taken, ll now)
{
    if(taken == (1<<N)-1) return w[now][0] == 0 ? INF : w[now][0];
    ll& ret = cache[taken][now];
    if(ret != -1) return ret;

    ret = INF;
    for(ll nxt = 0; nxt < N; nxt++) {
        if((taken&(1<<nxt)) || w[now][nxt] == 0) continue;
        ret = min(ret, dp(taken|(1<<nxt), nxt) + w[now][nxt]);
    }
    return ret;
}

int main()
{
    cin >> N;
    for(ll i = 0; i < N; i++) {
        for(ll j = 0; j < N; j++) {
            cin >> w[i][j];
        }
    }
    memset(cache, -1, sizeof(cache));
    ll result = dp(1, 0);
    cout << result;
}