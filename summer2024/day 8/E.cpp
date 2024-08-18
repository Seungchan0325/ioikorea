#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int N, A[5][MAXN], R[MAXN], indeg[MAXN], nxt[MAXN][5], rA[5][MAXN];
pair<bool, bool> nnxt[MAXN][5];

int main()
{
    cin >> N;
    memset(nnxt, -1, sizeof(nnxt));
    for(int i = 0; i < 5; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> A[i][j];
            rA[i][A[i][j]] = j;
        }
        for(int j = 1; j+1 <= N; j++) {
            nxt[A[i][j]][i] = A[i][j+1];
        }
    }

    vector<int> v(N);
    iota(v.begin(), v.end(), 1);
    sort(v.begin(), v.end(), [](int a, int b){
        int a_first = 0;
        int b_first = 0;
        for(int i = 0; i < 5; i++) {
            if(rA[i][a] < rA[i][b]) a_first++;
            else b_first++;
        }
        if(a_first >= 3) return true;
        else return false;
    });

    for(int i = 0; i < N; i++) cout << v[i] << " ";
}