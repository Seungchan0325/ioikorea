#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXH = 505;

int H, W, a, b;
ll c[MAXH][MAXH];

ll qry(int top, int bottom, int left, int right)
{
    return c[bottom][right] - c[top - 1][right] - c[bottom][left - 1] + c[top - 1][left - 1];
}

ll compute(int top, int bottom, int left, int right)
{
    ll s = qry(top, bottom, left, right);
    return abs(s - a) + abs(s - b);
}

int main()
{
    cin >> H >> W >> a >> b;

    for(int i = 1; i <= H; i++) {
        for(int j = 1; j <= W; j++) {
            cin >> c[i][j];
        }
    }

    for(int i = 1; i <= H; i++) {
        for(int j = 1; j <= W; j++) {
            c[i][j] += c[i-1][j] + c[i][j-1] - c[i-1][j-1];
        }
    }

    ll ans = 1e18;

    for(int top = 1; top <= H; top++) {
        for(int bottom = top; bottom <= H; bottom++) {
            int left = 1;
            for(int right = 1; right <= W; right++) {
                while(left < W && compute(top, bottom, left + 1, right) < compute(top, bottom, left, right)) {
                    left++;
                }
                ans = min(ans, compute(top, bottom, left, right));
            }
        }
    }
    cout << ans;
}