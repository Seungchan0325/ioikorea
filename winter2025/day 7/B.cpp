#include <bits/stdc++.h>

using namespace std;

const int MAXK = 10050;

int K, N, ans[MAXK];
vector<int> graph[MAXK];
bool inStack[MAXK];
int pv, num[MAXK], low[MAXK], scc[MAXK], t;
stack<int> s;

int Not(int u)
{
    return u^1;
}

void add_edge(int u, int v)
{
    graph[Not(u)].push_back(v);
    graph[Not(v)].push_back(u);
}

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
    cin >> K >> N;
    for(int i = 0; i < N; i++) {
        int v1, v2, v3;
        char c1, c2, c3;
        cin >> v1 >> c1 >> v2 >> c2 >> v3 >> c3;
        v1 *= 2;
        v2 *= 2;
        v3 *= 2;
        if(c1 == 'R') v1 = Not(v1);
        if(c2 == 'R') v2 = Not(v2);
        if(c3 == 'R') v3 = Not(v3);
        add_edge(v1, v2);
        add_edge(v2, v3);
        add_edge(v1, v3);
    }

    for(int i = 1; i <= K; i++) {
        if(!num[2*i]) dfs(2*i);
        if(!num[Not(2*i)]) dfs(Not(2*i));
    }

    bool is_satisfied = true;
    for(int i = 1; i <= K; i++) {
        if(scc[2*i] == scc[Not(2*i)]) {
            is_satisfied = false;
            break;
        }
    }

    if(!is_satisfied) {
        cout << "-1";
        return 0;
    }

    memset(ans, -1, sizeof(ans));
    vector<pair<int, int>> v;
    for(int i = 2; i <= 2*K+1; i++) {
        v.emplace_back(-scc[i], i);
    }
    sort(v.begin(), v.end());
    for(auto [scc, idx] : v) {
        if(ans[idx/2] < 0) {
            ans[idx/2] = idx&1;
        }
    }
    for(int i = 1; i <= K; i++) {
        if(!ans[i]) cout << "R";
        else cout << "B";
    }
}