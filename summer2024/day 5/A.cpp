#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        vector<int> v(N);
        for(auto& i : v) cin >> i;

        int ans = 0;
        int sum = 0;
        for(auto i : v) {
            if(sum < 0) sum = 0;
            sum += i;
            ans = max(ans, sum);
        }

        cout << ans << "\n";
    }
}