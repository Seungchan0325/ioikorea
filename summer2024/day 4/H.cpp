#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> v(N, vector<int>(5));
    for(auto& i : v) {
        for(int j = 0; j < 5; j++) {
            cin >> i[j];
        }
        sort(i.begin(), i.end());
    }

    map<vector<int>, int> m;

    long long ans = 0;
    for(int k = 0; k < N; k++) {
        auto i = v[k];
        long long sum = 0;
        for(int bit = 1; bit < (1<<5); bit++) {
            vector<int> t;
            for(int j = 0; j < 5; j++) {
                if(bit&(1<<j)) {
                    t.push_back(i[j]);
                }
            }

            int popcnt = __builtin_popcount(bit);
            if(popcnt&1) sum += m[t];
            else sum -= m[t];

            m[t]++;
        }
        ans += k - sum;
    }
    cout << ans;
}