#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;
const int MAXK = 9;

int N, K, A[MAXN][MAXK];
bitset<MAXN> bit[MAXK][4];
int mx = -1e9, mn = 1e9;

void f(int idx, bitset<MAXN> taken)
{
    if(idx == K) {
        mx = max(mx, N-(int)taken.count());
        mn = min(mn, N-(int)taken.count());
        return;
    }
    for(int i = 1; i <= 3; i++) {
        f(idx+1, taken | bit[idx][i]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < K; j++) {
            cin >> A[i][j];
            bit[j][A[i][j]].set(i);
        }
    }
    f(0, 0);
    cout << mn << " " << mx << "\n";
}