#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 250005;

struct T {
    ll sum, mn;
};

int N, Q;
T tree[4*MAXN];

T merge(T a, T b)
{
    T ret;
    ret.sum = a.sum + b.sum;
    ret.mn = min(a.mn, b.mn);
    return ret;
}

void update(int x, T v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] = v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    if(r <= m) return query(l, r, s, m, 2*idx);
    else if(m+1 <= l) return query(l, r, m+1, e, 2*idx+1);
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        int a;
        cin >> a;
        update(i, {a, a});
    }

    while(Q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i, v;
            cin >> i >> v;
            update(i, {v, v});
        } else if(op == 2) {
            int i, j;
            cin >> i >> j;
            T result = query(i, j);
            cout << result.mn << "\n";
        } else {
            int i, j;
            cin >> i >> j;
            T result = query(i, j);
            cout << result.sum << "\n";
        }
    }
}
