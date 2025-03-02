#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll N, ans;
string S;

string B, R;
map<pair<string, string>, ll> m;

void f(ll idx)
{
    if(idx == N) {
        reverse(B.begin(), B.end());
        reverse(R.begin(), R.end());
        m[{B, R}]++;
        reverse(B.begin(), B.end());
        reverse(R.begin(), R.end());
        return;
    }
    B += S[idx];
    f(idx+1);
    B.pop_back();
    R += S[idx];
    f(idx+1);
    R.pop_back();
}

void g(ll idx)
{
    if(idx == 2*N) {
        ans += m[{B, R}];
        return;
    }
    B += S[idx];
    g(idx+1);
    B.pop_back();
    R += S[idx];
    g(idx+1);
    R.pop_back();
}

int main()
{
    cin >> N;
    cin >> S;
    f(0);
    g(N);
    cout << ans;
}