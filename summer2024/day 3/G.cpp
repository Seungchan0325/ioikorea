#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

using ll = long long;

ll N, M, H[MAXN][MAXN], L[MAXN][MAXN], CNT[MAXN][MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> H[i][j];
        }
    }

    for(int j = 1; j <= M; j++) {
        int lst = 1;
        for(int i = 1; i <= N; i++) {
            if(H[lst][j] != H[i][j]) lst = i;
            L[i][j] = i - lst + 1;
        }
    }

    ll sum = 0;
    for(int i = 1; i <= N; i++) {
        ll s = 0;
        deque<int> dq;
        for(int j = 1; j <= M; j++) {
            if(H[i][j] != H[i][j-1]) dq.clear(), s = 0;

            CNT[i][j] = 1;
            while(dq.size() && L[i][dq.back()] >= L[i][j]) {
                s -= L[i][dq.back()] * CNT[i][dq.back()];
                CNT[i][j] += CNT[i][dq.back()];
                dq.pop_back();
            }
            dq.push_back(j);
            s += L[i][j] * CNT[i][j];
            sum += s;
        }
    }

    cout << sum;
}