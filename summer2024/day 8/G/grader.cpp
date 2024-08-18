#include "search.h"
#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "search.cpp"

#pragma warning(disable:4996)

static int NN;
static int A[100050];
static int B[100050];
static int compare_call_count = 0;
int compare(int i, int j) {
	compare_call_count++;
	if (i < 0 || i >= NN || j < 0 || j >= NN) {
		printf("Wrong Answer\n");
		exit(0);
	}
	if (A[i] < B[j]) return 1;
	else return 0;
}

int main() {
	int N, K, i;
	scanf("%d %d", &N, &K);
	NN = N;
	for (i = 0; i < N; i++) scanf("%d", &A[i]);
	for (i = 0; i < N; i++) scanf("%d", &B[i]);

	int cnt = 0;

	int p0 = 0, p1 = 0;
	int ans = 0;
	for (int i = 1; i <= K; i++) {
		if (p0 == N || (p1 != N && A[p0] > B[p1])) {
			ans = p1 + N;
			p1++;
		}
		else {
			ans = p0;
			p0++;
		}
	}
	
	if (search(N, K) != ans) printf("Wrong Answer\n");
	else {
		printf("Correct!\n");
		printf("Your function calls: %d\n", compare_call_count);
	}
	return 0;
}
