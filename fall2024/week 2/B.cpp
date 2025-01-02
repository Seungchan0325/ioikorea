#include <bits/stdc++.h>

using namespace std;

int N, H;

int main()
{
    cin >> N >> H;
    int cnt = 0, ans = 0;
    for(int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        if(c == '(') {
            if(cnt >= H) {
                ans++;
                cnt--;
            } else {
                cnt++;
            }
        } else {
            if(cnt == 0) {
                ans++;
                cnt++;
            } else {
                cnt--;
            }
        }
    }

    cout << ans;
}