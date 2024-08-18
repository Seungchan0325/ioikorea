#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int N, A[MAXN], tree[4*MAXN];

void update(int x, int v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx] = v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    if(A[tree[2*idx]] < A[tree[2*idx+1]]) tree[idx] = tree[2*idx];
    else tree[idx] = tree[2*idx+1];
}

int main()
{
    A[0] = INT_MAX;
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    for(int i = 1; i <= N; i++) update(i, i);

    for(int i = 1; i <= N; i++) {
        cout << A[tree[1]] << " ";
        update(tree[1], 0);
    }
}