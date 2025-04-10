#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ll n;
    cin >> n;
    vector<pair<ll, ll>> v;
    vector<ll> fi;
    for(ll i = 0; i < n; i++) {
        ll a;
        cin >> a;
        v.emplace_back(a, i);
        fi.push_back(a);
    }
    sort(fi.begin(), fi.end());
    sort(v.begin(), v.end());
    vector<ll> s(n);
    for(ll i = 0; i < n; i++) {
        s[i] = fi[i];
    }
    for(ll i = 1; i < n; i++) s[i] += s[i-1];
    string ans(n, '#');
    ll mx = v[n-1].first;
    for(ll i = n-1; i >= 0; i--) {
        ll idx = lower_bound(fi.begin(), fi.end(), v[i].first) - fi.begin();
        if(idx != 0 && s[i] > mx) ans[v[i].second] = 'T';
        else ans[v[i].second] = 'N';
        mx = max(v[i].first, mx - v[i].first);
    }
    cout << ans;
}