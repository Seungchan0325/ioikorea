#include "maxmin.h"
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> recover_sequence(int);

namespace {
    std::vector<int> A;
    int N;
    int num_calls;
};

int max_plus_min(int i, int j, int k) {
    if (!(0 <= i && i < N && 
            0 <= j && j <= N && 
            0 <= k && k < N && 
            i != j && j != k && k != i)) {
        printf("ERROR: i=%d, j=%d, k=%d is invalid\n", i, j, k);
        exit(0);
    }
    num_calls += 1;
    int x = A[i];
    int y = A[j];
    int z = A[k];
    return std::min(std::min(x, y), z) + std::max(std::max(x, y), z);
}

int main() {
    num_calls = 0;

    std::cin >> N;
    for (int i = 0; i < N; i++) {
        int x; std::cin >> x;
        A.push_back(x);
    }

    std::vector<int> C = recover_sequence(N);

    if (C.size() != N) {
        printf("ERROR: size of the returned vector is not N: N=%d, C.size()=%d\n", N, int(C.size()));
        return 0;
    }

    if (C != A) {
        printf("WA: Returned sequence is not equal to A\n");
        for (int i = 0; i < N; i++) {
            printf("%d%c", C[i], i+1<N ? ' ' : '\n');
        }
        return 0;
    }

    puts("YES");
    printf("number of calls = %d\n", num_calls);
    return 0;
}