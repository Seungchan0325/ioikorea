#include <vector>
#include <bits/stdc++.h>

using namespace std;

std::vector<int> change_lamps(std::vector<int> A, int K) {
	int n = A.size();
	int cnt = 1;
	vector<pair<int, int>> v1, v2;
	for(int i = 1; i < n; i++) {
		if(A[i-1] != A[i]) {
			if(A[i-1] == '0') v1.emplace_back(cnt, i-1);
			else v2.emplace_back(cnt, i-1);
			cnt = 0;
		}
		cnt++;
	}

	if(cnt) {
		if(A[n-1] == '0') v1.emplace_back(cnt, n-1);
		else v2.emplace_back(cnt, n-1);
	}

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	return A;
}
