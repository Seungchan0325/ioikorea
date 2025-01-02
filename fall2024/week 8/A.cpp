#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int N;

int main()
{
    cin >> N;
    vector<int> v(3*N);
    for(int i = 0; i < 3*N; i++) cin >> v[i];
    sort(v.begin(), v.end());
    ll ans = 0;
    for(int i = N; i < 3*N; i+=2) ans += v[i];
    cout << ans;
}