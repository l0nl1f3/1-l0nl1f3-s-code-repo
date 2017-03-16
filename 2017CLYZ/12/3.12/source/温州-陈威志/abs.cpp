#include<cstdio>
#include<cmath>
#define L long long
#define P 998244353
using namespace std;
int l[21],r[21],n;

int mi(int t,int num)
{
  if(num==1) return t;
  int tt=mi(t,num/2),ttt;
  if(num&1)  ttt=(L)tt*tt%P*t%P;
  else ttt=(L)tt*tt%P;
  return ttt;
}

int main()
{
  int i;
  freopen("abs.in","r",stdin);
  freopen("abs.out","w",stdout); 
  scanf("%d",&n);
  for(i=1;i<=n;i++) scanf("%d%d",&l[i],&r[i]);
  if((L)l[1]*r[1]>=0LL)
    {
	  l[1]=abs(l[1]),r[1]=abs(r[1]);
	  printf("%d",((L)l[1]+r[1])*mi(2,P-2)%P);
	}
  else
    {
	  l[1]=abs(l[1]),r[1]=abs(r[1]);
	  printf("%d",((L)l[1]*l[1]%P+(L)r[1]*r[1]%P)*mi(((L)l[1]+r[1])%P*2%P,P-2)%P);
	}
} 
