#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int N, M;
char A[MAXN][MAXN];
bool inStack[8*MAXN*MAXN];
int scc[8*MAXN*MAXN], num[8*MAXN*MAXN], low[8*MAXN*MAXN], pv, t;
vector<int> tkn[MAXN][MAXN];
vector<int> g[8*MAXN*MAXN];
stack<int> s;

int depth;
void dfs(int u)
{
    depth++;
    num[u] = low[u] = ++pv;
    inStack[u] = true;
    s.push(u);
    
    for(auto v : g[u]) {
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
        scc[s.top()] = t;
        inStack[s.top()] = false;
        s.pop();
    }
}

int L(int i)
{
    return i<<3;
}
int R(int i)
{
    return i<<3|2;
}
int U(int i)
{
    return i<<3|4;
}
int D(int i)
{
    return i<<3|6;
}
int NOT(int i)
{
    return i^1;
}
void add(int i, int j)
{
    g[NOT(i)].push_back(j);
    g[NOT(j)].push_back(i);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int T;
    cin >> T;
    while(T--) {
        cin >> N >> M;
        int b, w;
        b = w = 0;
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                cin >> A[i][j];
                if(A[i][j] == 'W') w++;
                if(A[i][j] == 'B') b++;
            }
        }

        if(2*b != w) {
            cout << "NO\n";
            goto DONE;
        }
        b = 0;
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                if(A[i][j] == 'B') {
                    for(int k = 0; k < 4; k++) {
                        int ni = i + dy[k];
                        int nj = j + dx[k];
                        if(ni < 1 || ni > N || nj < 1 || nj > M || A[ni][nj] != 'W') continue;
                        for(int other : tkn[ni][nj]) {
                            // add(L(b)+2*k, other);
                            add(NOT(L(b)+2*k), NOT(other)); 
                        }
                        tkn[ni][nj].push_back(L(b)+2*k);
                    }
                    if(A[i-1][j] == 'W' && A[i+1][j] == 'W') add(NOT(U(b)), NOT(D(b))), add(U(b), D(b));
                    else if(A[i-1][j] == 'W') add(U(b), U(b));
                    else if(A[i+1][j] == 'W') add(D(b), D(b));
                    else {
                        cout << "NO\n";
                        goto DONE;
                    }
                    if(A[i][j-1] == 'W' && A[i][j+1] == 'W') add(NOT(L(b)), NOT(R(b))), add(L(b), R(b));
                    else if(A[i][j-1] == 'W') add(L(b), L(b));
                    else if(A[i][j+1] == 'W') add(R(b), R(b));
                    else {
                        cout << "NO\n";
                        goto DONE;
                    }
                    b++;
                }
            }
        }
        for(int i = 0; i <= D(b-1); i++) {
            depth = 0;
            if(!num[i]) dfs(i);
        }
        b = 0;
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                if(A[i][j] == 'B') {
                    if(scc[L(b)] == scc[NOT(L(b))] ||
                       scc[R(b)] == scc[NOT(R(b))] ||
                       scc[U(b)] == scc[NOT(U(b))] ||
                       scc[D(b)] == scc[NOT(D(b))]) {
                        cout << "NO\n";
                        goto DONE;
                    }
                    b++;
                }
            }
        }
        cout << "YES\n";
        DONE: {}
        pv = t = 0;
        b = 0;
        while(s.size()) s.pop();
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                tkn[i][j].clear();
                if(A[i][j] == 'B') {
                    scc[L(b)] = num[L(b)] = low[L(b)] = inStack[L(b)] = 0;
                    g[L(b)].clear();
                    scc[NOT(L(b))] = num[NOT(L(b))] = low[NOT(L(b))] = inStack[NOT(L(b))] = 0;
                    g[NOT(L(b))].clear();

                    scc[R(b)] = num[R(b)] = low[R(b)] = inStack[R(b)] = 0;
                    g[R(b)].clear();
                    scc[NOT(R(b))] = num[NOT(R(b))] = low[NOT(R(b))] = inStack[NOT(R(b))] = 0;
                    g[NOT(R(b))].clear();

                    scc[U(b)] = num[U(b)] = low[U(b)] = inStack[U(b)] = 0;
                    g[U(b)].clear();
                    scc[NOT(U(b))] = num[NOT(U(b))] = low[NOT(U(b))] = inStack[NOT(U(b))] = 0;
                    g[NOT(U(b))].clear();

                    scc[D(b)] = num[D(b)] = low[D(b)] = inStack[D(b)] = 0;
                    g[D(b)].clear();
                    scc[NOT(D(b))] = num[NOT(D(b))] = low[NOT(D(b))] = inStack[NOT(D(b))] = 0;
                    g[NOT(D(b))].clear();

                    b++;
                }
                A[i][j] = '\0';
            }
        }
    }
}