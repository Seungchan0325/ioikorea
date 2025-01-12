#ifndef __GRADER_CPP___

#define __GRADER_CPP___

#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>

static void my_assert(bool cond, const char *MSG) {
    if(!cond) {
        printf("Wrong Answer: %s\n", MSG);
        exit(0);
    }
}

int find_minmax(int N);

static int N;
const int MAX_N = 100000;
static std::vector<int> A;
static std::set<int> S;
static int num_calls = 0;
static int MAX_CALLS;

int get_larger_index(int i, int j){
    my_assert(1 <= i && i <= N, "`get_larger_index` -- `i` out of range");
    my_assert(1 <= j && j <= N, "`get_larger_index` -- `j` out of range");
    num_calls += 1;
    my_assert(num_calls <= MAX_CALLS, "too many get_larger_index calls");
    if( A[i] >= A[j] ) return i;
    else return j;
}

int main() {
    my_assert(scanf("%d", &N) == 1, "wrong input format");
    my_assert(1 <= N && N <= MAX_N, "wrong input -- `N` out of range");
    
    MAX_CALLS = 4 * N;
    A.resize(N+1);
    for(int i = 1; i <= N; i++){
        int x;
        my_assert(scanf("%d", &x) == 1, "wrong input format");
        my_assert(-1000000000 <= x && x <= 1000000000, "wrong input -- `A_i` out of range");
        my_assert(S.find(x) == S.end(), "wrong input -- not distinct element");
        A[i] = x;
        S.insert(x);
    }

    int a = 1, b = 1;
    for(int i=1;i<=N;i++){
        if( A[a] > A[i] ) a = i;
        if( A[b] < A[i] ) b = i;
    }

    int ans = a * 37 + b;

    if( ans != find_minmax(N) ) {
        puts("Incorrect answer");
        printf("Used %d get_larger_index calls\n", num_calls);
    }
    else{
        puts("Correct!");
        printf("Used %d get_larger_index calls\n", num_calls);
    }
    return 0;
}
#endif