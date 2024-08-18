#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 5;

int N, M, Z[MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= M; i++) cin >> Z[i];

    set<int> s;
    for(int i = 1; i <= N; i++) s.insert(i);
    int cnt = 0;
    for(int i = 1; i <= M; i++) {
        auto it = s.upper_bound(Z[i]);
        if(it == s.begin()) break;
        it--;
        s.erase(it);
        cnt++;
    }
    cout << cnt;
}