#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<stack>
#include<bitset>
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;

typedef long long LL;
const LL mo = 998244353;

int n,l,r,Inv;

int Mul(const LL &x,const LL &y) {return x * y % mo;}
int Add(const int &x,const int &y) {return (x + y) % mo;}

int ksm(int x,int y)
{
	int ret = 1;
	for (; y; y >>= 1)
	{
		if (y & 1) ret = Mul(ret,x);
		x = Mul(x,x);
	}
	return ret;
}

int main()
{
	#ifdef DMC
		freopen("DMC.txt","r",stdin);
	#else
		freopen("abs.in","r",stdin);
		freopen("abs.out","w",stdout);
	#endif
	
	cin >> n >> l >> r;
	Inv = ksm(2,mo - 2);
	if (l >= 0) printf("%d\n",Mul(Add(l,r),Inv));
	else if (r <= 0) printf("%d\n",Mul(-l-r,Inv));
	else
	{
		int len = r - l,x,y; x = y = 0;
		len = ksm(len,mo - 2);
		x = Mul(Inv,Mul(r,Mul(r,len)));
		y = Mul(Inv,Mul(-l,Mul(-l,len)));
		printf("%d\n",Add(x,y));
	}
	return 0;
}
