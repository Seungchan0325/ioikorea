import random
import matplotlib.pyplot as plt

N = 1000
Iter = 100000

def gen1(N):
    a = [i for i in range(N)]
    for i in range(N):
        j = random.randint(i, N-1)
        a[i], a[j] = a[j], a[i]
    return a

def gen2(N):
    a = [i for i in range(N)]
    for i in range(N):
        j = random.randint(0, N-1)
        a[i], a[j] = a[j], a[i]
    return a

cnt = 0
for i in range(Iter):
    a = gen2(N)
    if 500 == a[499]: cnt += 1
print(cnt/Iter)

# dist1 = [[0 for _ in range(N)] for _ in range(N)]
# A = 0
# for i in range(Iter):
#     a = gen1(N)
#     for j in range(N):
#         A += abs(a[j] - j)
#         dist1[j][a[j]] += 1

# dist2 = [[0 for _ in range(N)] for _ in range(N)]
# B = 0
# for i in range(Iter):
#     a = gen2(N)
#     for j in range(N):
#         B += abs(a[j] - j)
#         dist2[j][a[j]] += 1

# for i in range(N):
#     for j in range(N):
#         dist1[i][j] /= Iter
#         dist2[i][j] /= Iter
plt.matshow(dist1)
plt.colorbar()
plt.matshow(dist2)
plt.colorbar()

# plt.show()

# print(A/Iter)
# print(B/Iter)