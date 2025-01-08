#include <bits/stdc++.h>

using namespace std;

int N;
string ans;

struct Trie {
    bool terminate = false;
    int depth = -1;
    Trie* childs[26];
    void insert(const char* c) {
        if(*c == NULL) {
            terminate = true;
            return;
        }
        if(childs[*c-'a'] == NULL) childs[*c-'a'] = new Trie();
        childs[*c-'a']->insert(c+1);
    }
    int getdepth()
    {
        if(depth != -1) return depth;
        for(int i = 0; i < 26; i++) {
            if(childs[i] != NULL) {
                depth = max(childs[i]->getdepth()+1, depth);
            }
        }
        return depth;
    }
    void dfs(bool islast)
    {
        if(terminate) ans.push_back('P');
        vector<pair<int, int>> v;
        for(int i = 0; i < 26; i++) {
            if(childs[i] != NULL) {
                v.emplace_back(childs[i]->getdepth(), i);
            }
        }
        sort(v.begin(), v.end());
        for(auto [dep, i] : v) {
            ans.push_back(i+'a');
            childs[i]->dfs(islast && i == v.back().second);
        }
        if(!islast) ans.push_back('-');
    }
};

int main()
{
    cin >> N;
    vector<string> v[26];
    Trie* root = new Trie;
    for(int i = 0; i < N; i++) {
        string s;
        cin >> s;
        root->insert(s.c_str());
    }
    root->dfs(true);
    cout << ans.size() << "\n";
    for(auto c : ans) {
        cout << c << "\n";
    }
}