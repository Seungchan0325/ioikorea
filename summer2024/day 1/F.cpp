#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

const int MAXN = 3005;

int N, DP[MAXN][MAXN];

int main()
{
    string s;
    cin >> s;
    N = s.size() + 1;
    s = "  " + s;

    DP[1][1] = 1;

    for(int i = 2; i <= N; i++) {
        if(s[i] == '<') {
            for(int j = 1; j <= i; j++) {
                DP[i][j] = ((DP[i-1][i-1] - DP[i-1][j-1]) % MOD + MOD) % MOD;
            }
        } else {
            for(int j = 1; j <= i; j++) {
                DP[i][j] = DP[i-1][j-1];
            }
        }

        for(int j = 1; j <= i; j++) {
            DP[i][j] = (DP[i][j] + DP[i][j-1]) % MOD;
        }
    }

    cout << DP[N][N];
}