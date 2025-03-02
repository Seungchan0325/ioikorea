#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100505;

int N, M;
vector<int> graph[2*MAXN];

bool inStack[2*MAXN];
int pv, num[2*MAXN], low[2*MAXN], scc[2*MAXN], t;
stack<int> s;

void dfs(int u)
{
    num[u] = low[u] = ++pv;
    inStack[u] = true;
    s.push(u);

    for(auto v : graph[u]) {
        if(!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(inStack[v]) {
            low[u] = min(low[u], low[v]);
        }
    }

    if(num[u] == low[u]) {
        t++;
        while(s.top() != u) {
            scc[s.top()] = t;
            inStack[s.top()] = false;
            s.pop();
        }

        scc[u] = t;
        inStack[u] = false;
        s.pop();
    }
}
int main()
{
    while(cin >> N >> M) {
        for(int i = 0; i <= 2 * N+1; i++) {
            graph[i].clear();
            num[i] = 0;
            scc[i] = 0;
            inStack[i] = false;
            low[i] = 0;
            t = 0;
            pv = 0;
            while(s.size()) s.pop();
        }
        graph[3].push_back(2);
        for(int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            if(u < 0) u = 2*-u + 1;
            else u = 2*u;

            if(v < 0) v = 2*-v + 1;
            else v = 2*v;

            graph[u^1].push_back(v);
            graph[v^1].push_back(u);
        }

        for(int i = 2; i <= 2*N+1; i++) {
            if(!num[i]) dfs(i);
        }

        bool is_satisfied = true;
        for(int i = 1; i <= N; i++) {
            if(scc[2*i] == scc[2*i+1]) {
                is_satisfied = false;
                break;
            }
        }

        if(is_satisfied) cout << "yes\n";
        else cout << "no\n";
    }
}