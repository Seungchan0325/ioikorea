#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int N, M, cache[MAXN][3][3];
string S;

int f(int n, int a, int b)
{
    if(a > 2 || b > 2) return 0;
    if(n == 0) {
        // if(a != 0 || b != 0) return 0;
        return 1;
    }
    int& ret = cache[n][a][b];
    if(ret != -1) return ret;

    ret = f(n-1, a+1, max(b-1, 0)) + f(n-1, max(a-1, 0), b+1);
    ret %= M;
    return ret;
}

void g(int n, int a, int b, string s, string ss)
{
    if(a > 2 || b > 2) return;
    if(n == 0) {
        // if(a != 0 || b != 0) return;
        cout << ss+s << "\n";
        return;
    }

    g(n-1, max(a-1, 0), b+1, s+'M', ss);
    g(n-1, a+1, max(b-1, 0), s+'R', ss);
}

int main()
{
    cin >> N >> M >> S;
    S = ' ' + S;

    memset(cache, -1, sizeof(cache));

    int ans = 1;
    int cntR = 0, cntM = 0;
    for(int i = 1; i <= N; i++) {   
        if(S[i] == 'R') {
            ans = (ans + f(N-i, max(cntR - 1, 0), cntM + 1)) % M;
            // g(N-i, max(cntR - 1, 0), cntM + 1, "", S.substr(1, i-1)+'M');
            cntR++;
            cntM = max(cntM-1, 0);
        } else {
            cntR = max(cntR-1, 0);
            cntM++;
        }
    }
    cout << ans;
}