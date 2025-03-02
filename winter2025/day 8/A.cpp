#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1505;

int dp[MAXN][MAXN];

int main()
{
    int N, M;
    string X, Y;
    cin >> N >> M;
    cin >> X >> Y;
    X = " " + X;
    Y = " " + Y;
    memset(dp, 0x80, sizeof(dp));
    dp[0][0] = 0;
    for(int i = 1; i <= N; i++) dp[i][0] = dp[i-1][0]-2;
    for(int j = 1; j <= M; j++) dp[0][j] = dp[0][j-1]-2;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            dp[i][j] = max({dp[i-1][j]-2, dp[i][j-1]-2, dp[i-1][j-1]-1});
            if(X[i] == Y[j]) dp[i][j] = max(dp[i-1][j-1]+2, dp[i][j]);
        }
    }
    cout << dp[N][M] << "\n";
    
    string a, b;

    int i = N;
    int j = M;
    while(true) {
        if(i == 0 && j == 0) break;
        if(dp[i][j] == dp[i-1][j]-2) {
            a.push_back(X[i]);
            b.push_back('_');
            i--;
        } else if(dp[i][j] == dp[i][j-1]-2) {
            a.push_back('_');
            b.push_back(Y[j]);
            j--;
        } else if(dp[i][j] == dp[i-1][j-1]-1) {
            a.push_back(X[i]);
            b.push_back(Y[j]);
            i--;
            j--;
        } else if(X[i] == Y[j] && dp[i][j] == dp[i-1][j-1]+2) {
            a.push_back(X[i]);
            b.push_back(Y[j]);
            i--;
            j--;
        } else {
            assert(0);
        }
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    cout << a << "\n" << b;
}