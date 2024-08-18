// 8, 45, 46, 49, 51, 54, 58th line modified
#include "queryandarray.h"
#include "queryandarray.cpp"
#include <queue>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
extern std::vector<int> findarray(int, std::vector<int>, std::vector<int>, std::vector<int>) ;

void assertion(bool x, int s) {
    if(x) return;
    else if(s < 0) puts("Wrong Input");
    else printf("Wrong Answer\n");
    exit(0);
}

static int _N, Q;

int main() {
    assertion(scanf("%d%d", &_N, &Q) == 2, -1);
    std::vector<int> L, R, A;
    for (int i = 0; i < Q; i++) {
        int l, r, a;
        assertion(scanf("%d%d%d", &l, &r, &a) == 3, -1);
        L.push_back(l);
        R.push_back(r);
        A.push_back(a);
    }
    std::vector<int> ans = findarray(_N, L, R, A);
    if(ans.size() != _N) {
        printf("Wrong Output : return vector size is not _N");
        exit(0);
    }
    bool isExistZero = false;
    for(int i = 0; i < _N; i++) {
        if(ans[i]==-1) isExistZero = true;
    }
    if(isExistZero) {
        for(int i = 0; i < _N; i++) {
            if(ans[i] != -1) {
                printf("Wrong Output : Impossible but not all element is -1");
                exit(0);
            }
        }
        for(int i = 0; i < _N; i++) printf("%d ", ans[i]);
        exit(0);
    }
    for(int i = 0; i < _N; i++) {
        if(ans[i] < 0 || ans[i] >= _N) {
            printf("Wrong Output : V[%d] out of range", i);
            exit(0);
        }
    }
    for(int i = 0; i < _N; i++) printf("%d ", ans[i]);
    sort(ans.begin(),ans.end());
    for(int i = 0; i < _N; i++) {
        if(ans[i] != i) {
            printf("\nNot permutation : Partially correct");
            exit(0);
        }
    }
}
