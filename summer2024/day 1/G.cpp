#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

using ll = long long;

int N, A[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    int l = 1;
    int r = 1;
    ll ans = 0;
    ll s, x;
    s = x = A[1];
    while(r <= N) {
        if(x < s) {
            s -= A[l];
            x ^= A[l];
            l++;
        } else {
            ans += r - l + 1;
            r++;
            s += A[r];
            x ^= A[r];
        }
    }

    cout << ans;
}