#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 500005;

ll N, a[MAXN], b[MAXN], deg[MAXN], root[MAXN], sum[MAXN], node[MAXN], edge[MAXN];

ll find(ll x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(ll x, ll y)
{
    x = find(x);
    y = find(y);

    edge[x]++;

    if(x == y) return;

    if(x < y) swap(x, y);
    root[y] = x;
    sum[x] += sum[y];
    node[x] += node[y];
    edge[x] += edge[y];
}

int main()
{
    cin >> N;
    vector<ll> vec;
    ll ans = 0;
    for(ll i = 1; i <= N; i++) {
        cin >> a[i] >> b[i];
        ans += a[i] + b[i];
        vec.push_back(a[i]);
        vec.push_back(b[i]);
    }
    
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());

    for(ll i = 0; i < vec.size(); i++) {
        root[i] = i;
        sum[i] = vec[i];
        node[i] = 1;
        edge[i] = 0;
    }

    for(ll i = 1; i <= N; i++) {
        ll u = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin();
        ll v = lower_bound(vec.begin(), vec.end(), b[i]) - vec.begin();
        merge(u, v);
    }

    for(ll i = 0; i < vec.size(); i++) {
        if(find(i) == i) {
            if(node[i] == edge[i]) ans -= sum[i];
            else ans -= sum[i] - vec[i];
        }
    }

    cout << ans;
}