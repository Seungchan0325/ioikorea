#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

struct DSU {
    vector<int> root;
    DSU(int n) : root(n)
    {
        iota(root.begin(), root.end(), 0);
    }
    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }
    void merge(int x, int y)
    {
        if(x > y) swap(x, y);
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

vector<int> getPartialMatch(const string& N)
{
    int m = N.size();
    vector<int> pi(m, 0);

    int matched = 0;
    for(int i = 1; i < m; i++) {
        while(matched > 0 && N[i] != N[matched])
            matched = pi[matched - 1];
        
        if(N[i] == N[matched])
            pi[i] = ++matched;
    }
    return pi;
}

ll mul(ll a, ll b)
{
    ll res = a * b;
    if(b == 0 || a > LLONG_MAX/b) return 0;
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll k;
    string s;
    cin >> s;
    cin >> k;

    int n = s.size();
    auto pi = getPartialMatch(s);
    DSU dsu(n);

    for (int i = 1; i < n; i++)
        if(pi[i]-1 >= 0)
            dsu.merge(pi[i]-1, i);

    ll ans = 26;
    vector<ll> v, cnt, step;
    v.push_back(0);
    cnt.push_back(26);
    step.push_back(0);
    for (int i = 1; i < n; i++) {
        if (pi[i] > 0) continue;
        v.push_back(i);
        step.push_back(0);
        set<int> s;
        for (int j = pi[i - 1]; ; j = pi[j - 1]) {
            s.insert(dsu.find(j));
            if (j == 0) break;
        }
        cnt.push_back(26 - (ll)s.size());
        ans *= 26 - (ll)s.size();
        ans %= MOD;
    }
    cout << ans << "\n";

    cnt.push_back(1);
    for(int i = v.size()-1; i >= 0; i--) {
        cnt[i] = mul(cnt[i], cnt[i+1]);
    }

    if(cnt[0] != 0 && cnt[0] < k) {
        cout << "OVER\n";
        return 0;
    }
    k--;
    for(int i = 0; i < v.size(); i++) {
        if(cnt[i+1] == 0) continue;
        step[i] = k / cnt[i+1];
        k -= step[i] * cnt[i+1];
    }

    string str(n, 'a');
    for(int i = 0; i < v.size(); i++) {
        int j = v[i];
        bool used[26] = {};
        if(j > 0) {
            for(int k = pi[j-1]; ; k = pi[k - 1]) {
                used[str[dsu.find(k)] - 'a'] = true;
                if(k == 0) break;
            }
        }
        for(int alphabet = 'a'; alphabet <= 'z'; alphabet++) {
            if(used[alphabet-'a']) continue;
            if(step[i] == 0) {
                str[j] = alphabet;
                break;
            }
            step[i]--;
        }
    }
    for(int i = 0; i < n; i++) {
        str[i] = str[dsu.find(i)];
    }
    cout << str;
}