#include <bits/stdc++.h>
#include "grader.cpp"

using namespace std;

struct DSU {
    vector<int> root;
    void init(int N) {
        root.resize(N);
        iota(root.begin(), root.end(), 0);
    }

    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

const int MAXN = 500505;

struct Rect {
    int a, b, c, d, idx;
};

vector<int> xs, ys;
DSU dsu;

void DnC(int l, int r, vector<Rect> v)
{
    int m = (l + r) / 2;
    vector<Rect> left, right, now;
    for(auto rect : v) {
        if(rect.a <= xs[m] && xs[m] <= rect.c) {
            now.push_back(rect);
        }
        if(rect.a < xs[m]) {
            left.push_back(rect);
        }
        if(xs[m] < rect.c) {
            right.push_back(rect);
        }
    }

    sort(now.begin(), now.end(), [](Rect a, Rect b){
        return a.b < b.b;
    });
    int mx = -2e9;
    int mxi = -1;
    for(auto rect : now) {
        if(rect.b <= mx) dsu.merge(rect.idx, mxi);
        if(rect.d > mx) {
            mx = rect.d;
            mxi = rect.idx;
        }
    }
    sort(now.begin(), now.end(), [](Rect a, Rect b){
        return a.a < b.a;
    });

    if(l == r) return;

    DnC(l, m, left);
    DnC(m+1, r, right);
}

std::vector<int> find_union(int N, std::vector<int> A, std::vector<int> B, std::vector<int> C, std::vector<int> D) {
    dsu.init(N);
    vector<Rect> v;
    for(int i = 0; i < N; i++) {
        int a = A[i];
        int b = B[i];
        int c = C[i];
        int d = D[i];
        xs.push_back(a);
        // xs.push_back(c);
        // ys.push_back(b);
        // ys.push_back(d);
        v.push_back({a, b, c, d, i});
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(v.begin(), v.end(), [](Rect a, Rect b)
    {
        return a.a < b.a;
    });
    DnC(0, xs.size()-1, v);
    vector<int> ans(N);
    for(int i = 0; i < N; i++) {
        ans[i] = dsu.find(i);
    }
    return ans;
}