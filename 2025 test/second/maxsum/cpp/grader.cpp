#include <iostream>
#include <vector>

extern std::vector<long long> maxsum(
    std::vector<int> A, std::vector<int> B, 
    std::vector<int> L1, std::vector<int> R1, 
    std::vector<int> L2, std::vector<int> R2);
 
void my_assert(bool x){
    if (!x){
        puts("Wrong input");
        exit(0);
    }
}
 
int main(){
    int N, Q;
    my_assert(scanf("%d %d", &N, &Q) == 2);
    
    std::vector<int> A(N), B(N);
    for (int i=0;i<N;i++){
        my_assert(scanf("%d %d", &A[i], &B[i]) == 2);
        my_assert(-1'000'000'000 <= A[i] && A[i] <= B[i] && B[i] <= 1'000'000'000);
    }
    
    std::vector<int> L1(Q), R1(Q), L2(Q), R2(Q);
    for (int i=0;i<Q;i++){
        my_assert(scanf("%d %d %d %d", &L1[i], &R1[i], &L2[i], &R2[i]) == 4);
        my_assert(0 <= L1[i] && L1[i] <= R1[i] && R1[i] <= N-1);
        my_assert(0 <= L2[i] && L2[i] <= R2[i] && R2[i] <= N-1);
    }
    
    std::vector<long long> S = maxsum(A, B, L1, R1, L2, R2);

    for (int i=0;i<(int)S.size();i++){
        printf("%lld", S[i]);
        if (i+1 < (int)S.size()) printf(" ");
        else printf("\n");
    }
}
