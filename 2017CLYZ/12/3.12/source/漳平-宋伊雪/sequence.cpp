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

const int maxn = 1E5 + 10;
const int T = 18;
typedef long long LL;
const LL INF = 1E15;

struct data{
	int Num; LL F,G; data(){}
	data(int Num,LL F,LL G): Num(Num),F(F),G(G){}
	bool operator < (const data &B) const {return F + G > B.F + G;}
};

int n,head,tail,q[maxn],A[maxn],B[maxn],Min[maxn],Max[maxn],Nex[maxn];
LL m,L,now,R,sum[maxn],f[maxn],g[maxn];
bool bo[maxn],inq[maxn];

priority_queue <data> Q;

LL Get_top(int tmp)
{
	while (!Q.empty())
	{
		data k = Q.top();
		if (!inq[k.Num] || k.G != g[k.Num] || k.Num < tmp) Q.pop();
		else return k.F + k.G;
	}
	return INF + 233LL;
}

bool Judge(LL now)
{
	int tmp; tmp = tail = 0; head = 1;
	memset(inq,0,sizeof(inq)); while (!Q.empty()) Q.pop();
	for (int i = 1; i <= n; i++)
	{
		f[i] = INF; g[i] = 0;
		while (sum[i] - sum[tmp] > now) ++tmp;
		while (head <= tail && q[head] < tmp)
			inq[Nex[q[head]]] = 0,++head;
		while (head <= tail && A[q[tail]] <= A[i])
			inq[Nex[q[tail]]] = 0,--tail;
		if (head <= tail && Nex[q[tail]] < i)
		{
			g[Nex[q[tail]]] = A[i]; inq[Nex[q[tail]]] = 1;
			Q.push(data(Nex[q[tail]],f[Nex[q[tail]]],A[i]));
		}
		q[++tail] = i; if (!bo[i]) continue; f[i] = Get_top(tmp);
		if (Nex[tmp] < q[head]) f[i] = min(f[i],f[Nex[tmp]] + 1LL * A[q[head]]);
	}
	return f[n] <= m;
}

int getint()
{
	char ch = getchar(); int ret = 0;
	while (ch < '0' || '9' < ch) ch = getchar();
	while ('0' <= ch && ch <= '9')
		ret = ret * 10 + ch - '0',ch = getchar();
	return ret;
}

int main()
{
	#ifdef DMC
		freopen("DMC.txt","r",stdin);
	#else
		freopen("sequence.in","r",stdin);
		freopen("sequence.out","w",stdout);
	#endif
	
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		Max[i] = A[i] = getint();
		sum[i] = Min[i] = B[i] = getint();
		R += 1LL * B[i]; L = max(L,1LL * B[i]);
	}
	for (int i = n - 1; i; i--) Max[i] = max(Max[i],Max[i + 1]);
	for (int i = 2; i <= n; i++) Min[i] = min(Min[i],Min[i - 1]),sum[i] += sum[i - 1];
	for (int i = 1; i < n; i++) if (Min[i] > Max[i + 1]) bo[i] = 1; bo[n] = bo[0] = 1;
	for (int i = n; i; i--) Nex[i] = bo[i] ? i : Nex[i + 1];
	while (R - L > 1LL)
	{
		LL mid = L + R >> 1LL;
		if (Judge(mid)) R = mid;
		else L = mid;
	}
	cout << (Judge(L) ? L : R) << endl;
	return 0;
}
