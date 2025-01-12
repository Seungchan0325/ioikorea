#include "five.h"
#include "grader.cpp"
#include <bits/stdc++.h>

using namespace std;

int five (int subtask) {
	if(subtask == 1) {
		pair<int, int> a, b;
		if(compare(1, 2) > 0) a = {1, 2};
		else a = {2, 1};
		if(compare(3, 4) > 0) b = {3, 4};
		else b = {4, 3};
		if(compare(a.first, b.first) < 0) swap(a, b);
		a.first = 5;
		if(compare(a.first, a.second) < 0) swap(a.first, a.second);
		if(compare(a.first, b.first) < 0) swap(a, b);
		if(compare(a.second, b.first) > 0) return a.second;
		else return b.first;
	} else {
		vector<int> order(3);
		pair<int, int> a{1, 2}, b{3, 4};
		if(compare(a.first, a.second) > 0) swap(a.first, a.second);
		if(compare(b.first, b.second) > 0) swap(b.first, b.second);
		if(compare(a.first, b.first) > 0) swap(a, b);

		order[0] = a.first;
		order[1] = b.first;
		order[2] = b.second;
		
		int lo = -1;
		int hi = order.size();
		while(lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if(compare(order[mid], 5) < 0) lo = mid;
			else hi = mid;
		}
		order.insert(order.begin()+hi, 5);

		int idx = -1;
		for(int i = 0; i < 4; i++) {
			if(order[i] == a.first) {
				idx = i;
				break;
			}
		}
		assert(idx != -1);

		lo = idx;
		hi = order.size();
		while(lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if(compare(order[mid], a.second) < 0) lo = mid;
			else hi = mid;
		}
		order.insert(order.begin()+hi, a.second);

		int ans[6] = {};
		for(int i = 0; i < 5; i++) {
			ans[order[i]] = i+1;
		}
		return ans[1] * 10000 + ans[2] * 1000 + ans[3] * 100 + ans[4] * 10 + ans[5];
	}
	return 5;
}
