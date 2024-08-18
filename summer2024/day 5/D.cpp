#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int N, A[MAXN], P[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];

    vector<int> v;
    for(int i = 1; i <= N; i++) {
        if(v.empty() || v.back() < A[i]) {
            P[i] = v.size();
            v.push_back(A[i]);
        } else {
            int idx = lower_bound(v.begin(), v.end(), A[i]) - v.begin();
            P[i] = idx;
            v[idx] = A[i];
        }
    }

    cout << v.size() << "\n";

    vector<int> lis;
    int p = v.size()-1;
    for(int i = N; i >= 1; i--) {
        if(p == P[i]) {
            p--;
            lis.push_back(i);
        }
    }

    reverse(lis.begin(), lis.end());
    for(auto i:lis) cout << i << " ";
}