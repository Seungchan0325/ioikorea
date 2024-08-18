#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 55;

ll n, k, cache[MAXN][MAXN];

ll dp(int open, int close)
{
    if(close > open) {
        return 1LL<<(n-open-close);
    }
    if(open + close == n) {
        if(open == close) return 0;
        return 1;
    }

    ll& ret = cache[open][close];
    if(ret != -1) return ret;

    ret = dp(open+1, close) + dp(open, close+1);
    return ret;
}

void my_find(int open, int close, ll k)
{
    if(close > open) {
        for(int i = n-open-close-1; i >= 0; i--) {
            if(k&(1LL<<i)) cout << ")";
            else cout << "(";
        }
        return;
    }
    if(open + close == n) return;

    if(k < dp(open+1, close)) {
        cout << "(";
        my_find(open+1, close, k);
    } else {
        cout << ")";
        my_find(open, close+1, k-dp(open+1, close));
    }
}

int main()
{
    cin >> n >> k;

    memset(cache, -1, sizeof(cache));
    if(k >= dp(0, 0)) {
        cout << "-1";
        return 0;
    }

    my_find(0, 0, k);
}