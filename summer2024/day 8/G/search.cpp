#include "search.h"
#include <bits/stdc++.h>

using namespace std;

int search(int N, int K) {
	int lo = max(-1, K - (N - 1) - 2);
	int hi = min(K, N);
	while(lo + 1 < hi) {
		int i = (lo + hi) / 2;
		int j = K - i - 2;
		if(compare(i, j+1)) lo = i;
		else hi = i;
	}

	int j = K - lo - 2;
	if(lo < 0 || (j >= 0 && compare(lo, j))) return N+j;

	return lo;
}
