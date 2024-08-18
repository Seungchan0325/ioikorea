#include <bits/stdc++.h>

using namespace std;

#define all(v) v.begin(), v.end()

const int MAXN = 100005;
const int MOD = 99999999;

int N, Q, C[MAXN];
vector<int> tree[4*MAXN];

void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx].push_back(C[s]);
        return;
    }

    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    tree[idx].resize(tree[2*idx].size()+tree[2*idx+1].size());
    merge(all(tree[2*idx]), all(tree[2*idx+1]), tree[idx].begin());
}

int query(int l, int r, int t, int s = 1, int e = N, int idx = 1)
{
    if(r < s || e < l) return 0;

    if(l <= s && e <= r) {
        return upper_bound(all(tree[idx]), t) - tree[idx].begin();
    }

    int m = (s + e) / 2;
    return query(l, r, t, s, m, 2*idx) + query(l, r, t, m+1, e, 2*idx+1);
}

int main()
{
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) cin >> C[i];
    init();
    int R = 0;
    int lst = 0;
    for(int i = 1; i <= Q; i++) {
        int s, e, h;
        cin >> s >> e >> h;
        R = ((long long)lst * i % MOD + h) % MOD;
        lst = query(s, e, R);
        cout << lst << "\n";
    }
}