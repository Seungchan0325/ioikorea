#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4005;

int DP[MAXN][MAXN];

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    int N = s1.size();
    int M = s2.size();
    s1 = '#' + s1;
    s2 = '#' + s2;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
            if(s1[i] == s2[j]) DP[i][j] = max(DP[i-1][j-1] + 1, DP[i][j]);
        }
    }
    cout << DP[N][M] << "\n";
    if(DP[N][M]) {
        string s;
        int i = N;
        int j = M;
        while(i && j) {
            if(s1[i] == s2[j] && DP[i][j] == DP[i-1][j-1] + 1) {
                s.push_back(s1[i]);
                i--;
                j--;
            } else if(DP[i][j] == DP[i-1][j]) {
                i--;
            } else if(DP[i][j] == DP[i][j-1]) {
                j--;
            }
        }
        reverse(s.begin(), s.end());
        cout << s;
    }
}