#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 500005;

int N, A[MAXN], tree[4*MAXN];

void update(int x, int v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx] += v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

int query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(r < s || e < l) return 0;

    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return query(l, r, s, m, 2*idx) + query(l, r, m+1, e, 2*idx+1);
}

int main()
{
    cin >> N;
    vector<int> vs;
    vector<int> v(N);
    for(int i = 0; i < N; i++) {
        cin >> v[i];
        vs.push_back(v[i]);
    }

    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    ll ans = 0;
    for(auto i : v) {
        int idx = lower_bound(vs.begin(), vs.end(), i) - vs.begin() + 1;
        ans += query(idx, N);
        update(idx, 1);
    }
    cout << ans;
}