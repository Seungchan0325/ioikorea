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
    if (ret != C) return printf("Wrong answer\n"), 0;
    printf("Accepted : %lld add call(s), %lld sub call(s), %lld mul call(s)\n", add_cnt, sub_cnt, mul_cnt);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "password.h"
#include <cassert>

using namespace std;

vector<unsigned int> longadd(vector<unsigned int> a, vector<unsigned int> b)
{
    vector<unsigned int> v(max(a.size(), b.size()));
    vector<bool> isused(max(a.size(), b.size()));
    for(int i = 0; i < max(a.size(), b.size()); i++) {
        if(i < a.size()) {
            v[i] = a[i];
            isused[i] = true;
        }
        if(i < b.size()) {
            if(isused[i]) v[i] = add(v[i], b[i]);
            else v[i] = b[i];
        }
        isused[i] = true;
    }
    return v;
}

vector<unsigned int> longsub(vector<unsigned int> a, vector<unsigned int> b)
{
    assert(a.size() >= b.size());
    vector<unsigned int> v(max(a.size(), b.size()));
    for(int i = 0; i < max(a.size(), b.size()); i++) {
        if(i < a.size()) v[i] = a[i];
        if(i < b.size()) v[i] = sub(v[i], b[i]);
    }
    return v;
}

vector<unsigned int> longmul(vector<unsigned int> a, vector<unsigned int> b)
{
    int n = a.size();
    if(n == 1) {
        return vector<unsigned int>{mul(a[0], b[0])};
    }
    int m = n/2;
    vector<unsigned int> A(a.begin()+m, a.end()),
                         B(a.begin(), a.begin()+m),
                         C(b.begin()+m, b.end()),
                         D(b.begin(), b.begin()+m);

    auto AC = longmul(A, C);
    auto BD = longmul(B, D);

    auto ApB = longadd(A, B);
    auto CpD = longadd(C, D);
    auto M = longmul(ApB, CpD);
    M = longsub(M, AC);
    M = longsub(M, BD);

    vector<unsigned int> v(2*n-1);
    vector<bool> isused(2*n-1);

    for(int i = 0; i < BD.size(); i++) {
        v[i] = BD[i];
        isused[i] = true;
    }

    for(int i = 0; i < M.size(); i++) {
        if(isused[i+B.size()]) v[i+B.size()] = add(v[i+B.size()], M[i]);
        else v[i+B.size()] = M[i];
        isused[i+B.size()] = true;
    }

    for(int i = 0; i < AC.size(); i++) {
        if(isused[i+2*B.size()]) v[i+2*B.size()] = add(v[i+2*B.size()], AC[i]);
        else v[i+2*B.size()] = AC[i];
        isused[i+B.size()] = true;
    }

    return v;
}

vector<unsigned int> find_password(vector<unsigned int> A, vector<unsigned int> B) {
    auto v = longmul(A, B);
    return v;
}