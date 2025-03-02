#include <bits/stdc++.h>

using namespace std;

const int MAXN = 45;

bool vst[MAXN];
int N, M, C[MAXN];
vector<int> graph[MAXN];
int ans = 1e9;
int sum = 0;

void dfs(int u)
{
    vector<int> arr;
    for(auto v : graph[u]) {
        if(vst[v]) continue;
        sum += C[v];
        vst[v] = true;
        arr.push_back(v);
    }
    if(u == N) {
        ans = min(ans, sum);
    } else {
        for(auto v : arr) {
            dfs(v);
        }
    }
    for(auto v : arr) {
        vst[v] = false;
        sum -= C[v];
    }
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) cin >> C[i];
    for(int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    sum = C[1];
    vst[1] = true;
    dfs(1);
    cout << ans;
}