#include <bits/stdc++.h>

using  namespace std;

#define int long long

const int MAXQ = 300505;
const int MAXT = 1050505;

int Q, t[MAXQ], d[MAXQ], tree[4*MAXT], lazy[4*MAXT], ttree[4*MAXT];

void upd(int x, int v, int s = 1, int e = MAXT, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        ttree[idx] += v;
        return;
    }

    int m = (s + e) / 2;
    upd(x, v, s, m, 2*idx);
    upd(x, v, m+1, e, 2*idx+1);
    ttree[idx] = ttree[2*idx] + ttree[2*idx+1];
}


int qry(int l, int r, int s = 1, int e = MAXT, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return ttree[idx];
    int m = (s + e) / 2;
    return qry(l, r, s, m, 2*idx) + qry(l, r, m+1, e, 2*idx+1);
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx] += lazy[idx];
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int v, int s = 1, int e = MAXT, int idx = 1)
{
    propagate(s, e, idx);
    if(r < s || e < l) return;

    if(l <= s && e <= r) {
        lazy[idx] += v;
        propagate(s, e, idx);
        return;
    }

    int m = (s + e) / 2;
    update(l, r, v, s, m, 2*idx);
    update(l, r, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 1, int e = MAXT, int idx = 1)
{
    propagate(s, e, idx);
    if(r < s || e < l) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> Q;
    for(int i = 0; i <= MAXT; i++) update(i, i, i);
    for(int i = 1; i <= Q; i++) {
        char op;
        cin >> op;
        if(op == '+') {
            cin >> t[i] >> d[i];
            update(0, t[i], d[i]);
            upd(t[i], d[i]);
        } else if(op == '-') {
            int j;
            cin >> j;
            update(0, t[j], -d[j]);
            upd(t[j], -d[j]);
        } else if(op == '?') {
            cin >> t[i];
            int result = query(0, t[i]) - qry(t[i]+1, MAXT) - t[i];
            cout << result << "\n";
        } else {
            assert(0);
        }
    }
}