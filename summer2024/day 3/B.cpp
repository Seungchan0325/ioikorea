// #include "nostl.h"
#include <cstdio>
#include <cstring>

struct Node {
    int data;
    int prv, nxt;
};

const int MAXN = 1000005;

int N, front, pv, cur;
Node node[MAXN];

int operate(int op, int c)
{
    int ret = -1;
    if(op == 1) {
        if(cur != front) {
            cur = node[cur].prv;
        }
    } else if(op == 2) {
        if(node[cur].nxt != -1) {
            cur = node[cur].nxt;
        }
    } else if(op == 3) {
        pv++;
        node[pv].data = c;
        node[pv].prv = cur;
        node[pv].nxt = node[cur].nxt;

        node[node[cur].nxt].prv = pv;
        node[cur].nxt = pv;

        cur = pv;
    } else if(op == 4) {
        if(cur != front) {
            ret = node[cur].data;
            node[node[cur].prv].nxt = node[cur].nxt;
            node[node[cur].nxt].prv = node[cur].prv;
            cur = node[cur].prv;
        }
    }

    return ret;
}

int main()
{
    scanf("%d", &N);
    node[front].data = -1;
    node[front].prv = -1;
    node[front].nxt = -1;

    char op[16];
    while(N--) {
        scanf("%s", op);

        if(strcmp(op, "PUSH") == 0) {
            int x;
            scanf(" %d", &x);
            operate(3, x);
        } else if(strcmp(op, "POP") == 0) {
            printf("%d\n", operate(4, -1));
        } else if(strcmp(op, "TOP") == 0) {
            printf("%d\n", node[cur].data);
        }
    }

    int sz = 0;
    for(int i = node[front].nxt; i != -1; i = node[i].nxt) sz++;
    printf("%d\n", sz);
    for(int i = node[front].nxt; i != -1; i = node[i].nxt) printf("%d ", node[i].data);
}