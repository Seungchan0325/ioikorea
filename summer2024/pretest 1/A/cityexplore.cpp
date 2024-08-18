#include "cityexplore.h"
#include <bits/stdc++.h>

using namespace std;

void DnC(int lo, int hi, vector<int> P)
{
    int N = P.size();
    vector<int> NP(N);

    int m = -1;
    for(int i = 1; i < N; i++) {
        if(P[i] == 1) {
            m = i;
            break;
        }
    }

    if(m == -1) {
        if(!P[0]) return;
        m = 0;
    }

    for(int i = 0; i < N; i++) {
        if(P[i] == 1 && i != m && i != lo) {
            P[i] = 0;

            bool f = false;
            if(!P[lo]) f = true,P[lo] = 1;

            bool cango = investigate(min(m, lo), max(m, lo), P);

            if(f) P[lo] = false;

            if(cango) {
                NP[i] = 1;
            } else {
                P[i] = 1;
            }

            vector<int> P1(N);
            P1[m] = 1;
            P1[i] = 1;

            cango = investigate(min(m, i), max(m, i), P1);
            if(cango) report(min(m, i), max(m, i));
        }
    }

    P[m] = 0;

    DnC(lo, m, P);
    DnC(m, hi, NP);
}

void city_explore(int T, int N) {
    vector<int> P(N, 1);
    DnC(0, N-1, P);

    // for(int i = 0; i < N; i++) {
    //     for(int j = i+1; j < N; j++) {
    //         P[i] = P[j] = 1;
    //         if(investigate(i, j, P)) {
    //             report(i, j);
    //         }
    //         P[i] = P[j] = 0;
    //     }
    // }
}