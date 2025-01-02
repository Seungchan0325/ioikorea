#include <bits/stdc++.h>

using namespace std;

struct student
{
    string s;
    int sum;
    int idx;
    bool operator < (const student& rhs) const {
        if(sum != rhs.sum) return sum > rhs.sum;
        return s < rhs.s;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<student> st(n);
    for(int i = 0; i < n; i++) {
        cin >> st[i].s;
        for(int j = 0; j < 5; j++) {
            int a;
            cin >> a;
            st[i].sum += a;
        }
        st[i].idx = i;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(st[j].idx == i) {
                st[j].sum += 500;
                break;
            }
        }
        sort(st.begin(), st.end());
        for(int j = 0; j < n; j++) {
            if(st[j].idx == i) {
                cout << j + 1 << " ";
                st[j].sum -= 500;
            } else {
                st[j].sum += 500;
            }
        }
        sort(st.begin(), st.end());
        for(int j = 0; j < n; j++) {
            if(st[j].idx == i) {
                cout << j + 1 << "\n";
            } else {
                st[j].sum -= 500;
            }
        }
    }
}