#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 5005;
const ll MOD = 1e9 + 9;

bool chk[MAXN];
ll N, K, A[MAXN], B[MAXN], nCr[MAXN][MAXN];

int main()
{
    cin >> N >> K;
    for(ll i = 1; i <= K; i++) {
        cin >> A[i];
        chk[A[i]] = true;
    }

    nCr[0][0] = 1;
    for(int i = 1; i <= N; i++) {
        nCr[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]) % MOD;
        }
    }

    ll ans = 1;
    for(int i = 1; i <= K; i++) {
        for(int j = A[i-1]+1; j < A[i]; j++) {
            ans += nCr[N-j][K-i];
            ans %= MOD;
        }
    }
    cout << ans << "\n";

    for(int i = K; i > 0; i--) {
        if(A[i]+1 <= N && (i==K || A[i]+1 < A[i+1])) {
            chk[A[i]] = false;
            A[i]++;
            chk[A[i]] = true;
            int lst = A[i];
            for(int j = i + 1; j <= N; j++) {
                A[j] = A[j-1]+1;
            }
            break;
        }
    }

    for(ll i = 1; i <= K; i++) {
        cout << A[i] << " ";
    }
}