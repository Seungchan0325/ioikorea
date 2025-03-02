#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T;
    cin >> T;
    int correct = 0;
    int wrong = 0;
    while(T--) {
        int N;
        cin >> N;
        vector<int> a(N);
        for(auto& i : a) cin >> i;
        int ans = 0;
        int cnt1 = 0;
        for(int i = 0; i < N; i++) {
            if(a[i] >= i && a[i] - i <= 450) cnt1++;
        }
        if(cnt1 >= 370) ans = 2;
        else ans = 1;
        cout << ans << "\n";

        if(T > 500) {
            if(ans == 1) correct++;
            else wrong++;
        } else {
            if(ans == 1) wrong++;
            else correct++;
        }
    }
    // cout << correct << "\n" << wrong << "\n";
}