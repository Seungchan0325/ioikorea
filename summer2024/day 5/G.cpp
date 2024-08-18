#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1005;

ll N, X[MAXN], Y[MAXN];
double DP[MAXN][MAXN];
double cache[MAXN][MAXN], table[MAXN][MAXN];

double dist(ll i, ll j)
{
    return sqrt((X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]));
}

double dp(ll i, ll j)
{
    if(i+1 == N) {
        return table[i][N] + table[j][N];
    }

    double ret = cache[i][j];
    if(ret != INFINITY) return ret;

    ret = min(dp(i+1, j)+table[i][i+1], dp(i+1, i)+table[j][i+1]);
    return ret;
}

int main()
{
    cin >> N;
    for(ll i = 1; i <= N; i++) {
        cin >> X[i] >> Y[i];
    }

    for(int i = 1; i <= N; i++) {
        for(int j = i+1; j <= N; j++) {
            table[i][j] = table[j][i] = dist(i, j);
        }
    }

    // for(ll i = 0; i < MAXN; i++) for(ll j = 0; j < MAXN; j++) cache[i][j] = INFINITY;
    // double result = dp(1, 1);
    // printf("%.8f\n", result);

    for(int j = 1; j < N; j++) DP[N-1][j] = dist(N-1, N) + dist(j, N);
    
    for(int i = N-2; i >= 1; i--) {
        for(int j = 1; j <= i; j++) {
            DP[i][j] = min(DP[i+1][j] + table[i][i+1], DP[i+1][i]+table[j][i+1]);
        }
    }

    printf("%.8f", DP[1][1]);
}