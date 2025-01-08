#include <bits/stdc++.h>

using namespace std;

const int SZ = 2000050;

struct T {
    int cnt;
    int sum;
};

int Q, lazy[4*SZ];
T tree[4*SZ];

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx].cnt += lazy[idx];
        if(tree[idx].cnt == 0) tree[idx].sum = tree[2*idx].sum + tree[2*idx+1].sum;
        else tree[idx].sum = e - s + 1;
        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int l, int r, int v, int s = 0, int e = SZ, int idx = 1)
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
    if(tree[idx].cnt) tree[idx].sum = e - s + 1;
    else tree[idx].sum = tree[2*idx].sum + tree[2*idx+1].sum;
}

int query(int l, int r, int s = 0, int e = SZ, int idx = 1)
{
    propagate(s, e, idx);
    if(r < s || e < l) return 0;

    if(l <= s && e <= r) return tree[idx].sum;
    if(tree[idx].cnt) return min(r, e) - max(l, s) + 1;

    int m = (s + e) / 2;
    return query(l, r, s, m, 2*idx) + query(l, r, m+1, e, 2*idx+1);
}

const int MAXQ = 300505;

struct Q_t {
    char op;
    int i, t, d, idx;
};
Q_t q[MAXQ];
int R[MAXQ], ans[MAXQ];
vector<Q_t> seg[4*MAXQ];
stack<pair<int, int>> st;
int IDX[MAXQ];
int maxtree[4*MAXQ];
vector<Q_t> v;

void upd(int x, int var, int s = 0, int e = v.size()-1, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        maxtree[idx] = var;
        return;
    }
    int m = (s + e) / 2;
    upd(x, var, s, m, 2*idx);
    upd(x, var, m+1, e, 2*idx+1);
    maxtree[idx] = max(maxtree[2*idx], maxtree[2*idx+1]);
}

int qry(int l, int r, int s = 0, int e = v.size()-1, int idx = 1)
{
    if(r < s || e < l) return 0;
    if(l <= s && e <= r) return maxtree[idx];
    int m = (s + e) / 2;
    return max(qry(l, r, s, m, 2*idx), qry(l, r, m+1, e, 2*idx+1));
}

void updates(int l, int r, Q_t& qt, int s = 0, int e = Q-1, int idx = 1)
{
    if(r < s || e < l) return;
    if(l <= s && e <= r) {
        seg[idx].push_back(qt);
        return;
    }
    int m = (s + e) / 2;
    updates(l, r, qt, s, m, 2*idx);
    updates(l, r, qt, m+1, e, 2*idx+1);
}

void add(Q_t qt)
{
    int lo = qt.t - 1;
    int hi = SZ;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(mid - qt.t + 1 - query(qt.t, mid) <= qt.d) lo = mid;
        else hi = mid;
    }
    update(qt.t, lo, 1);
    st.emplace(qt.t, lo);
    upd(IDX[qt.idx], lo);
}

void DnC(int s, int e, int idx)
{
    for(auto& qt : seg[idx]) {
        add(qt);
    }
    if(s == e) {
        if(q[s].op == '?') {
            int lo = 0;
            int hi = v.size();
            while(lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if(v[mid].t <= q[s].t) lo = mid;
                else hi = mid;
            }
            ans[s] = max(qry(0, lo) - q[s].t + 1, 0);
        }
    } else {
        int m = (s + e) / 2;
        DnC(s, m, 2*idx);
        DnC(m+1, e, 2*idx+1);
    }
    for(auto& qt : seg[idx]) {
        auto [lo, hi] = st.top(); st.pop();
        update(lo, hi, -1);
        upd(IDX[qt.idx], 0);
    }
}

int main()
{
    cin >> Q;
    for(int i = 0; i < Q; i++) {
        cin >> q[i].op;
        q[i].idx = i;
        if(q[i].op == '+') {
            cin >> q[i].t >> q[i].d;
            R[i] = Q;
            v.push_back(q[i]);
        } else if(q[i].op == '-') {
            cin >> q[i].i;
            q[i].i--;
            R[q[i].i] = i - 1;
        } else {
            cin >> q[i].t;
        }
    }
    sort(v.begin(), v.end(), [](Q_t a, Q_t b) {
        return a.t < b.t;
    });
    for(int i = 0; i < v.size(); i++) {
        IDX[v[i].idx] = i;
    }

    for(int i = 0; i < Q; i++) {
        if(q[i].op == '+') {
            updates(i, R[i], q[i]);
        }
    }

    DnC(0, Q-1, 1);
    for(int i = 0; i < Q; i++) {
        if(q[i].op == '?') {
            cout << ans[i] << "\n";
        }
    }
}