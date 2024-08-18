#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200200;

int N, dist[MAXN][2], X[MAXN], Y[MAXN];
int graph[MAXN][2][2];

int main()
{
    cin >> N >> X[0] >> Y[0] >> X[1] >> Y[1];
    for(int i = 2; i < N+2; i++) cin >> X[i] >> Y[i];

    vector<int> xs, ys;
    for(int i = 0; i < N+2; i++) {
        xs.push_back(X[i]);
        ys.push_back(Y[i]);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    vector<vector<pair<int, int>>> vx(xs.size()), vy(ys.size());
    for(int i = 0; i < N+2; i++) {
        int x = lower_bound(xs.begin(), xs.end(), X[i]) - xs.begin();
        int y = lower_bound(ys.begin(), ys.end(), Y[i]) - ys.begin();
        vx[x].emplace_back(y, i);
        vy[y].emplace_back(x, i);
    }
    for(auto& i : vx) sort(i.begin(), i.end());
    for(auto& i : vy) sort(i.begin(), i.end());

    memset(graph, -1, sizeof(graph));

    for(int i = 0; i < N+2; i++) {
        int x = lower_bound(xs.begin(), xs.end(), X[i]) - xs.begin();
        int y = lower_bound(ys.begin(), ys.end(), Y[i]) - ys.begin();

        auto idx = lower_bound(vx[x].begin(), vx[x].end(), pair(y, i)) - vx[x].begin();
        if(idx - 1 >= 0) graph[i][0][0] = vx[x][idx-1].second;
        if(idx + 1 < vx[x].size()) graph[i][0][1] = vx[x][idx+1].second;

        idx = lower_bound(vy[y].begin(), vy[y].end(), pair(x, i)) - vy[y].begin();
        if(idx - 1 >= 0) graph[i][1][0] = vy[y][idx-1].second;
        if(idx + 1 < vy[y].size()) graph[i][1][1] = vy[y][idx+1].second;
    }

    memset(dist, 0x7F, sizeof(dist));

    deque<tuple<int, int, int>> dq;
    dq.emplace_back(0, 0, 0);
    dq.emplace_back(0, 0, 1);

    while(!dq.empty()) {
        auto [d, u, dir] = dq.front(); dq.pop_front();
        if(d > dist[u][dir]) continue;

        for(int i = 0; i < 2; i++) {
            if(graph[u][dir][i] == -1) continue;
            int nd = d;
            int v = graph[u][dir][i];
            if(nd < dist[v][dir]) {
                dist[v][dir] = nd;
                dq.emplace_front(nd, v, dir);
            }
        }

        for(int i = 0; i < 2; i++) {
            if(graph[u][dir^1][i] == -1) continue;
            int nd = d + 1;
            int v = graph[u][dir^1][i];
            if(nd < dist[v][dir^1]) {
                dist[v][dir^1] = nd;
                dq.emplace_back(nd, v, dir^1);
            }
        }
    }

    int d = min(dist[1][0], dist[1][1]);
    if(d > N+2) cout << "-1";
    else cout << d;
}