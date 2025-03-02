#include "evolution2.h"
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10101;

bool vst[MAXN], erased[MAXN], dummy[MAXN];
int sz[MAXN], lst[MAXN];
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

vector<int> DnC(int now)
{
    get_sz(now, -1);
    int u = get_cent(sz[now], now, -1);
    erased[u] = true;
    vector<vector<int>> others;
    for(auto v : g[u]) {
        if(erased[v]) continue;
        others.push_back(DnC(v));
    }
    int m = others.size();
    vector<int> idx();
}

struct cmp {
    bool operator () (int i, int j)
    {
        return compare(i, j);
    }
};

std::vector<int> recover(int N, std::vector<int> U, std::vector<int> V) {
    for(int i = 0; i < N; i++) {
        vst[i] = false;
        g[i].clear();
    }

    for(int i = 0; i < N-1; i++) {
        g[U[i]].push_back(V[i]);
        g[V[i]].push_back(U[i]);
    }
    
    vector<int> v;
    for(int i = 0; i < N; i++) {
        v.push_back(i);
    }

    stable_sort(v.begin(), v.end(), cmp());
    vector<int> ans(N);
    for(int i = 0; i < N; i++) {
        ans[v[i]] = i;
    }
    // priority_queue<int, vector<int>, cmp> pq;

    // pq.push(0);
    // vst[0] = true;

    // int t = 0;
    // vector<int> ans(N);
    // while(!pq.empty()) {
    //     auto now = pq.top(); pq.pop();
    //     ans[now] = t++;
    //     for(auto nxt : g[now]) {
    //         if(vst[nxt]) continue;
    //         vst[nxt] = true;
    //         pq.push(nxt);
    //     }
    // }

    return ans; 
}
