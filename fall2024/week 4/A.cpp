#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 10;

int N, Q, P[3][MAXN];

int main()
{
    cin >> N >> Q;
    for(int i = 0; i < Q; i++) {
        int l, r, c;
        cin >> l >> r >> c;
        c--;
        P[c][l]++;
        P[c][r+1]--;
    }

    int cnt = 0;
    for(int i = 1; i <= N; i++) {
        P[0][i] += P[0][i-1];
        P[1][i] += P[1][i-1];
        P[2][i] += P[2][i-1];

        if(P[0][i] && P[1][i] && !P[2][i]) cnt++;
    }

    cout << cnt;
}