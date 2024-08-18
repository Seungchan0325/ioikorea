#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;
const int MOD = 1e9 + 7;

long long N, DP[MAXN];

int main()
{
    cin >> N;
    
    DP[0] = 1;
    DP[1] = 1;
    DP[2] = 2;
    for(int i = 3; i <= N; i++) {
        DP[i] = (DP[i-1] + DP[i-2] + DP[i-3]) % MOD;
    }

    cout << DP[N];
}