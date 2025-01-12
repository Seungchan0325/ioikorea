#include "kong.h"
// #include "grader.cpp"
#include <bits/stdc++.h>

using namespace std;

int kong(int n){
    vector<int> winner(n);
    iota(winner.begin(), winner.end(), 1);
    vector<vector<int>> loser(n+1);
    while(true) {
        if(winner.size() == 1) break;
        vector<int> newwinner;
        for(int i = 0; i < winner.size(); i+=2) {
            if(i+1 == winner.size()) {
                newwinner.push_back(winner[i]);
            } else {
                if(compare(winner[i], winner[i+1]) == 1) {
                    newwinner.push_back(winner[i]);
                    loser[winner[i]].push_back(winner[i+1]);
                } else {
                    newwinner.push_back(winner[i+1]);
                    loser[winner[i+1]].push_back(winner[i]);
                }
            }
        }
        winner = newwinner;
    }

    int mx = winner[0];
    int mx2 = loser[mx][0];
    for(int i = 1; i < loser[mx].size(); i++) {
        if(compare(mx2, loser[mx][i]) == -1) mx2 = loser[mx][i];
    }
    return mx2;
}
