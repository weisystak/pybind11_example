import example
import numpy as np
import time

size = 1000

a = example.Matrix(size, size)
b = example.Matrix(size, size)

for i in range(a.rows()):
    for j in range(a.cols()):
        a[i,j] = 10
        b[i,j] = 20
for i in range(a.rows()):
    for j in range(a.cols()):
        pass
        # print(a[i, j])

s = time.time()

c = a.add(b)
c = np.array(c, copy = False)
# print(c)
e = time.time()
d = e - s
print(d)


a  = np.empty((size,size))
b  = np.empty((size,size))
for i in range(size):
    for j in range(size):
        a[i, j] = 10
        b[i, j] = 20

s = time.time()
c = a+b
print(time.time() - s)