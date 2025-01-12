#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

int N, A, B, S[MAXN], Q[MAXN], dp[MAXN][MAXN][5050];

int main()
{
    cin >> N >> A >> B;
    for(int i = 1; i <= N; i++) {
        cin >> S[i] >> Q[i];
    }

    memset(dp, 0x7F, sizeof(dp));

    for(int i = 0; i <= N; i++) for(int k = 0; k <= A; k++) dp[i][0][k] = 0;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            for(int k = 0; k <= A; k++) {
                dp[i][j][k] = dp[i-1][j][k];
                dp[i][j][k] = min(dp[i][j][k], dp[i][j][k-1]);
                if(k-S[i] >= 0) dp[i][j][k] = min(dp[i][j][k], dp[i-1][j-1][k-S[i]]+Q[i]);
            }
        }
    }

    int ans = 0;
    for(int j = 1; j <= N; j++) {
        for(int k = 0; k <= A; k++) {
            if(dp[N][j][k] <= B) ans = max(ans, j);
        }
    }
    cout << ans;
}