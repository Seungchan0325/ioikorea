#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, Q, root[MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    root[y] = x;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    iota(root, root + N + 1, 0);
    while(Q--) {
        int op, i, j;
        cin >> op >> i >> j;
        if(op == 0) {
            merge(i, j);
        } else {
            i = find(i);
            j = find(j);
            if(i == j) cout << "1\n";
            else cout << "0\n";
        }
    }
}