#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1000005;

ll N, M, H[MAXN];

ll cut(int h)
{
    ll ret = 0;
    for(int i = 1; i <= N; i++) {
        ret += max(0LL, H[i] - h);
    }
    return ret;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) cin >> H[i];
    sort(H + 1, H + N + 1);

    ll lo = -1;
    ll hi = H[N];
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(cut(mid) >= M) lo = mid;
        else hi = mid;
    }
    cout << lo;
}