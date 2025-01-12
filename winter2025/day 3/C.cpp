#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;
const int MOD = 10007;

int N, nxt[MAXN][26], cache[MAXN];

int dp(int n)
{
    if(n == N) return 1;
    int& ret = cache[n];
    if(ret != -1) return ret;

    ret = 1;
    for(int i = 0; i < 26; i++) {
        ret = (ret + dp(nxt[n][i])) % MOD;
    }
    return ret;
}

int main()
{
    string s;
    cin >> s;
    N = s.size();
    s = "#" + s;
    
    for(int i = 0; i < 26; i++) nxt[N][i] = -1;
    for(int i = N-1; i >= 0; i--) {
        memcpy(nxt[i], nxt[i+1], sizeof(nxt[0]));
        nxt[i][s[i+1]-'a'] = i+1;
    }

    memset(cache, -1, sizeof(cache));
    int result = (dp(0) - 1 + MOD) % MOD;
    cout << result;
}