#include <cstdio>
#include <vector>
#include <cassert>
#include "craft.h"

int main() {
    init();
    int T;
    assert(1 == scanf("%d", &T));
    int cnt = 0;
    for (int i = 0; i < T; i++) {
        int N;
        assert(1 == scanf("%d", &N));
        std::vector<int> parent (N);
        for (int j = 0; j < N; j++) assert(1 == scanf("%d", &parent[j]));
        int a = classify(parent);
        if(a == 2) cnt++;
        printf("%d\n", a);
    }
    printf("CNT: %d\n", cnt);
    return 0;
}