#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1000005;
const ll MOD = 1e9 + 7;

bool chk[MAXN];
int n, m, a[MAXN], sz[MAXN], deg[MAXN], tree[MAXN];
vector<int> graph[MAXN];

ll pw(ll a, ll x)
{
    if(x == 0) return 1;
    if(x&1) return pw(a, x-1) * a % MOD;
    ll half = pw(a, x/2);
    return half * half % MOD;
}

int dfs(int u)
{
    chk[u] = true;
    sz[u] = 1;
    int ret = tree[u];
    for(auto v : graph[u]) {
        if(chk[v]) {
            continue;
        }
        ret += dfs(v);
        sz[u] += sz[v];
    }
    return ret;
}

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];

        graph[i].push_back(a[i]);
        graph[a[i]].push_back(i);
        deg[i]++;
        deg[a[i]]++;
    }

    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 1) {
            q.emplace(i);
            tree[i] = 0;
        } else tree[i] = 1;
    }

    while(!q.empty()) {
        auto u = q.front(); q.pop();
        for(auto v : graph[u]) {
            if(--deg[v] == 1) {
                q.push(v);
                tree[v] = 0;
            }
        }
    }

    ll ans = 1;
    for(int i = 1; i <= n; i++) {
        if(chk[i]) continue;
        ll cycle = dfs(i);
        ll tmp = (m - 1) * pw(-1, cycle) % MOD + pw(m - 1, cycle);
        if(cycle == 1) tmp = m;
        tmp %= MOD;
        if(cycle == 0) tmp *= pw(m - 1, sz[i] - cycle - 1);
        else tmp *= pw(m - 1, sz[i] - cycle);
        tmp %= MOD;
        ans = (ans * tmp) % MOD;
    }
    cout << ans;
}