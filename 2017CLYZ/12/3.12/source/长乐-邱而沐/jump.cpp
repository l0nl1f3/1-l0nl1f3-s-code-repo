#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int a[10][10];

inline int solve1(int x)
{
	if(x == 1) return 3;
	if(x & 1) return solve1(x - 1) + 1;
	if(x % 4 == 0) return x >> 1;
	return (x - 2) / 2 + 2;
}

inline int solve2(int x)
{
	if(x == 1) return 2;
	if(x == 2) return 4;
	return ((x / 3) + (x % 3 != 0)) * 2;
}

inline int solve(int x, int y) // x > y
{
	if(!y) return solve1(x);
	if(x == y) return solve2(x);
	if(x > y * 2) return y + solve1(x - y * 2);
	int xx = x % 3, yy = y % 3;
	return (x / 3 * 3 + y / 3 * 3) / 3 + a[xx][yy];
}

int main()
{	
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);
	
	//(1, 0) 本来是3，改为1会对？？
	
	a[0][0] = 0;  a[0][1] = 1;  a[0][2] = 2;  a[0][3] = 3;
	a[1][0] = 1;  a[1][1] = 2;  a[1][2] = 1;  a[1][3] = 2;
	a[2][0] = 2;  a[2][1] = 1;  a[2][2] = 2;  a[2][3] = 3;
	a[3][0] = 3;  a[3][1] = 2;  a[3][2] = 3;  a[3][3] = 2;
	
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(x < 0) x = -x;
		if(y < 0) y = -y;
		if(x < y) swap(x, y);
		cout << solve(x, y) << "\n";
	}
}