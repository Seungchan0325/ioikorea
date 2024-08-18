#include <bits/stdc++.h>

using namespace std;

int N;

using ll = long long;

const ll MOD = 1234567891;

int main()
{
    cin >> N;
    vector<pair<ll, ll>> vec(N);
    for(auto& [a, b] : vec) cin >> a >> b;
    sort(vec.begin(), vec.end(), [](pair<ll, ll> a, pair<ll, ll> b)
    {
        return b.first * a.second + b.second > a.first * b.second + a.second;
    });

    ll v = 1;
    for(auto [a, b] : vec) {
        v = (a*v + b) % MOD;
    }
    cout << v;
}