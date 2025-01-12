#include<cstdio>
#include "five.h"
#include <bits/stdc++.h>
using namespace std;

int _VAL[6];
int _CNT;

int compare (int _I, int _J) {
	assert(++_CNT <= 7);
	if(_VAL[_I] < _VAL[_J]) return -1;
	if(_VAL[_I] > _VAL[_J]) return 1;
	return 0;
}

int main()
{
	int _T;
	scanf("%d", &_T);
	scanf("%d%d%d%d%d",&_VAL[1], &_VAL[2], &_VAL[3], &_VAL[4], &_VAL[5]);
	printf("%d\n", five(_T));
	iota(_VAL, _VAL+6, 0);
	do {
		// assert(_VAL[five(1)] == 3);
		_CNT = 0;
		assert(five(2) == _VAL[1]*10000+_VAL[2]*1000+_VAL[3]*100+_VAL[4]*10+_VAL[5]);
	} while(next_permutation(_VAL+1, _VAL+6));
}
