#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, M, lazy[4*MAXN], tree[4*MAXN];

void propagate(int s, int e, int idx)
{
    if(lazy[idx]%2) {
        tree[idx] = (e - s + 1) - tree[idx];
        if(s != e) {
            lazy[2*idx]++;
            lazy[2*idx+1]++;
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(r < s || e < l) return;

    if(l <= s && e <= r) {
        lazy[idx]++;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) / 2;
    update(l, r, s, m, 2*idx);
    update(l, r, m+1, e, 2*idx+1);
    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

int query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(r < s || e < l) return 0;
    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    return query(l, r, s, m, 2*idx) + query(l, r, m+1, e, 2*idx+1);
}

int main()
{
    cin >> N >> M;
    while(M--) {
        int op, s, t;
        cin >> op >> s >> t;
        if(op == 0) {
            update(s, t);
        } else {
            int result = query(s, t);
            cout << result << "\n";
        }
    }
}