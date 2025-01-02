#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

bool vst[2*MAXN];
int N, A[MAXN], B[MAXN], parent[2*MAXN], cnt[2*MAXN], sum[2*MAXN];

int find(int x)
{
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    parent[y] = x;
    cnt[x] += cnt[y];
    sum[x] += sum[y];
}

int main()
{
    cin >> N;
    for(int i = 1; i <= 2*N; i++) {
        parent[i] = i;
        cnt[i] = 1;
        sum[i] = 0;
    }
    for(int i = 1; i <= N; i++) {
        cin >> A[i] >> B[i];
        merge(A[i], B[i]);
        sum[find(A[i])]++;
    }

    int ans = 0;
    for(int i = 1; i <= 2*N; i++) {
        int u = find(i);
        if(vst[u]) continue;
        ans += min(cnt[u], sum[u]);
        vst[u] = true;
    }

    cout << ans;
}