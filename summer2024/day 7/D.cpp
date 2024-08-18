#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int N, preorder[MAXN], inorder[MAXN], rinorder[MAXN], L[MAXN], R[MAXN];

void build(int& idx, int lo, int hi)
{
    if(lo > hi) return;
    if(lo == hi) {
        idx++;
        cout << inorder[lo] << " ";
        return;
    }
    int u = preorder[idx];
    int m = rinorder[u];
    idx++;
    build(idx, lo, m-1);
    build(idx, m+1, hi);
    cout << u << " ";
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> preorder[i];
    for(int i = 1; i <= N; i++) {
        cin >> inorder[i];
        rinorder[inorder[i]] = i;
    }

    int idx = 1;
    build(idx, 1, N);
}