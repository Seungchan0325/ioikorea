// #include "nostl.h"
#include <cstdio>

struct Node {
    char data;
    int prv, nxt;
};

const int MAXN = 1000005;

int N, front, pv;
Node node[MAXN];

int main()
{
    scanf("%d", &N);
    node[front].prv = -1;
    node[front].nxt = -1;

    int cur = front;
    while(N--) {
        int op;
        scanf("%d", &op);

        if(op == 1) {
            if(cur != front) {
                cur = node[cur].prv;
            }
        } else if(op == 2) {
            if(node[cur].nxt != -1) {
                cur = node[cur].nxt;
            }
        } else if(op == 3) {
            char c;
            scanf(" %c", &c);

            pv++;
            node[pv].data = c;
            node[pv].prv = cur;
            node[pv].nxt = node[cur].nxt;

            node[node[cur].nxt].prv = pv;
            node[cur].nxt = pv;

            cur = pv;
        } else if(op == 4) {
            if(cur != front) {
                node[node[cur].prv].nxt = node[cur].nxt;
                node[node[cur].nxt].prv = node[cur].prv;
                cur = node[cur].prv;
            }
        }
    }

    for(int i = node[front].nxt; i != -1; i = node[i].nxt) {
        printf("%c", node[i].data);
    }
}