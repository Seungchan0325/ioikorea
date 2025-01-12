#include "minmax.h"
// #include "grader.cpp"
#include <bits/stdc++.h>

using namespace std;

int find_minmax(int N) {
    vector<int> large, small;
    for(int i = 1; i+1 <= N; i += 2) {
        if(get_larger_index(i, i+1) == i) {
            large.push_back(i);
            small.push_back(i+1);
        } else {
            large.push_back(i+1);
            small.push_back(i);
        }
    }
    if(N%2) large.push_back(N), small.push_back(N);
    int mxi = large[0], mni = small[0];
    for(int i = 1; i < large.size(); i++) {
        mxi = get_larger_index(mxi, large[i]);
    }
    for(int i = 1; i < small.size(); i++) {
        mni = mni + small[i] - get_larger_index(small[i], mni);
    }
    return 37 * mni + mxi;
}