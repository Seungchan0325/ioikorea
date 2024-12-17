#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;

    vector<pair<int, int>> v1, v2;
    for(int i = 0; i < n; i++) {
        v1.emplace_back(a[i], i % 2);
        v2.emplace_back(b[i], i % 2);
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    if(v1 == v2) cout << "Yes";
    else cout << "No";
}