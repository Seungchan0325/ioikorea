#include <cstdio>
#include <string>
#include <cassert>

extern void init(int, std::string);
extern long long contest_time(long long, long long, long long);

#include "contest.cpp"

static int N, Q;
static std::string S;
static char str[1000005];

void assertion(bool x)
{
    if (x) return;
    else {
        printf("Wrong Input\n");
        exit(0);
    }
}

int main()
{
    assertion(scanf("%d", &N) == 1);
    assertion(scanf("%s", str) == 1);
    S = std::string(str);
    init(N, S);
    assertion(scanf("%d", &Q) == 1);
    for (int i = 0; i < Q; i++) {
        long long A, L, R;
        assertion(scanf("%lld %lld %lld", &A, &L, &R) == 3);
        printf("%lld\n", contest_time(A, L, R));
    }
    return 0;
}