#include "maxmin.h"
#include "grader.cpp"
#include <bits/stdc++.h>

using namespace std;

int query(int i, int j, int k)
{
    static map<array<int, 3>, int> m;
    if(i > j) swap(i, j);
    if(j > k) swap(j, k);
    if(i > j) swap(i, j);
    if(m.count({i, j, k})) return m[{i, j, k}];
    return m[{i, j, k}] = max_plus_min(i, j, k);
}

pair<int, int> get_min_max(int a, int b, int c, int d)
{
    int abc = query(a, b, c);
    int abd = query(a, b, d);
    int acd = query(a, c, d);
    int bcd = query(b, c, d);

    auto [mn, mnbit] = min({make_pair(abc, 0b1110), make_pair(abd, 0b1101), make_pair(acd, 0b1011), make_pair(bcd, 0b0111)});
    auto [mx, mxbit] = max({make_pair(abc, 0b1110), make_pair(abd, 0b1101), make_pair(acd, 0b1011), make_pair(bcd, 0b0111)});

    int mni = mnbit & ~mxbit;
    int mxi = mxbit & ~mnbit;

    int mnidx = -1;
    if(mni == 0b1000) mnidx = a;
    else if(mni == 0b0100) mnidx = b;
    else if(mni == 0b0010) mnidx = c;
    else if(mni == 0b0001) mnidx = d;
    else assert(0);

    int mxidx = -1;
    if(mxi == 0b1000) mxidx = a;
    else if(mxi == 0b0100) mxidx = b;
    else if(mxi == 0b0010) mxidx = c;
    else if(mxi == 0b0001) mxidx = d;
    else assert(0);

    return {mnidx, mxidx};
}

array<int, 5> get_order(array<int, 5> indexes)
{
    auto bit_qry = [&](int bit)
    {
        vector<int> v;
        for(int i = 0; i < 5; i++) {
            if(bit&(1<<i)) v.push_back(indexes[i]);
        }
        assert(v.size() == 4);
        return get_min_max(v[0], v[1], v[2], v[3]);
    };
    int bit1 = -1;
    int bit2 = -1;
    array<int, 5> order = {0, 0, 0, 0, 0};
    for(int i = 0; i < 5; i++) {
        int bit = 0b11111 ^ (1<<i);
        auto [mn, mx] = bit_qry(bit);
        int cnt1 = 0;
        int cnt2 = 0;
        for(int j = 0; j < 5; j++) {
            if(i == j) continue;
            int jbit = 0b11111 ^ (1<<j);
            auto [mnj, mxj] = bit_qry(jbit);
            if(mnj != mn) cnt1++;
            if(mxj != mx) cnt2++;
        }
        if(cnt1 > 2) bit1 = bit;
        else if(cnt2 > 2) bit2 = bit;
        else {
            order[0] = mn;
            order[4] = mx;
        }
    }

    assert(bit1 != -1);
    assert(bit2 != -1);

    auto [mn1, mx1] = bit_qry(bit1);
    auto [mn2, mx2] = bit_qry(bit2);
    order[1] = mn1;
    order[3] = mx2;
    
    for(int i = 0; i < 5; i++) {
        if(order[0] != indexes[i] && order[1] != indexes[i] && order[3] != indexes[i] && order[4] != indexes[i]) {
            order[2] = indexes[i];
            break;
        }
    }

    return order;
}

vector<int> ans;

void get_value(array<int, 5> indexes)
{
    auto order = get_order(indexes);
    array<int, 5> value;
    value[0] = query(order[0], order[1], order[2]) + query(order[0], order[1], order[4]) - query(order[2], order[3], order[4]);
    value[0] /= 2;
    value[2] = query(order[0], order[1], order[2]) - value[0];
    value[3] = query(order[0], order[1], order[3]) - value[0];
    value[4] = query(order[0], order[1], order[4]) - value[0];
    value[1] = query(order[1], order[2], order[3]) - value[3];

    for(int i = 0; i < 5; i++) {
        ans[order[i]] = value[i];
    }
}

std::vector<int> recover_sequence (int n) {
    ans.resize(n);

    get_value({0, 1, 2, 3, 4});

    set<tuple<int, int, int>> s;
    set<pair<int, int>> order;
    auto push = [&](int a, int b)
    {
        if(ans[a] > ans[b]) swap(a, b);
        s.emplace(ans[b] - ans[a], a, b);
    };

    for(int i = 0; i < 5; i++) {
        order.emplace(ans[i], i);
        for(int j = i+1; j < 5; j++) {
            push(i, j);
        }
    }

    for(int i = 5; i < n; i++) {
        auto [d, l, r] = *s.begin();
        while(query(l, r, i) == ans[l] + ans[r]) {
            s.erase(make_tuple(d, l, r));
            tie(d, l, r) = *s.begin();
        }
        if(query(l, r, i) < ans[l] + ans[r]) {
            ans[i] = query(l, r, i) - ans[r];
        } else {
            ans[i] = query(l, r, i) - ans[l];
        }
        auto it = order.lower_bound({ans[i], i});
        if(it != order.end()) {
            push(i, it->second);
        }
        if(it != order.begin()) {
            it--;
            push(i, it->second);
        }
        order.emplace(ans[i], i);
    }

    return ans;
}