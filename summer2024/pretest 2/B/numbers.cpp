#include "numbers.h"
#include <vector>
#include <stdbool.h>
#include <cstdio>
#include <algorithm>

using namespace std;

void init() {

}

bool numbers(std::vector<int> A, std::vector<int> B, std::vector<int> U, std::vector<int> V) {
    int N = A.size();
    int M = U.size();
    for(int i = 0; i < N; i++) {
        if(A[i] < B[i]) return false;
    }

    vector<int> deg(N+1);
    for(int i = 0; i < M; i++) {
        deg[U[i]]++;
        deg[V[i]]++;
    }

    int root = 1;
    vector<pair<int, int>> ver;
    vector<int> a;
    for(int i = 1; i <= N; i++) {
        ver.emplace_back(B[i-1], i);
        a.push_back(A[i-1]);
        if(deg[i] >= 2) root = i;
    }
    sort(a.begin(), a.end());
    sort(ver.begin(), ver.end(), greater<>());

    for(auto [b, idx] : ver) {
        if(!binary_search(a.begin(), a.end(), b)) return false;
        if(A[idx-1] != B[idx-1] && (A[root-1] < b || b < B[root-1])) return false;
    }
    return true;
}
