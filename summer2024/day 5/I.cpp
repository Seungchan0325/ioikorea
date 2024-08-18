#include <bits/stdc++.h>

using namespace std;

const int MAXA = 2000005;
const int MAXB = 4005;
const int INF = 987654321;

int lst[MAXA][26];
int DP[MAXB][MAXB];

int main()
{
    int T;
    cin >> T;
    while(T--) {
        string A;
        string B;
        cin >> A >> B;
        if(A.size() < B.size()) swap(A, B);
        int N = A.size();
        int M = B.size();
        A = ' ' + A;
        B = ' ' + B;

        for(int i = 0; i < 26; i++) lst[N+2][i] = N+1;
        for(int i = 0; i < 26; i++) lst[N+1][i] = N+1;
        for(int i = N; i >= 1; i--) {
            for(int j = 0; j < 26; j++) {
                lst[i][j] = lst[i+1][j];
            }
            lst[i][A[i]-'a'] = i;
        }

        for(int i = 0; i <= M; i++) for(int j = 0; j <= M; j++) DP[i][j] = N+1;

        int lcs = 0;
        DP[0][0] = 0;
        for(int i = 1; i <= M; i++) {
            for(int j = 0; j <= M; j++) {
                DP[i][j] = DP[i-1][j];
                if(lst[DP[i-1][j-1]+1][B[i]-'a'] < DP[i][j]) {
                    DP[i][j] = lst[DP[i-1][j-1]+1][B[i]-'a'];
                }
                if(DP[i][j] != N+1 && lcs < j) lcs = j;
            }
        }

        cout << lcs << "\n";
        if(lcs == 0) continue;

        int i = M;
        int j = lcs;
        string ans;
        while(j != 0) {
            while(true) {
                if(DP[i][j] != N+1 && lst[DP[i-1][j-1]+1][B[i]-'a'] == DP[i][j]) {
                    ans.push_back(B[i]);
                    i -= 1;
                    j -= 1;
                    break;
                }
                i--;
            }
        }
        reverse(ans.begin(), ans.end());
        cout << ans << "\n";
    }
}