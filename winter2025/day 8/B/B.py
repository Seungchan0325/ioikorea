import random
N = 64
Iter = 5000
def dfs(g, par, sz, u, p):
    par[u] = p
    sz[u] = 1
    for v in range(N):
        if g[u][v] != 0 and v != p:
            dfs(g, par, sz, v, u)
            sz[u] += sz[v]
print(Iter)
acc = [0 for _ in range(N)]
for _ in range(Iter):
    g = [[0 for _ in range(N)] for _ in range(N)]
    a = []
    b = [i for i in range(0, N)]
    v1 = random.choice(b)
    a.append(v1)
    b.remove(v1)
    v2 = random.choice(b)
    a.append(v2)
    b.remove(v2)
    g[v1][v2] += 1
    g[v2][v1] += 1
    for i in range(N-2):
        v1 = random.choice(a)
        v2 = random.choice(b)
        a.append(v2)
        b.remove(v2)
        g[v1][v2] += 1
        g[v2][v1] += 1
    par = [0 for _ in range(N)]
    sz = [0 for _ in range(N)]
    dfs(g, par, sz, 0, -1)
    print(N)
    print(*par)
    sz.sort()
    for i in range(N):
        acc[i] += sz[i]
for i in range(N):
    acc[i] /= Iter
print(*sz)