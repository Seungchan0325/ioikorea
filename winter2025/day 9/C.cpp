#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e10;

struct Point {
    ll x, y;
    bool operator < (const Point& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
};

ll ccw(Point a, Point b, Point c)
{
    ll ret = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    if(ret < 0) return -1;
    if(ret > 0) return 1;
    return 0;
}

bool isInter(Point a, Point b, Point u, Point v)
{
    return ccw(a, b, u) * ccw(a, b, v) < 0 && ccw(u, v, a) * ccw(u, v, b) < 0;
}

bool isInPoly(vector<Point> poly, Point p)
{
    int n = poly.size();
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        Point up = poly[i];
        Point dw = poly[(i+1)%n];
        if(up.y < dw.y) swap(up, dw);
        if(up.x > p.x && up.y == p.y) cnt++;
        else {
            if(isInter(p, {p.x+INF, p.y}, up, dw)) cnt++;
        }
    }
    return cnt%2;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int C;
    cin >> C;
    while(C--) {
        int N;
        cin >> N;
        vector<Point> v(N);
        for(auto& [x, y] : v) cin >> x >> y;
        int idx = min_element(v.begin(), v.end()) - v.begin();
        Point o = v[idx];
        vector<int> p(N);
        iota(p.begin(), p.end(), 0);
        swap(p[idx], p[0]);
        sort(p.begin()+1, p.end(), [&](int i, int j){
            if(int t = ccw(o, v[i], v[j])) return t < 0;
            return abs(v[i].x - o.x) > abs(v[j].x - o.x) || abs(v[i].y - o.y) > abs(v[j].y - o.y);
        });
        idx = 1;
        while(idx < N && ccw(o, v[p[1]], v[p[idx]]) == 0) idx++;
        reverse(p.begin()+1, p.begin() + idx);
        for(int i = 0; i < N; i++) cout << p[i] << " ";
        cout << "\n";
    }
}