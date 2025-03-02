#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")


#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    bool operator < (const Point& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
};

struct Line {
    ll i, j, dx, dy;
    Line(ll i, ll j, Point p, Point q) : i(i), j(j), dx(q.x-p.x), dy(q.y-p.y) {}
    bool operator < (const Line& rhs) const {
        ll l = dy * rhs.dx;
        ll r = rhs.dy * dx;
        return tie(l, i, j) < tie(r, rhs.i, rhs.j);
    }

    bool operator == (const Line& rhs) const {
        return dy*rhs.dx == rhs.dy*dx;
    }
};

const int MAXN = 1005;

ll area(Point a, Point b, Point c)
{
    return abs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

ll ccw(Point a, Point b, Point c)
{
    ll ret = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    if(ret < 0) return -1;
    if(ret > 0) return 1;
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N, P;
    cin >> N >> P;
    vector<Point> A(N);
    for(auto& [x, y] : A) cin >> x >> y;

    sort(A.begin(), A.end());
    vector<int> pos(N);
    iota(pos.begin(), pos.end(), 0);

    vector<Line> v;
    v.reserve(N*N);
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            v.emplace_back(i, j, A[i], A[j]);
        }
    }
    sort(v.begin(), v.end());

    ll mx = 0;
    for(int i = 0, j = 0; i < v.size();) {
        while(j < v.size() && v[i] == v[j]) j++;
        mx = max(mx, (ll)j - i);
        i = j;  
    }

    if(mx >= (N*P+99)/100) cout << "possible";
    else cout << "impossible";
}