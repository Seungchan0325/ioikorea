#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;

struct T {
    ll mx;
};

int N, Q;
T tree[4*MAXN];

T merge(T a, T b)
{
    T ret;
    ret.mx = max(a.mx, b.mx);
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

struct Qt {
    int l, r, idx;
    bool operator < (const Qt& rhs) const {
        int l1 = l;
        int r1 = r;
        int l2 = rhs.l;
        int r2 = rhs.r;
        if(l1 == l2 && r1 == r2) return false;
        if(r1 == r2) return l1 > l2;
        if(l1 == l2) return r1 < r2;

        if(l1 > l2) {
            if(r2 < l1) return query(l1, r1).mx < query(l2, r2).mx;
            if(r1 < r2) return true;
            return query(r2+1, r1).mx < query(l2, l1-1).mx;
        } else if(l1 < l2) {
            if(r1 < l2) return query(l1, r1).mx < query(l2, r2).mx;
            if(r1 > r2) return false;
            return query(l1, l2-1).mx < query(r1+1, r2).mx;
        }
    }
};

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        int b;
        cin >> b;
        update(i, {b});
    }

    cin >> Q;
    vector<Qt> v(Q);
    for(int i = 0; i < Q; i++) {
        cin >> v[i].l >> v[i].r;
        v[i].idx = i;
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < Q; i++) {
        cout << v[i].idx + 1 << " ";
    }
}