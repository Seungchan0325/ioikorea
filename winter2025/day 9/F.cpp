#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    bool operator < (const Point& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
    Point operator + (const Point& rhs) const {
        return {x + rhs.x, y + rhs.y};
    }
    Point operator - (const Point& rhs) const {
        return {x - rhs.x, y - rhs.y};
    }
};

ll ccw(Point a, Point b, Point c)
{
    ll ret = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    if(ret < 0) return -1;
    if(ret > 0) return 1;
    return 0;
}

vector<Point> convexHull(vector<Point> p)
{
    int n = p.size();
    sort(p.begin(), p.end());
    vector<Point> up, dw;
    for(int i = 0; i < n; i++) {
        while(up.size() >= 2 && ccw(up.end()[-2], up.end()[-1], p[i]) >= 0) up.pop_back();
        while(dw.size() >= 2 && ccw(dw.end()[-2], dw.end()[-1], p[i]) <= 0) dw.pop_back();
        up.push_back(p[i]);
        dw.push_back(p[i]);
    }
    for(int i = up.size()-2; i >= 1; i--) dw.push_back(up[i]);
    return dw;
}

bool isInConvexHull(Point p, const vector<Point>& poly)
{
    if(poly.size() == 2) {
        return ccw(poly[0], poly[1], p) == 0 && min(poly[0], poly[1]) < p && p < max(poly[0], poly[1]);
    }
    int lo = 1;
    int hi = poly.size();
    if(ccw(poly[0], poly.back(), p) == 0) return min(poly[0], poly.back()) < p && p < max(poly[0], poly.back());
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(ccw(poly[0], poly[mid], p) >= 0) lo = mid;
        else hi = mid;
    }
    if(hi == poly.size()) return false;
    return ccw(poly[0], poly[lo], p) >= 0 && ccw(poly[0], poly[hi], p) <= 0 && ccw(poly[lo], poly[hi], p) >= 0;
}

int solve(vector<Point> A, vector<Point> B)
{
    int N = A.size();
    B = convexHull(B);
    int M = B.size();

    int cnt = 0;
    for(int i = 0; i < N; i++) {
        if(isInConvexHull(A[i], B)) {
            cnt++;
        }
    }
    return cnt;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N;
    cin >> N;
    vector<Point> A(N), B(N);
    for(auto& [x, y] : A) cin >> x >> y;
    for(auto& [x, y] : B) cin >> x >> y;

    cout << solve(B, A) << " " << solve(A, B) << "\n";
}