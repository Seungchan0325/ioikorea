#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int N, k, q, heap[MAXN];
set<int> s;
queue<int> que;

int log2(int a)
{
    for(int i = 31; i >= 0; i--) {
        if(a&(1<<i)) {
            return i;
        }
    }
    return -1;
}

void build(int& k, int q)
{
    if(q > N) return;
    if(s.count(k) == 0) k = 1e9;
    heap[q] = k++;
    s.erase(heap[q]);
    build(k, 2*q);
    build(k, 2*q+1);
}

int main()
{
    cin >> N >> k >> q;

    for(int i = 1; i <= N; i++) s.insert(i);

    memset(heap, -1, sizeof(heap));

    int u = q / 2;
    while(u > 0) {
        heap[u] = log2(u) + 1;
        s.erase(heap[u]);
        u /= 2;
    }

    int tk = k;
    build(tk, q);
    if(tk > N+1) goto NOT_FOUND;

    for(int i = 1; i <= N; i++) {
        if(heap[i] != -1) continue;

        auto it = s.lower_bound(heap[i/2]);
        if(it == s.end()) goto NOT_FOUND;
        s.erase(it);
        heap[i] = *it;
    }

    que.push(1);
    while(!que.empty()) {
        int u = que.front(); que.pop();
        cout << heap[u] << "\n";
        if(2*u <= N) que.push(2*u);
        if(2*u+1 <= N) que.push(2*u+1);
    }

    return 0;
NOT_FOUND:
    cout << "-1";
    return 0;
}