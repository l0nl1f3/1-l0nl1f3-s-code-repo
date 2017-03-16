#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cmath>
using namespace std;

typedef long long llong;
inline llong gen(llong x, llong y)
{
	if (y & 1)
		return ((y + 2) >> 1) / 3 * 2 + x + 1;
	else
		return ((y - 1) >> 1) / 3 * 2 + x + 2;
}
inline llong solve(llong x, llong y)
{
	x = abs(x), y = abs(y);
	if (x <= y)
	{
		int t(x);
		x = y;
		y = t;
	}
	static const llong table[8][8] =
	{
		{0},
		{3,2},
		{2,1,4},
		{3,2,3,2},
		{2,3,2,3,4},
		{3,4,3,4,3,4},
		{4,3,4,3,4,5,4},
		{5,4,5,4,5,4,5,6}
	};
	if (x < 8 && y < 8)
		return table[x][y];
	if (y * 2 <= x)
		switch (x & 3)
		{
		case 0:
			return floor(x / 2.0) + (y & 1);
		case 1:
			return ceil(x / 2.0) + (y & 1);
		case 2:
			return floor(x / 2.0) - (y & 1) + 1;
		case 3:
			return ceil(x / 2.0) - (y & 1) + 1;
		}
	return gen(x / 2, y - x / 2 + (x & 1));
}

int main()
{
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i)
	{
		llong x, y;
		scanf("%lld%lld", &x, &y);
		printf("%lld\n", solve(x, y));
	}
	//for (int i = 1; i < 5005; ++i)
	//{
	//	for (int j = 0; j <= i; ++j)
	//	{
	//		printf("%lld\t", solve(i, j));
	//	}
	//	putchar('\n');
	//}
}