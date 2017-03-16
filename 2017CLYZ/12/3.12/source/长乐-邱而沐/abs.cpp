#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define p 998244353
using namespace std;

typedef long long LL;

inline int Ksm(int x, int y)
{
	int ans = 1;
	for(; y; x = (LL)x * x % p, y >>= 1)
		if(y & 1) ans = (LL)ans * x % p;
	return ans;
}

inline int solve(int x)
{
	return (LL)x * (LL)x % p * Ksm(2, p - 2) % p;
}

int main()
{
	freopen("abs.in", "r", stdin);
	freopen("abs.out", "w", stdout);
	
	int n;
	scanf("%d", &n);
	if(n == 1)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(x < 0 && y < 0) x = -x, y = -y, swap(x, y);
		if(x * y > 0) cout << ((solve(y) - solve(x)) % p + p) % p;
		else cout << (solve(-x) + solve(y)) % p;
	}
}