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
    bool operator == (const Point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};

inline ll ccw(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int main()
{
    int N, P;
    cin >> N >> P;
    vector<Point> v(N);
    for(auto& [x, y] : v) cin >> x >> y;

    if(N == 1) {
        cout << "possible";
        return 0;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, N-1);

    for(int iter = 0; iter < 100; iter++) {
        Point p = v[dis(gen)];
        Point q = v[dis(gen)];
        while(p == q) q = v[dis(gen)];
        int cnt = 0;
        for(auto i : v) {
            if(ccw(p, q, i) == 0) cnt++;
        }
        if(cnt >= (N*P+99)/100) {
            cout << "possible";
            return 0;
        }
    }
    cout << "impossible";
}