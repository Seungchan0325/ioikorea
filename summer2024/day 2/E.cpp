#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int N;

vector<int> DnC(vector<int> a)
{
    if(a.size() <= 2) return a;
    vector<int> l, r;
    for(auto i : a) {
        if(i&1) l.push_back((i+1)/2);
        else r.push_back(i/2);
    }
    l = DnC(l);
    r = DnC(r);
    for(int& i : l) i = 2*i-1;
    for(int& i : r) i = 2*i;
    l.insert(l.end(), r.begin(), r.end());
    return l;
}

int main()
{
    cin >> N;
    vector<int> v(N);
    for(auto& i : v) cin >> i;
    sort(v.begin(), v.end());
    for(int i = 0; i+2 < v.size(); i++) {
        if(v[i] == v[i+1] && v[i] == v[i+2]) {
            cout << "-1";
            return 0;
        }
    }
    auto result = DnC(v);
    for(int i : result) cout << i << " ";
}