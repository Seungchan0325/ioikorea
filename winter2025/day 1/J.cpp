#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 200505;

struct P {
    ll t;
    ll low, high;
    bool operator < (ll x) {
        return t < x;
    }
    bool operator < (const P& rhs) const {
        return t < rhs.t;
    }
};

bool operator < (P p, ll x)
{
    return p.t < x;
}
bool operator < (ll x, P p)
{
    return x < p.t;
}

int N, A[MAXN], B[MAXN], K[MAXN];
vector<P> tree[4*MAXN];

ll f(ll x, const vector<P>& p)
{
    int n = p.size();
    int lo = -1;
    int hi = n;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(p[mid].t <= x) lo = mid;
        else hi = mid;
    }
    if(lo == -1) return p[0].low;
    return p[lo].high;
}

vector<P> merge(const vector<P>& a, const vector<P>& b)
{
    int n = a.size();
    int m = b.size();

    vector<P> newa, newb;
    newa.reserve(n);
    newb.reserve(m);

    ll x1 = b[0].low;
    ll x2 = b[0].low;
    int idx1 = -1;
    int idx2 = -1;

    for(int i = 0; i < n; i++) {
        P p = a[i];

        while(idx1+1 < m && b[idx1+1].t <= p.t + p.high) idx1++;
        if(idx1 != -1) x1 = b[idx1].high;
        p.high += x1;

        while(idx2+1 < m && b[idx2+1].t <= p.t - 1 + p.low) idx2++;
        if(idx2 != -1) x2 = b[idx2].high;
        p.low += x2;

        newa.push_back(p);
    }

    int idx = -1;

    for(int i = 0; i < m; i++) {
        P p = b[i];

        while(idx+1 < n && a[idx+1].high + a[idx+1].t <= p.t) idx++;
        ll x;
        if(idx < 0) {
            x = p.t - a[0].low;
            if(x >= a[0].t) continue;
        } else {
            x = p.t - a[idx].high;
            if(a[idx].t > x || (idx+1 < n && x >= a[idx+1].t)) continue;
        }

        p.t = x;
        p.high += f(x, a);
        p.low += f(x-1, a);
        newb.push_back(p);
    }

    m = newb.size();

    int i, j;
    i = j = 0;
    vector<P> ret;
    ret.reserve(n+m);
    while(i < n || j < m) {
        if(i < n && j < m && newa[i].t == newb[j].t) {
            // assert(newa[i].low == newb[j].low); 이거 만족안하는데 안됨???
            // assert(newa[i].high == newb[j].high);
            ret.push_back(newa[i]);
            i++;
            j++;
        }
        else if((j >= m) || (i < n && newa[i] < newb[j])) {
            ret.push_back(newa[i++]);
        } else {
            ret.push_back(newb[j++]);
        }
    }

    return ret;
}

void init(int s = 0, int e = N+1, int idx = 1)
{
    if(s == e) {
        tree[idx].push_back({K[s], A[s], B[s]});
        return;
    }

    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

ll query(int l, int r, ll x, int s = 0, int e = N+1, int idx = 1)
{
    if(l <= s && e <= r) return f(x, tree[idx]);
    int m = (s + e) / 2;
    if(r <= m) return query(l, r, x, s, m, 2*idx);
    if(m+1 <= l) return query(l, r, x, m+1, e, 2*idx+1);
    ll q = query(l, r, x, s, m, 2*idx);
    return q + query(l, r, x + q, m+1, e, 2*idx+1);
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i] >> B[i] >> K[i];
    }

    init();
    for(int i = 1; i <= N; i++) {
        ll x = query(0, i-1, 0);
        x = x + query(i+1, N+1, x);
        cout << x << "\n";
    }
}