#include <vector>
#include <bits/stdc++.h>
#include "grader.cpp"
 
using namespace std;
 
const int MAXN = 1010101;

using ll = long long;

ll ans = 0;
bool erased[MAXN];
int sz[MAXN];
vector<int> g[MAXN];

void get_sz(int u, int p)
{
    sz[u] = 1;
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

int get_cent(int n, int u, int p)
{
    for(auto v : g[u]) {
        if(v == p || erased[v]) continue;
        if(sz[v] > n/2) return get_cent(n, v, u);
    }
    return u;
}

pair<int, ll> DnC(int now)
{
    get_sz(now, -1);
    int u = get_cent(sz[now], now, -1);
    erased[u] = true;
    vector<pair<int, ll>> arr;
    ll a = 0;
    for(auto v : g[u]) {
        if(erased[v]) continue;
        auto t = DnC(v);        
        arr.push_back(t);
    }
    sort(arr.begin(), arr.end(), greater<>());
    int ret = 0;
    ll s = 0;
    for(int i = 0; i < min((int)arr.size(), 2); i++) {
        ret += arr[i].first;
        s -= arr[i].second;
    }
    for(auto i : arr) s += i.second;
    a += (ll)ret * (s);
    return {ret + 1, a};
}

long long max_diversity(int N, int M, vector<int> U, vector<int> V) {
    for(int i = 0; i < M; i++) {
        g[U[i]].push_back(V[i]);
        g[V[i]].push_back(U[i]);
    }
    auto [a, b] = DnC(0);
    return (ll)a * (ll)(a-1) / 2 + b;
}
