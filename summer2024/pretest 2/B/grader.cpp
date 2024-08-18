#include "numbers.h"
#include "numbers.cpp"
#include <queue>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <stdbool.h>
extern bool numbers(std::vector<int>, std::vector<int>, std::vector<int>, std::vector<int>) ;
extern void init();

void assertion(bool x, int s) {
    if(x) return;
    else if(s < 0) puts("Wrong Input");
    else printf("Wrong Answer\n");
    exit(0);
}

static int T;

int main() {
    assertion(scanf("%d", &T) == 1, -1);
    init();
    for(int tc = 1; tc <= T; tc++) {
        std::vector<int> A, B, U, V;
        int N, M;
        assertion(scanf("%d%d", &N, &M) == 2, -1);
        for(int i = 0; i < N; i++) {
            int c;
            assertion(scanf("%d", &c) == 1, -1);
            A.push_back(c);
        }
        for(int i = 0; i < N; i++) {
            int c;
            assertion(scanf("%d", &c) == 1, -1);
            B.push_back(c);
        }
        for(int i = 0; i < M; i++) {
            int u, v;
            assertion(scanf("%d%d", &u, &v) == 2, -1);
            U.push_back(u);
            V.push_back(v);
        }
        bool result = numbers(A, B, U, V);
        if(result) printf("1\n");
        else printf("0\n");
    }
}
