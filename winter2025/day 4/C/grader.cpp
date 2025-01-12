#include <iostream>
#include "twolist.h"
using namespace std;

static const int MX=500010;

static int n, A[MX], B[MX];
static int count;

int compare(int i, int j){
	count++;
	return A[i]<B[j] ? -1 : 1;
}

int main(){
	scanf("%d", &n);
	for(int i=1; i<=n; i++) scanf("%d", &A[i]);
	for(int i=1; i<=n; i++) scanf("%d", &B[i]);

	printf("Your answer: %d\n", twolist(n));
	printf("Compare count: %d\n", count);

	return 0;
}
