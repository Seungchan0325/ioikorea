#include <array>
#include <string>
#include <bits/stdc++.h>
#include "grader.cpp"
using namespace std;

array<int, 2> roadwork(string S){
    vector<pair<int, int>> v;
    v.clear();
    int i, j;
    i = j = 0;
    v.emplace_back(i, j);
    for(int k = 0; k < S.size(); k++) {
        if(S[k] == 'A') j++;
        else i++;
        v.emplace_back(i, j);
    }
    assert(i == j);

    vector<vector<int>> g(i+1);
    for(auto [i, j] : v) {
        g[i].push_back(j);
    }
    int cnt = 0;
    int mx = -1;
    for(int k = 0; k <= i; k++) {
        int mn = 1e9;
        for(auto l : g[k]) {
            if(mx < l) {
                mn = min(mn, l);
            }
        }
        if(mn < 1e9) {
            mx = mn;
            cnt++;
        }
    }
    return {cnt, -1};
}
