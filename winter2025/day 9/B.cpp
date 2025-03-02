#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e10;

struct Point {
    ll x, y;
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
    int N;
    cin >> N;
    vector<Point> v(N);
    for(auto& [x, y] : v) cin >> x >> y;
    Point P1, P2;
    cin >> P1.x >> P1.y;
    cin >> P2.x >> P2.y;
    if(isInPoly(v, P1)) cout << "in\n";
    else cout << "out\n";
    if(isInPoly(v, P2)) cout << "in\n";
    else cout << "out\n";
}