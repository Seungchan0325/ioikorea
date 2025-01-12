#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

int N, M, R[MAXN][MAXN], cache[MAXN][MAXN][MAXN][MAXN];

int query(int t, int b, int l, int r)
{
    return R[b][r] - R[t-1][r] - R[b][l-1] + R[t-1][l-1];
}

int DP(int t, int b, int l, int r)
{
    if(t == b && l == r) return 0;
    int& ret = cache[t][b][l][r];
    if(ret != -1) return ret;

    ret = 1e9;
    for(int i = t; i < b; i++) {
        ret = min(ret, DP(t, i, l, r) + DP(i+1, b, l, r) + query(t, b, l, r));
    }
    for(int i = l; i < r; i++) {
        ret = min(ret, DP(t, b, l, i) + DP(t, b, i+1, r) + query(t, b, l, r));
    }
    return ret;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> R[i][j];
            R[i][j] = R[i][j] + R[i-1][j] + R[i][j-1] - R[i-1][j-1];
        }
    }
    memset(cache, -1, sizeof(cache));
    int result = DP(1, N, 1, M);
    cout << result;
}