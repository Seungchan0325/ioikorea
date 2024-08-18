#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int N, M, DP[MAXN][3];
string S;

int main()
{
    cin >> N >> M >> S;
    S = ' ' + S;

    DP[1][0] = 1;
    DP[1][1] = 1;

    DP[2][0] = 2;
    DP[2][1] = 1;
    DP[2][2] = 1;
    for(int i = 3; i <= N; i++) {
        DP[i][2] = (DP[i-1][1]) % M;
        DP[i][1] = (DP[i-1][2] + DP[i-1][0]) % M;
        DP[i][0] = (DP[i-1][1] + 1) % M;
    }


    int ans = 1;
    int cnt = 0;
    for(int i = 1; i <= N; i++) {
        if(S[i] == 'R') {
            if(cnt == 0) ans = (ans + DP[N-i+1][0] + DP[N-i+1][1]) % M;
            else if(cnt == 1) ans = (ans + DP[N-i][0] + DP[N-i][1]) % M;
            cnt = 0;
        } else {
            cnt++;
        }
    }
    cout << ans;
}