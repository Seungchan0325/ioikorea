#include <bits/stdc++.h>

using namespace std;

using ll = long long;

long long N, fibo[55];

int main()
{
    cin >> N;
    fibo[1] = 1;
    for(int i = 2; i <= N; i++) {
        fibo[i] = fibo[i-1] + fibo[i-2];
    }
    cout << fibo[N];
}