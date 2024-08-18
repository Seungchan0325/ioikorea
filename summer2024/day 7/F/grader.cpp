#include "buildbst.h"
#include "buildbst.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

static int N, K;
static int A[300000], B[300000];
static int compare_call_count = 0;

int compare(char arr, int i, int j) {
	compare_call_count++;
	if(K < compare_call_count || ('A' != arr && 'B' != arr) || i < 0 || j <= i || N <= j) {
		printf("Wrong Answer\n");
		exit(0);
	}
	if('A' == arr) {
		if(A[i] < A[j]) return 1;
		else return 0;
	} else {
		if(B[i] < B[j]) return 1;
		else return 0;
	}
}

int main() {
	scanf("%d %d", &N, &K);
	for(int i = 0; i < N; i++) scanf("%d", &A[i]);
	for(int i = 0; i < N; i++) scanf("%d", &B[i]);

	std::vector<int> ret = buildbst(N);

	for(int i = 0; i < ret.size(); i++) {
		printf("%d ", ret[i]);
	}
	printf("\n");
	return 0;
}
