#include <string>
#include <bits/stdc++.h>
using namespace std;

string s;

void init(int N, std::string S)
{
    s = S;
    return;
}

long long contest_time(long long A, long long L, long long R)
{
    vector<int> key(3);
    long long ret = 1e18;
    for(int i = 0; i < 3; i++) key[i] = i;
    do {
        long long type = A * s.size();
        for(int i = 1; i < s.size(); i++) {
            if(s[i-1] == s[i]) continue;

            if(key[s[i-1]-'A'] < key[s[i]-'A']) {
                type += R * (key[s[i]-'A'] - key[s[i-1]-'A']);
            } else {
                type += L * (key[s[i-1]-'A'] - key[s[i]-'A']);
            }
        }
        ret = min(ret, type);
    } while(next_permutation(key.begin(), key.end()));
    return ret;
}