#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

bool visited[MAXN];
int N, mat[MAXN][MAXN], dist[MAXN];

int bfs(int u)
{
    memset(visited, 0, sizeof(visited));
    memset(dist, 0, sizeof(dist));
    queue<int> q;
    q.push(u);
    visited[u] = true;

    while(!q.empty()) {
        auto u = q.front(); q.pop();
        for(int v = 1; v <= N; v++) {
            if(mat[u][v] && !visited[v]) {
                dist[v] = dist[u] + 1;
                q.push(v);
                visited[v] = true;
            }
        }
    }

    if(!visited[1] || !visited[2]) return 1e8;

    return dist[2];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            char c;
            cin >> c;
            if(c == '1') {
                mat[i][j] = 1;
                // cout << i << " " << j << "\n";
            }
        }
    }

    int item = bfs(1) + 1;
    if(item >= 1e8) {
        cout << "-1";
        return 0;
    }

    int day = 0;

    while(true) {
        if(item <= 2) break;
        int nitem = 0;
        while(item - 3 >= 0) {
            nitem += 2;
            item -= 3;
        }
        nitem += item;
        item = nitem;
        day++;
    }

    cout << day;
}