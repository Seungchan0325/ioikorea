#include <vector>
#include "grader.cpp"
#include <bits/stdc++.h>

using namespace std;

std::random_device rd;
std::mt19937 gen(rd());

using lint = long long;
double random_real(double l, double r)
{
    l = clamp(l, 0.0, 1e5);
    r = clamp(r, 0.0, 1e5);
    return uniform_real_distribution<double>(l, r)(gen);
}
lint random_int(lint l, lint r)
{
    return uniform_int_distribution<lint>(l, r)(gen);
}

lint ccw(pair<lint, lint> o, pair<lint, lint> a, pair<lint, lint> b) {
    lint c = (lint)(a.first-o.first)*(b.second-o.second) - (lint)(a.second-o.second)*(b.first-o.first);
    if(c > 0) return 1; // 반 시계 방향
    if(c < 0) return -1; // 시계 방향
    return 0; // 일직선 상
}

struct State {
    double x, y, f1, f2;
    void change()
    {
        x = random_real(x - 1000, x + 1000);
        y = random_real(y - 1000, y + 1000);
    }
    double get_deg1(std::vector<lint>& x1, std::vector<lint>& y1)
    {
        auto cmp = [&](pair<lint, lint> p,pair<lint, lint> q){
            if((p<make_pair((lint)x, (lint)y))^(q<make_pair((lint)x, (lint)y))) return q < p;
            if(lint t = ccw(make_pair((lint)x, (lint)y),p,q)) return t > 0;
            return abs(p.first)<abs(q.first) || abs(p.second)<abs(q.second);
        };
        lint x0 = -1, y0 = -1;
        vector<pair<lint, lint>> v;
        for(lint i = 0; i < x1.size(); i++) {
            if(x1[i] <= x) {
                if(x0 < 0 || cmp({x0, y0}, {x1[i], y1[i]})) {
                    x0 = x1[i];
                    y0 = y1[i];
                }
                v.emplace_back(x1[i], y1[i]);
            }
        }
        if(x0 < 0) return 1e9;
        double ret = (double)(y0 - y) / (x0 - x) + 0.01;
        f1 = ret;
        return ret;
    }
    double get_deg2(std::vector<lint>& x1, std::vector<lint>& y1)
    {
        auto cmp = [&](pair<lint, lint> p,pair<lint, lint> q){
            if((p<make_pair((lint)x, (lint)y))^(q<make_pair((lint)x, (lint)y))) return q < p;
            if(lint t = ccw(make_pair((lint)x, (lint)y),p,q)) return t > 0;
            return abs(p.first)<abs(q.first) || abs(p.second)<abs(q.second);
        };
        lint x0 = -1, y0 = -1;
        vector<pair<lint, lint>> v;
        for(lint i = 0; i < x1.size(); i++) {
            if(x1[i] >= x) {
                if(x0 < 0 || !cmp({x0, y0}, {x1[i], y1[i]})) {
                    x0 = x1[i];
                    y0 = y1[i];
                }
                v.emplace_back(x1[i], y1[i]);
            }
        }
        if(x0 < 0) return 1e9;
        double ret = (double)(y0 - y) / (x0 - x) - 0.01;
        f2 = ret;
        return ret;
    }
    lint get_score(std::vector<lint>& x1, std::vector<lint>& y1, std::vector<lint>& x2, std::vector<lint>& y2)
    {
        lint N = x1.size();
        lint M = x2.size();
        lint wrong = 0;
        for(lint iter = 0; iter < 3000; iter++) {
            lint i = random_int(0, N-1);
            if(x1[i] <= x) {
                if(y1[i] < f1 * (x1[i] - x) + y) {
                    wrong++;
                    // assert(0);
                }
            } else {
                if(y1[i] < f2 * (x1[i] - x) + y) {
                    wrong++;
                    // assert(0);
                }
            }
        }
        for(lint iter = 0; iter < 3000; iter++) {
            lint i = random_int(0, M-1);
            if(x2[i] <= x) {
                if(y2[i] > f1 * (x2[i] - x) + y) wrong++;
            } else {
                if(y2[i] > f2 * (x2[i] - x) + y) wrong++;
            }
        }
        return wrong;
    }
};

std::vector<double> classify(std::vector<int> _x1, std::vector<int> _y1, std::vector<int> _x2, std::vector<int> _y2) {
    vector<lint> x1;
    for(auto i : _x1) x1.push_back(i);
    vector<lint> x2;
    for(auto i : _x2) x2.push_back(i);
    vector<lint> y1;
    for(auto i : _y1) y1.push_back(i);
    vector<lint> y2;
    for(auto i : _y2) y2.push_back(i);
    State ret;
    ret.x = 1e5/2;
    ret.y = 1e5/2;
    ret.f1 = ret.get_deg1(x1, y1);
    ret.f2 = ret.get_deg2(x1, y1);
    for(lint iter = 0; iter < 10000; iter++) {
        State st;
        st.x = random_real(0, 1e5);
        st.y = random_real(0, 1e5);
        st.f1 = st.get_deg1(x1, y1);
        st.f2 = st.get_deg2(x1, y1);

        if(st.get_score(x1, y1, x2, y2) < ret.get_score(x1, y1, x2, y2)) ret = st;
    }

    return {ret.x, ret.y, ret.get_deg1(x1, y1), ret.get_deg2(x1, y1)};
}