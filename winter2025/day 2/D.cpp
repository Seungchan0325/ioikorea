#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    cin >> s;
    string tmp = "#";
    for(auto c : s) {
        tmp += c;
        tmp += "#";
    }
    s = tmp;

    int mx = -1;
    int mxi = -1;

    int n = s.size();
    int p, r;
    p = r = 0;
    vector<int> A(n);
    for(int i = 0; i < n; i++) {
        if(i <= r)
            A[i] = min(A[2*p-i], r-i);
        else
            A[i] = 0;
        
        int left = i - A[i] - 1;
        int right = i + A[i] + 1;
        while(0 <= left && right < n && s[left] == s[right]) {
            A[i]++;
            left--;
            right++;
        }

        if(r < i + A[i]) {
            r = i + A[i];
            p = i;
        }

        if(mx < A[i]) {
            mx = A[i];
            mxi = i;
        }
    }

    for(int i = mxi - mx + 1; i < mxi + mx; i+=2) {
        cout << s[i];
    }
}