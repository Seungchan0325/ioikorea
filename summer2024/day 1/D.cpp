#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const ll MAXL = 1e7 + 5;

pair<int, int> EEA(int a, int b)
{
    int r0 = a;
    int r1 = b;
    int ca0 = 1, ca1 = 0;
    int cb0 = 0, cb1 = 1;
    
    while(r1) {
        int q = r0 / r1;
        
        int temp = r0 % r1;
        swap(r0, r1);
        r1 = temp;

        if(!r1) break;

        temp = ca0 - q * ca1;
        temp %= MOD;
        swap(ca0, ca1);
        ca1 = temp;

        temp = cb0 - q * cb1;
        temp %= MOD;
        swap(cb0, cb1);
        cb1 = temp;
    }

    return {ca1, cb1};
}

int L, F[MAXL], EEA_t[MAXL];

void init(int l)
{
    L = l;
    F[0] = 1;
    for(int i = 1; i < MAXL; i++) {
        F[i] = ((ll)i * F[i-1]) % MOD;
    }

    EEA_t[MAXL-1] = (EEA(MOD, F[MAXL-1]).second + MOD) % MOD;
    for(int i = MAXL-2; i >= 0; i--) {
        EEA_t[i] = ((ll)EEA_t[i+1] * (i+1)) % MOD;
    }
}

int ncm(int N, int M)
{
    int iden = ((ll)EEA_t[M] * EEA_t[N-M]) % MOD;
    int ret = (ll)F[N] * iden % MOD;
    return ret;
}

int main()
{
    int k, l;
    cin >> k >> l;
    init(l);
    while(k--)
    {
        int n, m;
        cin >> n >> m;
        cout << ncm(n, m) << "\n";
    }
}