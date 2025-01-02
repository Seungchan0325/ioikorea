#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;
const ll MOD = 1e9 + 7;

ll N, M, D[MAXN], C[MAXN], S[MAXN];
vector<int> graph[MAXN];
vector<pair<int, int>> edges;

ll mypow(ll x, ll n)
{
    if(n == 0) return 1;
    if(n&1) return mypow(x, n-1) * x % MOD;
    ll half = mypow(x, n/2);
    return half * half % MOD;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        cin >> D[i];
        C[D[i]]++;
    }
    for(int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;
        if(D[u] > D[v]) swap(u, v);
        edges.emplace_back(u, v);
        if(D[u] != D[v]) graph[v].push_back(u);
        else S[D[u]]++;
    }

    for(int i = 2; i <= N; i++) {
        if(D[i] == 0) {
            cout << "0";
            return 0;
        }
    }

    for(auto [u, v] : edges) {
        if(D[v] - D[u] > 1) {
            cout << "0";
            return 0;
        }
    }

    ll ans = 1;
    for(int i = 2; i <= N; i++) {
        if(C[D[i]-1] == 0) {
            cout << "0";
            return 0;
        }
        ll cnt = C[D[i]-1] - (ll)graph[i].size();
        if(cnt != 0) {
            if(graph[i].empty()) ans *= mypow(2, cnt) - 1;
            else ans *= mypow(2, cnt);
        }
        ans %= MOD;
    }
    for(int i = 1; i < N; i++) {
        ll cnt = (C[i] * (C[i] - 1) / 2 - S[i]) % MOD;
        ans *= mypow(2, cnt);
        ans %= MOD;
    }

    cout << ans;
}