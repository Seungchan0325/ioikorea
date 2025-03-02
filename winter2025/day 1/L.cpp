#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node* left, *right;
    int v;
};

int N, Q;

void init(Node* nd, int v, int s = 0, int e = N-1)
{
    if(s == e) {
        nd->v = v;
        return;
    }
    int m = (s + e) / 2;
    nd->left = new Node;
    nd->right = new Node;
    init(nd->left, v, s, m);
    init(nd->right, v, m+1, e);
    nd->v = nd->left->v + nd->right->v;
}

int query(int l, int r, Node* nd, int s = 0, int e = N-1)
{
    if(r < s || e < l) return 0;
    if(l <= s && e <= r) return nd->v;
    int m = (s + e) / 2;
    return query(l, r, nd->left, s, m) + query(l, r, nd->right, m+1, e);
}

void swap(int l, int r, Node* n1, Node* n2, int s = 0, int e = N-1)
{
    if(r < s || e < l) return;
    if(l <= s && e <= r) {
        swap(*n1, *n2);
        return;
    }
    int m = (s + e) / 2;
    swap(l, r, n1->left, n2->left, s, m);
    swap(l, r, n1->right, n2->right, m+1, e);
    n1->v = n1->left->v + n1->right->v;
    n2->v = n2->left->v + n2->right->v;
}

int main()
{
    cin >> N >> Q;
    Node* roots[52];
    for(int i = 0; i < 52; i++) {
        roots[i] = new Node;
        init(roots[i], i%13+1);
    }
    while(Q--) {
        int op;
        cin >> op;
        if(op == 0) {
            int A, B, I, J;
            cin >> A >> B >> I >> J;
            swap(A, B-1, roots[I], roots[J]);
        } else {
            int A, B;
            cin >> A >> B;
            int result = query(A, B-1, roots[51]);
            cout << result << "\n";
        }
    }
}