#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int ans = 0;
    if(n&1) ans = 2*(max((n-1)/2, 0)/3) + 1;
    else ans = 2*(max((n-2)/2, 0)/3) + 2;
    cout << ans << " " << n;
}