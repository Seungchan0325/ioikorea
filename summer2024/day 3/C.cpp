#include <bits/stdc++.h>

using namespace std;

int main()
{
    stack<char> s;
    string str;
    cin >> str;

    bool yes = true;
    for(auto c : str) {
        if(c == '(') s.push(c);
        else if(c == '[') s.push(c);
        else if(c == ')') {
            if(s.empty() || s.top() != '(') yes = false;
            if(s.size()) s.pop();
        } else if(c == ']') {
            if(s.empty() || s.top() != '[') yes = false;
            if(s.size()) s.pop();
        }
    }

    if(s.size()) yes = false;

    if(yes) cout << "YES";
    else cout << "NO";
}