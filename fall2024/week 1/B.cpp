#include <bits/stdc++.h>

using namespace std;

int N, A[11], B[11], sum;

int distribute(int A[], int i)
{
    int a = A[i];
    A[i] = 0;
    while(a) {
        i = (i + 1) % N;
        A[i]++;
        a--;
    }
    // for(int i = 0; i < N; i++) {
    //     cout << A[i] << " ";
    // }
    // cout << "\n";
    return i;
}

void collect(int A[], int i)
{
    int a = 0;
    while(A[i]) {
        a++;
        A[i]--;
        i = (i-1+N)%N;
    }
    A[i] += a;
}

vector<pair<int, int>> normalize(int A[])
{
    vector<pair<int, int>> path;
    while(A[0] != sum) {
        for(int i = 1; i < N; i++) {
            if(A[i]) {
                int j = distribute(A, i);
                path.emplace_back(i, j);
            }
        }
    }
    return path;
}

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = 0; i < N; i++) cin >> B[i];

    for(int i = 0; i < N; i++) sum += A[i];

    // while(true) {
    //     char op;
    //     int i;
    //     cin >> op >> i;
    //     i--;
    //     if(op == 'D') distribute(A, i);
    //     else collect(A, i);
    //     for(int i = 0; i < N; i++) {
    //         cout << A[i] << " ";
    //     }
    //     cout << "\n";
    // }

    vector<string> ans;

    for(auto [i, j] : normalize(A)) {
        ans.emplace_back("D " + to_string(i+1));
    }

    auto path = normalize(B);
    reverse(path.begin(), path.end());
    for(auto [i, j] : path) {
        ans.emplace_back("C " + to_string(j+1));
    }

    cout << ans.size() << "\n";
    for(auto& s : ans) cout << s << "\n";
}