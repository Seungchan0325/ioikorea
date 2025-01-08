#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 2050;

int N, Q;
ll tree[MAXN][MAXN];

void update(int x, int y, int d)
{
    for(int i = x; i <= N; i+=i&-i)
        for(int j = y; j <= N; j+=j&-j)
            tree[i][j] += d;
}

ll query(int x, int y)
{
    ll ret = 0;
    for(int i = x; i > 0; i-=i&-i)
        for(int j = y; j > 0; j-=j&-j)
            ret += tree[i][j];
    return ret;
}

int main()
{
    cin >> N >> Q;
    while(Q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int x, y, v;
            cin >> x >> y >> v;
            update(x, y, v);
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            ll result = query(x2, y2) - query(x1-1, y2) - query(x2, y1-1) + query(x1-1, y1-1);
            cout << result << "\n";
        }
    }
}