#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 14;
const ll INF = 1e18;

ll N, L, w[MAXN][MAXN];

struct State {
    ll dist;
    bool operator < (const State& other) const {
        return dist < other.dist;
    }
    
    bool operator < (const ll& other) const {
        return dist < other;
    }
};

vector<State> sts[1<<MAXN][MAXN];

void f(ll now, ll vst, ll dist)
{
    vst |= (1<<now);
    ll visited = __popcount(vst);
    if(visited >= N/2) {
        sts[vst][now].push_back({dist});
    }
    if(visited > (N+1)/2) return;
    for(ll nxt = 0; nxt < N; nxt++) {
        if(vst&(1<<nxt)) continue;
        f(nxt, vst, dist+w[now][nxt]);
    }
}

int main()
{
    cin >> N >> L;
    for(ll i = 0; i < N; i++) {
        for(ll j = 0; j < N; j++) {
            cin >> w[i][j];
        }
    }

    f(0, 0, 0);
    for(ll i = 0; i < (1<<N); i++) {
        for(ll j = 0; j < N; j++) {
            sort(sts[i][j].begin(), sts[i][j].end(), [](State& a, State& b){
                return a.dist < b.dist;
            });
        }
    }
    for(ll i = 0; i < (1<<N); i++) {
        for(ll j = 0; j < N; j++) {
            for(auto& state : sts[i][j]) {
                ll overvst = ((1<<N)-1)^i | 1 | (1<<j);
                if(sts[overvst][j].empty()) continue;
                ll lo = 0;
                ll hi = sts[overvst][j].size();
                while(lo + 1 < hi) {
                    ll mid = (lo + hi) / 2;
                    if(sts[overvst][j][mid].dist <= L - state.dist) lo = mid;
                    else hi = mid;
                }
                if(sts[overvst][j][lo].dist + state.dist == L) {
                    cout << "possible";
                    return 0;
                }
            }
        }
    }
    cout << "impossible";
}