#include <cstdio>
#include <vector>
#include <random>
#include <cstdlib>
#include <algorithm>
 
extern std::vector<int> change_lamps(std::vector<int>, int) ;
 
static int N, K, M;
static std::vector<int> A;
 
static void assertion(bool x, int s) {
    if (x) return;
    if (s < 0) printf("Wrong Input");
    else printf("Wrong Answer[%d]", s);
    exit(0);
}

int main() {
    assertion(scanf("%d%d", &N, &K) == 2, -1);
    A.resize(N);
    for (int i = 0; i < N; i++) assertion(scanf("%1d", &A[i]) == 1, -1);
    std::vector<int> res = change_lamps(A, K);
    assertion((int)res.size() == N, 1);
    M = 0;
    for (int i = 0; i < N; i++) {
        assertion(res[i] == 0 || res[i] == 1, 2);
        if(res[i] != A[i]) ++M;
    }
    int cnt = 1;
    for (int i = 1; i < N; i++) if(res[i-1] != res[i]) ++cnt;
    assertion(cnt <= K, 3);
    for (int i = 0; i < N; i++) printf("%d", A[i]);
    printf("\n");
    printf("OK %d changes\n", M);
}
