#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

using ll = long long;

ll N, Q, A[MAXN], PSUM[MAXN];

int main()
{
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) cin >> A[i];
    sort(A+1, A+N+1);
    PSUM[1] = A[1];
    for(int i = 2; i <= N; i++) {
        PSUM[i] = PSUM[i-1] + A[i];
    }

    while(Q--) {
        ll l, r;
        cin >> l >> r;
        if(r < l) {
            cout << "0 0\n";
            continue;
        }
        l = lower_bound(A+1, A+N+1, l) - A;
        r = upper_bound(A+1, A+N+1, r) - A;
        cout << r - l << " " << PSUM[r-1] - PSUM[l-1] << "\n";
    }
}