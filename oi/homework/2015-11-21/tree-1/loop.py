D = int(input('D: '))
I = int(input('I: '))

n = 0
for i in range(0, D):
    n += 2 ** i
# print(n)

T = []
for i in range(0, n + 1):
    T.append(False)

L = []
for i in range(0, 2 ** (D - 1) + 1):
    # L.append(0)
    L.append('')


def left(x):
    return x * 2


def right(x):
    return x * 2 + 1

for i in range(1, len(L)):
    depth = 1
    pos = 1

    # path = []
    # path.append(str(pos))
    while depth < D:
        flag = T[pos]
        T[pos] = not flag

        if flag is False:
            pos = left(pos)
        else:
            pos = right(pos)

        # path.append(str(pos))
        depth += 1

    # print(' -> '.join(path))
    # L[i] = pos
    L[i] = str(pos)

# print(' '.join(L))
L[0] = L[len(L) - 1]
print(L[I % (len(L) - 1)])

# print(' '.join(L))
