#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 20020;

int N, X[MAXN], Y[MAXN], dp[MAXN][2020][2];

int main()
{
    cin >> N;
    X[0] = Y[0] = 1000;
    for(int i = 1; i <= N; i++) {
        cin >> X[i] >> Y[i];
        X[i] += 1000;
        Y[i] += 1000;
    }

    for(int i = 0; i < MAXN; i++)
        for(int xy = 0; xy < 2020; xy++)
            dp[i][xy][0] = dp[i][xy][1] = 1e9;

    for(int xy = 0; xy <= 2000; xy++) dp[0][xy][0] = dp[0][xy][1] = abs(1000 - xy);
    for(int i = 1; i <= N; i++) {
        for(int xy = 0; xy <= 2000; xy++) {
            int x = xy;
            int y = Y[i];
            dp[i][xy][0] = min(dp[i-1][x][0] + abs(Y[i-1]-y), dp[i-1][y][1] + abs(X[i-1]-x));
            x = X[i];
            y = xy;
            dp[i][xy][1] = min(dp[i-1][x][0] + abs(Y[i-1]-y), dp[i-1][y][1] + abs(X[i-1]-x));
        }
    }

    int ans = 1e9;
    for(int xy = 0; xy <= 2000; xy++) {
        ans = min(ans, dp[N][xy][0]);
        ans = min(ans, dp[N][xy][1]);
    }
    cout << ans;
}