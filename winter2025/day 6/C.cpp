#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;
    vector<int> small, large;
    for(int i = 0; i < K; i++) {
        int p;
        cin >> p;
        if(p <= 32) small.push_back(p);
        else large.push_back(p);
    }

    vector<bitset<1024>> prime, large_prime;
    for(auto p : small) {
        bitset<1024> bit;
        for(int i = p; i <= N; i+=p) bit.set(i);
        prime.push_back(bit);
    }
    for(auto p : large) {
        bitset<1024> bit;
        for(int i = p; i <= N; i+=p) bit.set(i);
        large_prime.push_back(bit);
    }

    int ans = 0;
    int n = prime.size();
    for(int bit = 0; bit < (1<<n); bit++) {
        bitset<1024> taken;
        for(int i = 0; i < n; i++) {
            if(bit&(1<<i)) taken ^= prime[i];
        }
        for(auto& p : large_prime)
            if(taken.count() < (taken^p).count()) taken ^= p;
        ans = max(ans, (int)taken.count());
    }
    cout << ans;
}