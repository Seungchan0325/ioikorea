#include <cstdio>
#include <cstdlib>
#include <vector>
#include <array>

extern std::vector<long long> max_stability(std::vector<int> A, std::vector<int> B, std::vector<int> L, std::vector<int> R);
void my_assert(bool x){ if(!x) { puts("invalid input"); exit(0); } } 

int main(){
    int N, M, Q;
	my_assert(scanf("%d%d%d", &N, &M, &Q) == 3);
	std::vector<int> A(N), B(M), L(Q), R(Q);
	for(int i = 0; i < N; i++) my_assert(scanf("%d",&A[i])==1);
	for(int i = 0; i < M; i++) my_assert(scanf("%d",&B[i])==1);
    for(int i = 0; i < Q; i++){
        my_assert(scanf("%d%d",&L[i],&R[i])==2);
    }
    auto res = max_stability(A,B,L,R);
    for(auto &t: res){
        printf("%lld\n",t);
    }
}
