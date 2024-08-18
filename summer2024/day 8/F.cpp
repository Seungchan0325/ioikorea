#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, K, A[MAXN], B[MAXN];

bool chk(double L)
{
    vector<double> v;
    for(int i = 1; i <= N; i++) {
        v.emplace_back(A[i] - L * B[i]);
    }
    sort(v.begin(), v.end(), greater<>());
    double sum = 0;
    for(int i = 0; i < N-K; i++) {
        sum += v[i];
    }

    return sum > 0;
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> A[i] >> B[i];

    double lo = 0;
    double hi = 1;
    for(int i = 0; i < 100; i++) {
        double mid = (lo + hi) / 2;
        if(chk(mid)) lo = mid;
        else hi = mid;
    }

    cout << fixed << setprecision(6) << lo;
}