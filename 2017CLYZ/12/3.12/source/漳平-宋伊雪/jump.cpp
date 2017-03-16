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

const int maxn = 3000;
const int N = (1 << 10);
const int dx[8] = {1,1,2,2,-1,-1,-2,-2};
const int dy[8] = {2,-2,1,-1,-2,2,-1,1};
const int Add[4] = {3,0,1,2};
typedef long long LL;

struct Point{
	int x,y; Point(){}
	Point(int x,int y): x(x),y(y){}
	bool operator < (const Point &B) const
	{
		if (x < B.x) return 1;
		if (x > B.x) return 0;
		return y < B.y;
	}
};

int T,f[maxn][maxn];
bool vis[maxn][maxn];
char ch[20];

queue <Point> Q;

int Get(int x) {return x + 1200;}

void Print(LL x)
{
	if (!x) {puts("0"); return;} int len = 0;
	while (x) ch[++len] = x % 10LL,x /= 10LL;
	for (int i = len; i; i--) putchar(ch[i] + '0'); puts("");
}

LL Calc1(int x)
{
	if (x <= 3)
	{
		if (x == 1) return 2;
		if (x == 2) return 4;
		return 2;
	}
	int tmp = x / 3;
	if (x % 3 != 0) ++tmp;
	return 2LL * tmp;
}

LL Calc2(int x)
{
	if (x <= 3)
	{
		if (x == 1) return 3;
		if (x == 2) return 2;
		return 3;
	}
	x -= 3; int tmp = x / 4;
	if (x % 4 != 0) ++tmp;
	LL ret = 2LL * tmp + 1LL * Add[tmp % 4];
	return ret;
}

int main()
{
	#ifdef DMC
		freopen("DMC.txt","r",stdin);
	#else
		freopen("jump.in","r",stdin);
		freopen("jump.out","w",stdout);
	#endif
	
	vis[Get(0)][Get(0)] = 1; Q.push(Point(0,0));
	while (!Q.empty())
	{
		Point k = Q.front(); Q.pop();
		//printf("%d %d\n",k.x,k.y);
		for (int i = 0; i < 8; i++)
		{
			int xx = k.x + dx[i],yy = k.y + dy[i];
			if (xx < -N || N < xx || yy < -N || N < yy) continue;
			if (vis[Get(xx)][Get(yy)]) continue;
			f[Get(xx)][Get(yy)] = f[Get(k.x)][Get(k.y)] + 1;
			vis[Get(xx)][Get(yy)] = 1; Q.push(Point(xx,yy));
		}
	}
	cin >> T;
	while (T--)
	{
		int x,y; scanf("%d%d",&x,&y);
		if (abs(x) <= 1000 && abs(y) <= 1000)
		{
			printf("%d\n",f[Get(x)][Get(y)]);
			continue;
		}
		LL Ans = 0; x = abs(x); y = abs(y);
		if (min(x,y) > 0) Ans = Calc1(min(x,y));
		if (x != y) Ans += Calc2(abs(x - y)); Print(Ans);
	}
	return 0;
}
