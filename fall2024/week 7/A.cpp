#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXC = 1050;
const int MOD = 1e9 +7;

int N, C, x[MAXC];

int main()
{
    cin >> N >> C;
    for(int i = 1; i <= C; i++) {
        cin >> x[i];
    }

    ll ans = 1;

    for(int i = 1; i <= N; i++) {
        bool flag = false;
        int cnt = 0;
        for(int j = 1; j <= C; j++) {
            if(abs(x[j]) == i) flag = true;
            if(x[j] > 0 && i > x[j]) cnt++;
            if(x[j] < 0 && i < -x[j]) cnt++;
        }
        if(!flag) ans = (ans * cnt) % MOD;
    }
    cout << ans;
}