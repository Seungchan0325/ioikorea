#include <queue>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include "hideandseek.cpp"

extern int hide(int, std::vector<int>, std::vector<int>) ;
void light_switch(int) ;

static int N, M, curr;
static std::vector<int> adj[2006], adj_rev[2006];
static int lights[2006], res;
static int full;

void assertion(bool x, int s) {
    if (x) return;
    else if (s < 0) puts("Wrong Input");
    else printf("Wrong Answer\n");
    exit(0);
}

void light_switch(int to) {
    if (full != -1) return;
    if (!(to >= 1 && to <= N)) {
        full = 0;
        return;
    }
    to--;
    std::vector<int> visited(N, 0);
    std::queue<int> q;
    q.push(curr);
    visited[curr] = 1;
    while (!q.empty()) {
        int t = q.front(); q.pop();
        for (auto &i: adj[t]) {
            if (visited[i]) continue;
            if (!lights[t]) continue;
            visited[i] = true;
            q.push(i);
        }
        for (auto &i: adj_rev[t]) {
            if (visited[i]) continue;
            if (!lights[i]) continue;
            visited[i] = true;
            q.push(i);
        }
    }
    if (!visited[to]) {
        full = 1;
        return;
    }
    curr = to;
    if (!lights[curr]) res++;
    lights[curr] ^= 1;
}

int main() {
    full = -1;
    assertion(scanf("%d%d", &N, &M) == 2, -1);
    std::vector<int> U, V;
    for (int i = 0; i < M; i++) {
        int u, v;
        assertion(scanf("%d%d", &u, &v) == 2, -1);
        U.push_back(u);
        V.push_back(v);
        adj[u - 1].push_back(v - 1);
        adj_rev[v - 1].push_back(u - 1);
    }
    curr = 0;
    lights[0] = 1;
    int result = hide(N, U, V);
    if (result != -1) {
        if (!(curr == N - 1) && full == -1) full = 2;
        if (full == -1) for (int i = 0; i < N; i++) if (lights[i]) full = 3;
        if (!(res == result) && full == -1) full = 4;
        printf("%d\n", result);
    } else {
        if (!(res == 0)) full = 5;
        for (int i = 1; i < N; i++) if (lights[i]) full = 5;
        printf("%d\n", -1);
    }
    if (full != -1) printf("Wrong answer [%d]\n", full);
}