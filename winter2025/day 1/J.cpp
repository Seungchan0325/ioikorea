#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200505;

struct P {
    int t;
    int low, high;
    bool operator < (int x) {
        return t < x;
    }
    bool operator < (const P& rhs) const {
        return t < rhs.t;
    }
};

bool operator < (P p, int x)
{
    return p.t < x;
}
bool operator < (int x, P p)
{
    return x < p.t;
}

int N, A[MAXN], B[MAXN], K[MAXN];
vector<P> tree[4*MAXN];

int f(int x, vector<P>& p)
{
    int n = p.size();
    int idx = upper_bound(p.begin(), p.end(), x) - p.begin();
    if(idx == n) {
        return p[idx-1].high;
    }
    return p[idx].low;
}

vector<P> merge(vector<P> a, vector<P> b)
{
    int n = a.size();
    int m = b.size();
    vector<P> ret;

    int i, j;
    i = j = 0;
    while(i < n || j < m) {
        P nw;
        if(i < n && j < m && a[i].t == b[j].t - a[i].high) {
            nw.t = a[i].t;
            nw.low = a[i].low + b[j].low;
            nw.high = a[i].high + b[j].high;
            ret.push_back(nw);
            i++;
            j++;
        } else if(ret.size() && j < m && b[j].t - ret.back().high < ret.back().t) {
            j++;
        } else if((i >= n) || (j < m && b[j].t - a[i].low < a[i].t)){
            nw = b[j];
            if(i < n) {
                nw.t -= a[i].low;
                nw.low += a[i].low;
                nw.high += a[i].low;
            } else {
                nw.t -= a[n-1].high;
                nw.low += a[n-1].high;
                nw.high += a[n-1].high;
            }
            ret.push_back(nw);
            j++;
        } else {
            nw = a[i];
            if(j < m) {
                nw.low += b[j].low;
                while(j < m && b[j].t - nw.high < nw.t) j++;
                if(j < m)
                    nw.high += b[j].low;
                else
                    nw.high += b[m-1].high;
            } else {
                nw.low += b[m-1].high;
                nw.high += b[m-1].high;
            }
            ret.push_back(nw);
            i++;
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

int query(int l, int r, int x, int s = 0, int e = N+1, int idx = 1)
{
    if(l <= s && e <= r) return f(x, tree[idx]);
    int m = (s + e) / 2;
    if(r <= m) return query(l, r, x, s, m, 2*idx);
    if(m+1 <= l) return query(l, r, x, m+1, e, 2*idx+1);
    x = query(l, r, x, s, m, 2*idx);
    return x + query(l, r, x, m+1, e, 2*idx+1);
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i] >> B[i] >> K[i];
    }

    init();
    for(int i = 1; i <= N; i++) {
        int x = query(0, i-1, 0);
        x = x + query(i+1, N+1, x);
        cout << x << "\n";
    }
}