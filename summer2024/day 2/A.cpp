#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150;

int N, A[MAXN][MAXN];

string compress(int r, int c, int len)
{
    if(len == 1) {
        return to_string(A[r][c]);
    }

    bool is_all_zero = true;
    bool is_all_one = true;
    for(int i = r; i < r+len; i++) {
        for(int j = c; j < c+len; j++) {
            if(A[i][j] == 0) is_all_one = false;
            else is_all_zero = false;
        }
    }

    if(is_all_zero) return "0";
    else if(is_all_one) return "1";

    string left_top = compress(r, c, len/2);
    string right_top = compress(r+len/2, c, len/2);
    string left_bottom = compress(r, c+len/2, len/2);
    string right_bottom = compress(r+len/2, c+len/2, len/2);

    return '(' + left_top + right_top + left_bottom + right_bottom + ')';
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> A[j][i];
        }
    }

    cout << compress(1, 1, N);
}