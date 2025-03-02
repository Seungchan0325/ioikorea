#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int MAXK = 1005;

bool vst[MAXN];
int N, K, owner[MAXN];
vector<int> graph[MAXN];

bool dfs(int u)
{
    for(auto v : graph[u]) {
        if(vst[v]) continue;
        vst[v] = true;
        if(owner[v] == -1 || dfs(owner[v])) {
            owner[v] = u;
            return true;
        }
    }
    return false;
}


int main()
{
    cin >> N >> K;
    vector<int> xs;
    for(int i = 1; i <= K; i++) {
        int x, y;
        cin >> x >> y;
        y = y + N;
        xs.push_back(x);
        graph[x].push_back(y);
    }

    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    int cnt = 0;
    memset(owner, -1, sizeof(owner));
    for(auto x : xs) {
        memset(vst, 0, sizeof(vst));
        cnt += dfs(x);
    }

    cout << cnt;
}