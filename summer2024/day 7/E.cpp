#include <bits/stdc++.h>

using namespace std;

int N;

int main()
{
    cin >> N;
    priority_queue<int> mnpq, mxpq;
    int m;
    cin >> m;
    N--;
    cout << m << "\n";
    while(N--) {
        int a;
        cin >> a;
        if(a < m) mxpq.push(a);
        else mnpq.push(-a);
        
        if(mxpq.size() > mnpq.size()) {
            mnpq.push(-m);
            m = mxpq.top(); mxpq.pop();
        } else if(mxpq.size() < mnpq.size()) {
            mxpq.push(m);
            m = -mnpq.top(); mnpq.pop();
        }

        if(~N&1) cout << m << "\n";
    }
}