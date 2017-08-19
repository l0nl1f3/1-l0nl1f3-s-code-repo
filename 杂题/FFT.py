import math
import time

def DFT(a,n,g):
	w=range(n)
	Pe = math.pi
	if g:
		for i in range(n):
			w[i] = complex(math.cos(2 * Pe * i/n), -math.sin(2 * Pe * i/n))
	else:
		for i in range(n):
			w[i] = complex(math.cos(2 * Pe * i/n), math.sin(2 * Pe * i/n))
	i = j = 0
	while i < n:
		if i < j:
			k = a[i]
			a[i] = a[j]
			a[j] = k
		k = n/2
		j ^= k
		while j < k:
			k /= 2
			j ^= k
		i += 1
	
	i = 2
	m = 1
	while i <= n:
		j = 0
		while j < n:
			for k in range(m):
				t = a[j + m + k] * w[n/i * k]
				a[j + m + k] = a[j + k] - t
				a[j + k] += t
			j += i
		i *= 2
		m *= 2
	if g:
		for i in range(n):
			a[i] /= n 
n = int(input())
m = int(input())

t0 = time.clock()
N = 1
while N <= n + m:
	N *= 2
a = range(N)
b = range(N)
for i in range(N):
	a[i] = b[i] = 0

print "Input Cost ", time.clock() - t0, "ms \n";

t0 = time.clock()

for i in range(n + 1):
	a[i] = int(input())
for i in range(m + 1):
	b[i] = int(input())

DFT(a, N, 0)
DFT(b, N, 0)
for i in range(N):
	a[i] *= b[i]
DFT(a, N, 1)

print "DFT Cost ", time.clock() - t0, " ms\n";
#for i in range(n + m + 1):
#	print int(a[i].real),

print
