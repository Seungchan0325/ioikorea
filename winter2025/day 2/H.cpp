#include <bits/stdc++.h>

using namespace std;

int c2i[256];

struct Trie {
    vector<int> idxs;
    Trie* childs[4] = {0, };
    ~Trie() {
        for(int i = 0; i < 4; i++)
            if(childs[i])
                delete childs[i];
    }

    void insert(const char* c, int idx) {
        idxs.push_back(idx);
        if(*c == '\0') return;
        if(childs[c2i[*c]] == NULL) childs[c2i[*c]] = new Trie;
        childs[c2i[*c]]->insert(c+1, idx);
    }

    int query(const char* c, int l, int r)
    {
        if(*c == '\0') {
            return upper_bound(idxs.begin(), idxs.end(), r) - lower_bound(idxs.begin(), idxs.end(), l);
        }
        if(childs[c2i[*c]] == NULL) return 0;
        return childs[c2i[*c]]->query(c+1, l, r);
    }
};

int N, M;

int main()
{
    cin >> N >> M;
    vector<string> v(N);
    for(auto& i : v) cin >> i;
    sort(v.begin(), v.end());

    c2i['A'] = 0;
    c2i['G'] = 1;
    c2i['C'] = 2;
    c2i['U'] = 3;

    Trie* root = new Trie;
    for(int i = 0; i < N; i++) {
        auto tmp = v[i];
        reverse(tmp.begin(), tmp.end());
        root->insert(tmp.c_str(), i);
    }

    while(M--) {
        string p, q;
        cin >> p >> q;
        int l = lower_bound(v.begin(), v.end(), p) - v.begin();

        int lo = 0;
        int hi = N;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(v[mid] <= p || (v[mid].size() > p.size() && v[mid].substr(0, p.size()) <= p)) lo = mid;
            else hi = mid;
        }

        if(lo < l) {
            cout << "0\n";
            continue;
        }

        reverse(q.begin(), q.end());
        int ans = root->query(q.c_str(), l, lo);
        cout << ans << "\n";
    }

    delete root;
}