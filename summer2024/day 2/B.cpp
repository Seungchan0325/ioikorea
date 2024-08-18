#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll mul(ll A, ll B, ll M)
{
    if(B == 0) return 0;
    if(B & 1) return (mul(A, B-1, M) + A) % M;
    ll half = mul(A, B/2, M);
    return (half + half) % M;
}

int main()
{
    ll A, B, M;
    cin >> A >> B >> M;
    cout << mul(A, B, M);
}