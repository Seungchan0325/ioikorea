#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 5050;
const int MOD = 1e9 + 7;

int N, X, W[MAXN], S[MAXN], L[MAXN], R[MAXN];

int main()
{
    cin >> N >> X;
    for(int i = 1; i <= N; i++) cin >> W[i];

    vector<int> v;
    for(int i = 1; i <= N; i++) {
        if(2*W[i] > X) {
            S[i]++;
            continue;
        }
        int l = i;
        while(l >= 1 && W[i] + W[l] <= X) {
            l--;
        }
        int r = i;
        while(r <= N && W[i] + W[r] <= X) {
            r++;
        }

        L[i] = l+1;
        R[i] = r-1;
        v.push_back(i);
    }
    sort(v.begin(), v.end(), [](int a, int b)
    {
        return R[a] - L[a] < R[b] - L[b];
    });

    int ans = 1;
    for(int i : v) {
        int s = 1;
        for(int j = L[i]; j <= R[i]; j++) {
            s += S[j];
        }
        ans = (ll)ans * s % MOD;
        S[i]++;
    }

    cout << ans;
}