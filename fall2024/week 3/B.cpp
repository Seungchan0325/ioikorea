#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, A[MAXN], B[MAXN], C[MAXN];

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = 0; i < N; i++) cin >> B[i];
    for(int i = 0; i < N; i++) cin >> C[i];
    sort(A, A + N);
    sort(B, B + N);
    sort(C, C + N);

    int i, j, k;
    i = j = k = 0;
    while(true) {
        while(j < N && A[i] >= B[j]) j++;
        if(j == N) break;
        while(k < N && B[j] >= C[k]) k++;
        if(k == N) break;
        i++;
        j++;
        k++;
    }
    cout << i << "\n";
}