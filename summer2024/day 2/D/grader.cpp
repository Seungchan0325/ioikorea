#include "password.h"
#include <bits/stdc++.h>

using namespace std;

static long long add_cnt, sub_cnt, mul_cnt;

unsigned int add(unsigned int x,unsigned  int y) {
    ++add_cnt;
    return x + y;
}

unsigned int sub(unsigned int x,unsigned  int y) {
    ++sub_cnt;
    return x - y;
}

unsigned int mul(unsigned int x,unsigned  int y) {
    ++mul_cnt;
    return x * y;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<unsigned int> A(n), B(n);
    for (int i = 0; i < n; ++i) scanf("%u", &A[i]);
    for (int i = 0; i < n; ++i) scanf("%u", &B[i]);
    vector<unsigned int> C(n + n - 1, 0);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        C[i + j] = add(C[i + j], mul(A[i], B[j]));
    }
    add_cnt = sub_cnt = mul_cnt = 0;
    vector<unsigned int> ret = find_password(A, B);
    for(int i = 2*n-2; i >= 0; i--) cout << C[i] << " ";
    cout << "\n";
    for(int i = ret.size()-1; i >= 0; i--) cout << ret[i] << " ";
    cout << "\n";
    if (ret != C) return printf("Wrong answer\n"), 0;
    printf("Accepted : %lld add call(s), %lld sub call(s), %lld mul call(s)\n", add_cnt, sub_cnt, mul_cnt);
    return 0;
}