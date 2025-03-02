#include <vector>
#include <bits/stdc++.h>
#include "grader.cpp"

using namespace std;

const int MAXN = 5050;
 
using ll = long long;

struct T {
    ll l, r, mx, sum;
};

ll dpl[MAXN], dpr[MAXN], mxl[MAXN], mxr[MAXN], cache[MAXN][MAXN], S[MAXN];
T tree[4*MAXN];
int N;

T merge(T a, T b)
{
    T ret;
    ret.l = max(a.l, a.sum + b.l);
    ret.r = max(b.r, b.sum + a.r);
    ret.mx = max({a.mx, b.mx, a.r + b.l});
    ret.sum = a.sum + b.sum;
    return ret;
}

void update(int x, ll v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx].l = tree[idx].r = tree[idx].mx = tree[idx].sum = v;
        return;
    }
    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(r < s || e < l) return T{(ll)-1e18, (ll)-1e18, (ll)-1e18, (ll)-1e18};
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

vector<pair<int, int>> get_lr(vector<int> A)
{
    int N = A.size();
    ll mx = -1e18, s = 0;
    vector<pair<int, int>> lr;
    int l = 0;
    for(int r = 0; r < N; r++) {
        if(s + A[r] < 0) {
            l = r;
            s = A[r];
        } else {
            s = s + A[r];
        }
        if(s > mx) {
            mx = s;
        }
        if(A[r] > 0) {
            while(lr.size() && lr.back().first == l) lr.pop_back();
            lr.emplace_back(l, r);
        }
    }
    return lr;
}

std::vector<long long> maxsum(
    std::vector<int> A, std::vector<int> B, 
    std::vector<int> L1, std::vector<int> R1, 
    std::vector<int> L2, std::vector<int> R2) {

    N = A.size();

    A.insert(A.begin(), 0);
    B.insert(B.begin(), 0);
    for(auto& i : L1) i++;
    for(auto& i : L2) i++;
    for(auto& i : R1) i++;
    for(auto& i : R2) i++;

    for(int i = 1; i <= N; i++) {
        S[i] = S[i-1] + B[i];
        update(i, B[i]);
    }

    dpl[0] = -1e18;
    mxl[0] = -1e18;
    for(int i = 1; i <= N; i++) {
        dpl[i] = max(dpl[i-1] + A[i], (ll)A[i]);
        mxl[i] = max(dpl[i], mxl[i-1]);
    }
    dpr[N+1] = -1e18;
    mxr[N+1] = -1e18;
    for(int i = N; i >= 1; i--) {
        dpr[i] = max(dpr[i+1] + A[i], (ll)A[i]);
        mxr[i] = max(dpr[i], mxr[i+1]);
    }

    for(int l = 1; l <= N; l++) {
        for(int r = l; r <= N; r++) {
            ll sum = S[r] - S[l-1];
            auto t = query(l, r);
            // ll mx = max({mxl[l-1], mxr[r+1], t.mx, t.l + dpl[l-1], t.r + dpr[r+1]});
            if(mxl[l-1] <= sum && mxr[r+1] <= sum && dpl[l-1] <= 0 && dpr[r+1] <= 0 && t.mx <= sum) {
                cache[l][r] = 1;
            } else {
                cache[l][r] = 0;
            }
        }
    }

    for(int l = 1; l <= N; l++) {
        for(int r = 1; r <= N; r++) {
            cache[l][r] += cache[l-1][r] + cache[l][r-1] - cache[l-1][r-1];
        }
    }

    vector<ll> ans;
    int Q = L1.size();
    for(int q = 0; q < Q; q++) {
        ll cnt = cache[R1[q]][R2[q]] - cache[R1[q]][L2[q]-1] - cache[L1[q]-1][R2[q]] + cache[L1[q]-1][L2[q]-1];
        ans.push_back(cnt);
    }
    return ans;
}