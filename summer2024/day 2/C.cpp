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

ll pw(ll A, ll B, ll M)
{
    if(B == 0) return 1;
    if(B & 1) return (mul(pw(A, B-1, M), A, M));
    ll half = pw(A, B/2, M);
    return mul(half, half, M) % M;
}

int main()
{
    ll a, b, M;
    cin >> a >> b >> M;
    cout << pw(a, b, M);
}