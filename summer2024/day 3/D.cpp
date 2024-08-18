// #include "nostl.h"
#include <cstdio>
#include <cstring>

struct Node {
    int data;
    int prv, nxt;
};

const int MAXN = 1000005;

int N, front, pv = 1, back = 1;
Node node[MAXN];

void insert(int prv, int data)
{
    pv++;
    node[pv].data = data;
    node[pv].prv = prv;
    node[pv].nxt = node[prv].nxt;

    node[node[prv].nxt].prv = pv;
    node[prv].nxt = pv;
}

int pop(int nd)
{
    int ret = node[nd].data;
    node[node[nd].prv].nxt = node[nd].nxt;
    node[node[nd].nxt].prv = node[nd].prv;
    return ret;
}

int main()
{
    scanf("%d", &N);
    node[front].data = -1;
    node[front].prv = -1;
    node[front].nxt = back;

    node[back].data = -1;
    node[back].prv = front;
    node[back].nxt = -1;

    char op[16];
    while(N--) {
        scanf("%s", op);

        if(strcmp(op, "PUSH") == 0) {
            int x;
            scanf(" %d", &x);
            insert(node[back].prv, x);
        } else if(strcmp(op, "POP") == 0) {
            if(node[front].nxt == back) printf("-1\n");
            else printf("%d\n", pop(node[front].nxt));
        } else if(strcmp(op, "FRONT") == 0) {
            if(node[front].nxt == back) printf("-1\n");
            else printf("%d\n", node[node[front].nxt].data);
        } else if(strcmp(op, "BACK") == 0) {
            if(node[front].nxt == back) printf("-1\n");
            else printf("%d\n", node[node[back].prv].data);
        }
    }

    int sz = 0;
    for(int i = node[front].nxt; i != back; i = node[i].nxt) sz++;
    printf("%d\n", sz);
    for(int i = node[front].nxt; i != back; i = node[i].nxt) printf("%d ", node[i].data);
}