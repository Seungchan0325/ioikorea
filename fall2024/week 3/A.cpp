#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ll A1, A2, A3;
    cin >> A1 >> A2 >> A3;
    if(2*A2 > A1 + A3) cout << 2*A2 - A1 - A3 << "\n";
    else cout << (A1 + A3 + 1) / 2 - A2 + (A1 + A3) % 2 << "\n";
}