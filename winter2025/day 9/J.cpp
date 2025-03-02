#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y, w;
    bool operator < (const Point& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
};

struct Line {
    ll i, j, dx, dy;
    Line(ll i, ll j, Point pi, Point pj) : i(i), j(j), dx(pj.x-pi.x), dy(pj.y-pi.y) {}
    bool operator < (const Line& rhs) const {
        ll l = dy*rhs.dx;
        ll r = rhs.dy*dx;
        return tie(l, i, j) < tie(r, rhs.i, rhs.j);
    }
    bool operator == (const Line& rhs) const {
        return dy*rhs.dx == rhs.dy*dx;
    }
};


const int MAXN = 2005;

int N, pos[MAXN];
ll ans, lazy[4*MAXN];
Point A[MAXN];
ll tree[4*MAXN];

void push(int s, int e, int idx)
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

void update(int l, int r, ll delta, int s = 1, int e = N, int idx = 1)
{
    push(s, e, idx);
    if(e < l || r < s) return;

    if(s == e) {
        lazy[idx] += delta;
        push(s, e, idx);
        return;
    }

    int m = (s + e) / 2;
    update(l, r, delta, s, m, 2*idx);
    update(l, r, delta, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    vector<Point> A;
    for(int i = 1; i <= N; i++) {
        int x0, x1, y;
        cin >> x0 >> x1 >> y;
        if(x0 > 0) swap(x0, x1);
        A.push_back({x0, y, x1 - x0});
        A.push_back({x1+1, y, x0 - x1});
    }

    N = A.size();

    sort(A.begin(), A.end());
    for(int i = 0; i < N; i++) {
        pos[i] = i;
        update(i, N, A[i].w);
    }
    vector<Line> v;
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            v.emplace_back(i, j, A[i], A[j]);
        }
    }
    ans = max(ans, tree[1]);
    sort(v.begin(), v.end());
    for(int i = 0, j = 0; i < v.size(); i = j) {
        while(j < v.size() && v[i] == v[j]) j++;
        for(; i < j; i++) {
            auto p = v[i].i;
            auto q = v[i].j;
            if(pos[p] < pos[q]) {
                update(pos[p], pos[q]-1, A[pos[q]].w);
                update(pos[p], pos[q]-1, -A[pos[p]].w);
            } else {
                update(pos[q], pos[p]-1, -A[pos[q]].w);
                update(pos[q], pos[p]-1, A[pos[p]].w);
            }
            swap(A[pos[p]], A[pos[q]]);
            swap(pos[p], pos[q]);
        }
        ans = max(ans, tree[1]);
    }
    cout << ans;
}