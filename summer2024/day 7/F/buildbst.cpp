#include "buildbst.h"
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

std::vector<int> buildbst(int N) {
	vector<int> ans(N);

	stack<int> s;
	vector<int> l(N, -1), r(N, -1), deg(N);
	vector<vector<int>> graph(N);	
	for(int i = 0; i < N; i++) {
		while(s.size() && !compare('B', s.top(), i)) {
			int j = s.top();
			r[j] = i;
			deg[j]++;
			graph[r[j]].push_back(j);
			s.pop();
		}
		if(s.size()) {
			l[i] = s.top();
			deg[i]++;
			graph[l[i]].push_back(i);
		}
		s.push(i);
	}

	queue<int> q;
	for(int i = 0; i < N; i++) {
		if(l[i] == -1 && r[i] == -1) {
			q.push(i);
			break;
		}
	}

	while(!q.empty()) {
		auto i = q.front(); q.pop();
		int dep = -1;
		if(l[i] != -1) dep = max(dep, ans[l[i]]);
		if(r[i] != -1) dep = max(dep, ans[r[i]]);
		ans[i] = dep + 1;
		for(auto j : graph[i]) {
			if(--deg[j] == 0) q.push(j);
		}
	}

	return ans;
}