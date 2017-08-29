import math
MaxN = 101234

n, K = map(int, raw_input().split());

x = map(int, raw_input().split());
y = map(int, raw_input().split());

z = [0] * len(x);

for i in range(0, len(x)):
	z[i] = x[i] * x[i] + y[i] * y[i];

z.sort();

print int(math.ceil(math.sqrt(z[K - 1])))