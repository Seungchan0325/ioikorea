#include <vector>
#include <bits/stdc++.h>

using namespace std;

void light_switch(int) ;

const int MAXN = 2005;

bool chk[20][1<<16];
pair<int, int> par[20][1<<16];
vector<pair<int, int>> graph[MAXN];

int hide(int N, std::vector<int> U, std::vector<int> V) {
    for(int i = 0; i < U.size(); i++) {
        graph[U[i]].emplace_back(V[i], 1);
        graph[V[i]].emplace_back(U[i], 0);
    }

    deque<tuple<int, int, int>> q;

    chk[1][1<<1] = true;
    par[1][1<<1] = {-1, 0};
    q.emplace_back(1, 1<<1, 0);
    while(!q.empty()) {
        auto [u, bit, depth] = q.front(); q.pop_front();
        if(u == N && bit == 0) {
            vector<int> v;
            v.push_back(bit);
            while(true) {
                int tmpu = u;
                int tmpbit = bit;
                u = par[tmpu][tmpbit].first;
                bit = par[tmpu][tmpbit].second;
                if(u == -1) break;
                v.push_back(bit);
            }
            reverse(v.begin(), v.end());
            for(int i = 2; i < v.size(); i++) {
                if(v[i-1] == v[i]) continue;
                
                int diff = v[i-1] ^ v[i];
                for(int i = 0; i < 20; i++) {
                    if(diff & (1<<i)) {
                        cout << i << "\n";
                        light_switch(i);
                        break;
                    }
                }
            }
            return depth;
        }
        if(!chk[u][bit|(1<<u)]) {
            chk[u][bit|(1<<u)] = true;
            par[u][bit|(1<<u)] = {u, bit};
            q.emplace_back(u, bit|(1<<u), depth+1);
        }
        if(!chk[u][bit&~(1<<u)]) {
            chk[u][bit&~(1<<u)] = true;
            par[u][bit&~(1<<u)] = {u, bit};
            q.emplace_front(u, bit&~(1<<u), depth);
        }
        for(auto [v, t] : graph[u]) {
            if(t && (bit&(1<<u)) && !chk[v][bit]) {
                chk[v][bit] = true;
                par[v][bit] = {u, bit};
                q.emplace_front(v, bit, depth);
            } else if(!t && (bit&(1<<v)) && !chk[v][bit]) {
                chk[v][bit] = true;
                par[v][bit] = {u, bit};
                q.emplace_front(v, bit, depth);
            }
        }
    }
    
    return -1;
}