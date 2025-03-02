#include <bits/stdc++.h>
#include <vector>
#include "grader.cpp" 
#include "craft.h"

using namespace std;

int g[64][64], sz[64];

void init() {
    return;
}

void dfs(int u, int p)
{
    sz[u] = 1;
    for(int v = 0; v < 64; v++) {
        if(v != p && g[u][v]) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}

int classify(std::vector<int> parent) {
    memset(g, 0, sizeof(g));
    memset(sz, 0, sizeof(sz));
    int N = parent.size();
    for(int i = 0; i < N; i++) {
        if(i != 0) {
            g[i][parent[i]]++;
            g[parent[i]][i]++;
        }
    }
    dfs(0, -1);
    sort(sz, sz + N);

    int cnt = 0;
    for(int i = 0; i < N; i++) {
        if(sz[i] <= 2) cnt++;
    }

    if(cnt >= 38) return 1;
    return 2;
}