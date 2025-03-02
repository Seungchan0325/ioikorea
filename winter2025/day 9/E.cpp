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
    Point operator + (const Point& rhs) const {
        return {x + rhs.x, y + rhs.y};
    }
    Point operator - (const Point& rhs) const {
        return {x - rhs.x, y - rhs.y};
    }
};

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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int C;
    cin >> C;
    while(C--) {
        int N;
        cin >> N;
        vector<Point> A(N);
        for(auto& [x, y] : A) cin >> x >> y;
        A = convexHull(A);
        N = A.size();
        ll mx = 0;
        for(int i = 0; i < N; i++) {
            int a = i+1, b = i;
            for(int j = i+1; j < i+N; j++) {
                while(a - i < N && ccw(A[i%N], A[j%N], A[(a+1)%N] - A[a%N] + A[j%N]) >= 0) a++;
                while(b < j && ccw(A[i%N], A[j%N], A[(b+1)%N] - A[b%N] + A[j%N]) <= 0) b++;
                mx = max(mx, area(A[i%N], A[j%N], A[a%N]) + area(A[i%N], A[j%N], A[b%N]));
            }
        }
        cout << mx/2;
        if(mx%2) cout << ".5";
        cout << "\n";
    }
}