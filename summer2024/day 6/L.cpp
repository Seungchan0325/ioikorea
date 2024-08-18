#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;
const int INF = 1e9;

int chk[MAXN], dist[MAXN];

int main()
{
    int n;
    cin >> n;

    deque<pair<int, int>> dq;
    dq.emplace_back(1, 1);
    dist[1] = 1;
    for(int i = 0; i <= n; i++) dist[i] = INF;

    while(!dq.empty()) {
        auto [d, r] = dq.front(); dq.pop_front();

        if(d > dist[r]) continue;

        if(d < dist[10*r%n]) {
            dist[10*r%n] = d;
            dq.emplace_front(d, 10*r%n);
        }
        if(d+1 < dist[(r+1)%n]) {
            dist[(r+1)%n] = d+1;
            dq.emplace_back(d+1, (r+1)%n);
        }
    }

    cout << dist[0];
}