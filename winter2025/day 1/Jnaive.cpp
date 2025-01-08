#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200505;

int N, A[MAXN], B[MAXN], K[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i] >> B[i] >> K[i];
    }
    while(true) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;

        for(int j = x; j <= y; j++) {
            cout << j << "\t";
        }
        cout << "\n";

        for(int j = x; j <= y; j++) {
            int mental = j;
            int add = 0;
            for(int i = l; i <= r; i++) {
                if(mental < K[i]) {
                    mental += A[i];
                    add += A[i];
                } else {
                    mental += B[i];
                    add += B[i];
                }
            }
            cout << add << "\t";
        }
        cout << "\n";
    }
}