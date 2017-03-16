#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<set>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
int n,a[100010],g[100010],c[100010][30],d[100010][30],w[100010];
long long m,b[100010],f[100010],l,r;
multiset<long long> t;
inline int maxa(int i,int j)
{
    return a[i]>a[j]?i:j;
}
inline int minb(int i,int j)
{
    int k=w[j-i];
    return min(c[i][k],c[j-(1<<k)+1][k]);
}
inline bool check(long long p)
{
    int i,j,l=1,r=0;
    long long k,s=0;
    for(i=1,j=0;i<=n;i++)
      {
       while(l<=r && a[i]>=a[g[r]])
         {
          if(l<r)
            t.erase(t.find(f[g[r-1]]+a[g[r]]));
          r--;
         }
       g[++r]=i;
       if(l<r)
         t.insert(f[g[r-1]]+a[g[r]]);
       s+=b[i];
       while(s>p)
         s-=b[++j];
       while(j>=g[l])
         {
          t.erase(t.find(f[g[l]]+a[g[l+1]]));
          l++;
         }
       f[i]=f[j]+a[g[l]];
       k=*t.begin();
       if(l<r && k<f[i])
         f[i]=k;
      }
    t.clear();
    return f[n]<=m;
}
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int i,j,k;
	scanf("%d%I64d",&n,&m);
	for(i=1;i<=n;i++)
	  scanf("%d%I64d",&a[i],&b[i]);
	for(i=n;i>0;i--)
	  {
       c[i][0]=b[i];
       d[i][0]=i;
       for(j=1;j<=20;j++)
         {
          c[i][j]=min(c[i][j-1],c[min(n,i+(1<<j-1))][j-1]);
          d[i][j]=maxa(d[i][j-1],d[min(n,i+(1<<j-1))][j-1]);
         }
      }
    for(i=2;i<=n;i++)
      w[i]=w[i>>1]+1;
    for(i=1,k=0;i<=n;)
      {
       for(j=i;j<n && a[d[j+1][20]]>=minb(i,j);j=d[j+1][20]);
       a[++k]=a[i];
       b[k]=b[i];
       for(i++;i<=j;i++)
         {
          a[k]=max(a[k],a[i]);
          b[k]+=b[i];
         }
      }
    n=k;
    for(i=1;i<=n;i++)
      {
       l=max(l,b[i]);
       r+=b[i];
      }
    while(l<r)
      if(check(l+r>>1))
        r=(l+r>>1);
      else
        l=(l+r>>1)+1;
    cout<<l<<"\n";
	return 0;
}

