#include <bits/stdc++.h>

using namespace std;

const int MAXN = 14;

int N, ans, d[MAXN], nPr[9*MAXN+1][MAXN];

int main()
{
    cin >> N;
    int sum = 0;
    for(int i = 0; i < N; i++) {
        char c;
        cin >> c;
        d[i] = c-'0';
        sum += d[i];
    }

    nPr[0][0] = 1;
    for(int i = 1; i <= sum; i++) {
        for(int j = 1; j <= N; j++) {
            for(int k = 0; k < 10 && k <= i; k++) {
                nPr[i][j] += nPr[i-k][j-1];
            }
        }
    }
    for(int i = 0; i < sum; i++) {
        ans += nPr[i][N];
    }
}