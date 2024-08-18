#include "subarraymin.h"
#include <bits/stdc++.h>

using namespace std;    

void subarray_min(int n, int k) {
    deque<int> dq;
    for(int i = n; i > n-k+1; i--) {
        while(dq.size() && dq.front() > i + k - 1) dq.pop_front();
        while(dq.size() && !compare(dq.back(), i)) dq.pop_back();
        dq.push_back(i);
        // answer(i, dq.front());
    }

    for(int i = n-k+1; i >= 1; i--) {
        while(dq.size() && dq.front() > i + k - 1) dq.pop_front();
        while(dq.size() && !compare(dq.back(), i)) dq.pop_back();
        dq.push_back(i);
        answer(i, dq.front());
    }
}

// #include <cstdio>
// #include <cstdlib>
// #include <algorithm>
// #include "subarraymin.h"

using namespace std;

static int n, k, A[1005], cnt, answered[1005];

static void iassert(int x) {
    if (x) return;
    printf("Wrong Answer\n");
    exit(0);
}

bool compare(int i, int j) {
    ++cnt;
    iassert(1 <= i && i <= n && 1 <= j && j <= n);
    return A[i] < A[j];
}

void answer(int i, int x) {
    iassert(1 <= i && i <= n - k + 1 && i <= x && x <= i + k - 1 && !answered[i]);
    answered[i] = 1;
    int mn = 1e9;
    for (int j = i; j <= i + k - 1; ++j) mn = min(mn, A[j]);
    iassert(A[x] == mn);
}

int main() {
    iassert(int(scanf("%d%d", &n, &k)) == 2);
    for (int i = 1; i <= n; ++i) iassert(int(scanf("%d", &A[i])) == 1);
    subarray_min(n, k);
    for (int i = 1; i <= n - k + 1; ++i) iassert(answered[i]);
    printf("Accepted : %d compare call(s)\n", cnt);
    return 0;
}