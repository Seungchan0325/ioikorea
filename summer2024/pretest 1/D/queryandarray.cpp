#include "queryandarray.h"
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

bool chk[MAXN];
int N, tree[4*MAXN], lazy[4*MAXN], mxL[MAXN], mnR[MAXN];

void propagate(int s, int e, int idx)
{
    if(lazy[idx] != -1) {
        tree[idx] = lazy[idx];
        if(s != e) {
            lazy[2*idx+1] = lazy[2*idx] = lazy[idx];
        }
        lazy[idx] = -1;
    }
}

void update(int l, int r, int v, int s = 0, int e = N-1, int idx = 1)
{
    propagate(s, e, idx);
    if(r < s || e < l) return;

    if(l <= s && e <= r) {
        lazy[idx] = v;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = min(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 0, int e = N-1, int idx = 1)
{
    propagate(s, e, idx);
    if(r < s || e < l) return 1e9;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return min(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

std::vector<int> findarray(int _N, std::vector<int> L, std::vector<int> R, std::vector<int> A) {
    N = _N;

    for(int i = 0; i < N; i++) mnR[i] = 1e9;

    vector<tuple<int, int, int>> q;
    for(int i = 0; i < L.size(); i++) {
        q.emplace_back(A[i], L[i], R[i]);
        mnR[A[i]] = min(mnR[A[i]], R[i]);
        mxL[A[i]] = max(mxL[A[i]], L[i]);
    }
    sort(q.begin(), q.end());

    for(int i = 0; i < N; i++) {
        if(mxL[i] > mnR[i]) return vector<int>(N, -1);
    }

    for(auto [a, l, r] : q) update(l, r, a);

    priority_queue<pair<int, int>> pq;
    vector<int> ans(N);
    for(int i = 0; i < N; i++) {
        int mn = query(i, i);
        if(mxL[mn] <= i && i <= mnR[mn] && !chk[mn]) {
            ans[i] = mn;
            chk[mn] = true;
        } else { 
            pq.emplace(mn, i);
        }
    }
    
    int lst = N-1;
    while(pq.size()) {
        while(lst > 0 && chk[lst]) lst--;
        auto [val, idx] = pq.top(); pq.pop();
        ans[idx] = lst;
        chk[lst] = true;
    }

    for(int i = 0; i < N; i++) {
        update(i, i, ans[i]);
    }

    for(auto [a, l, r] : q) {
        if(query(l, r) != a) return vector<int>(N, -1);
    }
    return ans;
}
