#include <bits/stdc++.h>

using namespace std;

const int sqrtk = 13;

int f(int idx, vector<vector<bitset<1024>>>& combs, bitset<1024> taken)
{
    if(idx == sqrtk) return taken.count();
    int ret = f(idx+1, combs, taken);
    for(int i = 0; i < combs[idx].size(); i++) {
        ret = max(ret, f(idx+1, combs, taken^combs[idx][i]));
    }
    return ret;
}

int main()
{
    int N, K;
    cin >> N >> K;
    vector<int> small;
    for(int i = 0; i < K; i++) {
        int p;
        cin >> p;
        small.push_back(p);
    }

    vector<vector<bitset<1024>>> bucket(sqrtk);
    for(int i = 0; i < small.size(); i++) {
        bitset<1024> bit;
        for(int j = small[i]; j <= N; j+=small[i]) bit.set(j);
        bucket[i/sqrtk].push_back(bit);
    }

    vector<vector<bitset<1024>>> combs(sqrtk);
    for(int i = 0; i < sqrtk; i++) {
        int n = bucket[i].size();
        assert(n <= sqrtk);
        for(int bit = 0; bit < (1<<n); bit++) {
            bitset<1024> taken;
            for(int j = 0; j < n; j++) {
                if(bit&(1<<j)) taken ^= bucket[i][j];
            }
            combs[i].push_back(taken);
        }
    }

    int ans = f(0, combs, 0);
    cout << ans;
}