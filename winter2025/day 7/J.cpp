#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100505;

bool vst[MAXN];
int N, M, S, P, cash[MAXN];
vector<int> graph[MAXN];
vector<pair<int, int>> edges;

int root[MAXN];

int find(int x)
{
    if(x == root[x]) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;

    root[y] = x;
    cash[x] = min(cash[x], cash[y]);
}

bool inStack[MAXN];
int pv, num[MAXN], low[MAXN];
stack<int> s;

void dfs(int u)
{
    num[u] = low[u] = ++pv;
    s.push(u);
    inStack[u] = true;

    for(auto v : graph[u]) {
        if(!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(inStack[v]) {
            low[u] = min(low[u], low[v]);
        }
    }

    if(num[u] == low[u]) {
        while(s.top() != u) {
            merge(u, s.top());
            inStack[s.top()] = false;
            s.pop();
        }

        s.pop();
        inStack[u] = false;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    edges.resize(M);
    for(int i = 1; i <= N; i++) cin >> cash[i];
    for(auto& [u, v] : edges) {
        cin >> u >> v;
        graph[u].push_back(v);
    }

    iota(root, root + N + 1, 0);
    dfs(1);

    long long ans = 0;
    for(int i = 1; i <= N; i++) {
        int j = find(i);
        if(vst[j]) continue;
        vst[j] = true;
        ans += cash[j];
    }
    cout << ans;
}