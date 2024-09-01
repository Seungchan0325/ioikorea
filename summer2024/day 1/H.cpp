#include <bits/stdc++.h>

using namespace std;

const int MAXN = 205;
const int MOD = 998244353;

using ll = long long;

bool visited[MAXN][MAXN];
ll N, X[MAXN], Y[MAXN];

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
    for(int i = 1; i <= N; i++) cin >> X[i] >> Y[i];
    
    ll ans = (pw(2, N) - 1 - N + MOD) % MOD;
    for(int i = 1; i <= N; i++) {
        for(int j = i+1; j <= N; j++) {
            if(visited[i][j]) continue;
            int cnt = 0;
            vector<int> v;
            for(int k = 1; k <= N; k++) {
                if(Y[k] * (X[i] - X[j]) == (Y[i] - Y[j]) * (X[k] - X[i]) + (X[i] - X[j]) * Y[i]) {
                    v.push_back(k);
                    cnt++;
                }
            }

            for(auto n : v) for(auto m : v) visited[n][m] = true;

            ans = (ans - (pw(2, cnt) - 1 - cnt) % MOD + MOD) % MOD;
        }
    }
    cout << ans;
}