#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101;
const int MAXS = 101;
const int MOD = 993244853;

int N, S, A[4][MAXN];

int chk(int i, int j, int k, int x, int y, int z)
{
    int a, b, c;
    for(int n = 3; n <= N; n++) {
        a = S - y - k;
        c = S - y - i;
        b = S - a - c;
        if(a < 0 || b < 0 || c < 0) return 0;
        if(A[1][n] != -1 && A[1][n] != a) return 0;
        if(A[2][n] != -1 && A[2][n] != b) return 0;
        if(A[3][n] != -1 && A[3][n] != c) return 0;
        tie(i, j, k) = tie(x, y, z);
        tie(x, y, z) = tie(a, b, c);
    }
    return 1;
}

int main()
{
    cin >> N >> S;
    for(int j = 1; j <= 3; j++) {
        for(int i = 1; i <= N; i++) {
            cin >> A[j][i];
        }
    }
    if(N == 1) {
        long long cnt = 0;
        for(int i = 0; i <= S; i++) {
            if(A[1][1] != -1 && A[1][1] != i) continue;
            for(int j = 0; i + j <= S; j++) {
                int k = S - i - j;
                if(A[2][1] != -1 && A[2][1] != j) continue;
                if(A[3][1] != -1 && A[3][1] != k) continue;
                cnt++;
            }
        }
        cout << cnt;
        return 0;
    }
    long long cnt = 0;
    for(int i = 0; i <= S; i++) {
        if(A[1][1] != -1 && A[1][1] != i) continue;
        for(int k = 0; i+k <= S; k++) {
            int j = S - i - k;
            if(A[2][1] != -1 && A[2][1] != j) continue;
            if(A[3][1] != -1 && A[3][1] != k) continue;
            for(int x = 0; x <= S; x++) {
                if(A[1][2] != -1 && A[1][2] != x) continue;
                for(int y = 0; x+y <= S && i+y <= S && k+y <= S; y++) {
                    int z = S - x - y;
                    if(A[2][2] != -1 && A[2][2] != y) continue;
                    if(A[3][2] != -1 && A[3][2] != z) continue;
                    cnt += chk(i, j, k, x, y, z);
                }
            }
        }
    }
    cout << cnt % MOD;
}