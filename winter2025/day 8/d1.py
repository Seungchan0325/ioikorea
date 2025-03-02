N = 1000
DD = []
for k in range(0, N):
    D = [0.0 for _ in range(N)]
    D[k] = 1.0
    for i in range(1, N):
        s = 0.0
        for j in range(0, N):
            s += D[j]
        for j in range(0, N):
            if i == j: continue
            D[j] *= (N-1) / N
            D[j] += D[i] / N
        D[i] = s / N
    DD.append(D) 
import matplotlib.pyplot as plt
plt.matshow(DD)
plt.colorbar()
# s = 0
# for i in range(0, N):
#     s += D[i]
#     print(i, D[i])
# print(D[200])
# print(s)