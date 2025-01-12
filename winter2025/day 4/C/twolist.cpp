#include "twolist.h"
// #include "grader.cpp"
#include <bits/stdc++.h>

using namespace std;

int twolist(int n){
	int lo1 = 1;
	int hi1 = n;
	int lo2 = 1;
	int hi2 = n;
	while(true) {
		if(lo1 == hi1 || lo2 == hi2) break;
		int mid1 = (lo1 + hi1) / 2;
		int mid2 = (lo2 + hi2) / 2;
		if(compare(mid1, mid2) < 0) {
			hi2 = mid2;
			lo1 = n - hi2 + 1;
		} else {
			hi1 = mid1;
			lo2 = n - hi1 + 1;
		}
	}
	if(compare(lo1, lo2) < 0) return lo1;
	else return lo2 + n;
}
