#include <bits/stdc++.h>
#include <vector>
#include "grader.cpp"

using namespace std;

const int MAXN = 200505;

struct SegTree {
	int N;
	vector<int> tree, lazy;
	void init(int n) {
		N = n;
		tree.resize(4*N);
		lazy.resize(4*N);
	}

	void push(int s, int e, int idx)
	{
		if(lazy[idx]) {
			tree[idx] += lazy[idx];
			if(s != e) {
				lazy[2*idx] += lazy[idx];
				lazy[2*idx+1] += lazy[idx];
			}
			lazy[idx] = 0;
		}
	}

	void update(int l, int r, int delta, int s, int e, int idx)
	{
		push(s, e, idx);
		if(r < s || e < l) return;
		if(l <= s && e <= r) {
			lazy[idx] += delta;
			push(s, e, idx);
			return;
		}
		int m = (s + e) / 2;
		update(l, r, delta, s, m, 2*idx);
		update(l, r, delta, m+1, e, 2*idx+1);
		tree[idx] = tree[2*idx] + tree[2*idx+1];
	}

	int query(int l, int r, int s, int e, int idx)
	{
		push(s, e, idx);
		if(e < l || r < s) return 0;
		if(s == e) return tree[idx];
		int m = (s + e) / 2;
		return query(l, r, s, m, 2*idx) + query(l, r, m+1, e, 2*idx+1);
	}

	void update(int l, int r, int delta)
	{
		update(l, r, delta, 1, N, 1);
	}

	int query(int l, int r)
	{
		return query(l, r, 1, N, 1);
	}
};

struct SegTree2 {
	int N;
	vector<int> tree, lazy;
	void init(int n) {
		N = n;
		tree.resize(4*N, 1);
		lazy.resize(4*N);
	}

	void push(int s, int e, int idx)
	{
		if(lazy[idx]) {
			tree[idx] = max(tree[idx], lazy[idx]);
			if(s != e) {
				lazy[2*idx] = max(lazy[2*idx], lazy[idx]);
				lazy[2*idx+1] = max(lazy[idx], lazy[2*idx+1]);
			}
			lazy[idx] = 0;
		}
	}

	void update(int l, int r, int delta, int s, int e, int idx)
	{
		push(s, e, idx);
		if(r < s || e < l) return;
		if(l <= s && e <= r) {
			lazy[idx] += delta;
			push(s, e, idx);
			return;
		}
		int m = (s + e) / 2;
		update(l, r, delta, s, m, 2*idx);
		update(l, r, delta, m+1, e, 2*idx+1);
		tree[idx] = max(tree[2*idx], tree[2*idx+1]);
	}

	int query(int l, int r, int s, int e, int idx)
	{
		push(s, e, idx);
		if(e < l || r < s) return 0;
		if(s == e) return tree[idx];
		int m = (s + e) / 2;
		return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
	}

	void update(int l, int r, int delta)
	{
		update(l, r, delta, 1, N, 1);
	}

	int query(int l, int r)
	{
		return query(l, r, 1, N, 1);
	}
};

int sz[MAXN], dep[MAXN], par[MAXN], top[MAXN], in[MAXN], out[MAXN], order[MAXN], pv, t;
int ans, state[MAXN];
vector<int> graph[MAXN], input[MAXN];
SegTree sum;
SegTree2 root;

void dfs0(int u, int p)
{
	for(auto v : input[u]) {
		if(v == p) continue;
		graph[u].push_back(v);
		dfs0(v, u);
	}
}

void dfs(int u)
{
	sz[u] = 1;
	for(auto& v : graph[u]) {
		par[v] = u;
		dep[v] = dep[u] + 1;
		dfs(v);
		sz[u] += sz[v];
		if(sz[v] > sz[graph[u][0]]) swap(v, graph[u][0]);
	}
}

void dfs1(int u)
{
	in[u] = ++pv;
	order[in[u]] = u;
	for(auto v : graph[u]) {
		top[v] = v == graph[u][0] ? top[u] : v;
		dfs1(v);
	}
	out[u] = pv;
}

void update(int u, int v, int delta)
{
	while(top[u] != top[v]) {
		if(dep[u] < dep[v]) swap(u, v);
		sum.update(in[top[u]], in[u], delta);
		u = par[top[u]];
	}
	if(dep[u] < dep[v]) swap(u, v);
	sum.update(in[v], in[u], delta);
}

void initialize(int N, std::vector<int> A, std::vector<int> B){
	int M = A.size();
	for(int i = 0; i < M; i++) {
		input[A[i]].push_back(B[i]);
		input[B[i]].push_back(A[i]);
	}
	dfs0(0, -1);
	dfs(0);
	dfs1(0);
	sum.init(N);
	root.init(N);
	return;
}
 
int generate(int v, bool result){
	state[v] = result ? 1 : -1;
	if(result) {
		int r = order[root.query(in[v], in[v])];
		update(r, v, 1);
		if(sum.query(in[r], in[r])%2 == 0) ans++;
	} else {
		int r = order[root.query(in[v], in[v])];
		int t = sum.query(in[v], in[v]);
		int tt = sum.query(in[r], in[r]);
		ans -= tt / 2;
		ans += (tt - t) / 2;
		update(v, r, -t);
		for(auto w : graph[v]) {
			if(state[w] == -1) continue;
			root.update(in[w], out[w], in[w]);
			ans += sum.query(in[w], in[w]) / 2;
		}
	}
	return ans;
}
