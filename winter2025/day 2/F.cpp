#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 2000050;
const ll X1 = 325;
const ll X2 = 534;
const ll M1 = 1100000009;
const ll M2 = 900000011;

ll N, pw1[MAXN], pw2[MAXN];
vector<ll> H1[MAXN], H2[MAXN];
string A[MAXN];
map<pair<ll, ll>, ll> idx;
vector<ll> graph[MAXN];
ll indeg[MAXN], dp[MAXN];

vector<ll> getPartialMatch(const string& N)
{
    ll m = N.size();
    vector<ll> pi(m, 0);

    ll matched = 0;
    for(ll i = 1; i < m; i++) {
        while(matched > 0 && N[i] != N[matched])
            matched = pi[matched - 1];
        
        if(N[i] == N[matched])
            pi[i] = ++matched;
    }
    return pi;
}

int main()
{
    pw1[0] = 1;
    pw2[0] = 1;
    for(ll i = 1; i < MAXN; i++) {
        pw1[i] = (ll)pw1[i-1] * X1 % M1;
        pw2[i] = (ll)pw2[i-1] * X2 % M2;
    }
    cin >> N;

    for(ll i = 1; i <= N; i++) {
        cin >> A[i];
        ll n = A[i].size();

        H1[i].resize(n);
        H2[i].resize(n);
        H1[i][0] = H2[i][0] = A[i][0];
        for(ll j = 1; j < n; j++) {
            H1[i][j] = ((ll)H1[i][j-1]+(ll)pw1[j]*A[i][j]) % M1;
            H2[i][j] = ((ll)H2[i][j-1]+(ll)pw2[j]*A[i][j]) % M2;
        }

        auto pi = getPartialMatch(A[i]);
        ll matched = n;
        while(matched > 0) {
            if(idx.count({H1[i][matched-1], H2[i][matched-1]})) {
                int j = idx[{H1[i][matched-1], H2[i][matched-1]}];
                graph[i].push_back(j);
                indeg[j]++;
            }
            matched = pi[matched-1];
        }

        idx[{H1[i][n-1], H2[i][n-1]}] = i;
    }
    queue<ll> q;
    for(ll i = 1; i <= N; i++) {
        if(indeg[i] == 0) {
            dp[i] = 1;
            q.push(i);
        }
    }
    ll ans = 0;
    while(!q.empty()) {
        auto u = q.front(); q.pop();
        ans = max(ans, dp[u]);
        for(auto v : graph[u]) {
            if(--indeg[v] == 0) {
                q.push(v);
            }
            dp[v] = max(dp[v], dp[u] + 1);
        }
    }
    cout << ans;
}