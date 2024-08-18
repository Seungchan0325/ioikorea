#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

int N, L[MAXN], R[MAXN], deg[MAXN];

void preorder(int u)
{
    if(u == 0) return;
    cout << u << " ";
    preorder(L[u]);
    preorder(R[u]);
}

void inorder(int u)
{
    if(u == 0) return;
    inorder(L[u]);
    cout << u << " ";
    inorder(R[u]);
}

void postorder(int u)
{
    if(u == 0) return;
    postorder(L[u]);
    postorder(R[u]);
    cout << u << " ";
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> L[i] >> R[i];
        deg[L[i]]++;
        deg[R[i]]++;
    }
    int root = -1;
    for(int i = 1; i <= N; i++) {
        if(deg[i] == 0) root = i;
    }
    preorder(root);
    cout << "\n";
    inorder(root);
    cout << "\n";
    postorder(root);
}