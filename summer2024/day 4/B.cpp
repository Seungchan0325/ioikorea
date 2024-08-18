#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int Q;
    cin >> Q;

    map<int, int> s;
    while(Q--){
        int t;
        cin >> t;
        int x;
        cin >> x;
        if(t == 1) {
            s[x]++;
        } else if(t == 2) {
            if(s[x]) s[x]--;
        } else if(t == 3) {
            cout << s[x] << "\n";
        }
    }
}