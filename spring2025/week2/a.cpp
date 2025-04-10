#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for(auto&i:v)cin>>i;
    sort(v.begin(),v.end());
    int i = (n+1)/2-1;
    int j = i+1;
    while(i >= 0 || j < n) {
        if(i >= 0) cout << v[i--] << " ";
        if(j < n) cout << v[j++] << " ";
    }
}