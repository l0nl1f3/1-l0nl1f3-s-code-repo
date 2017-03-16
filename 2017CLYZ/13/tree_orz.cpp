#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define L long long
using namespace std;
int n,m,t,r,x[1010],f[1010][2100],a[1010],b[2010],c[2010],d[2010],u[2],rev[2100],p,q=998244353;
int orzfang[1010];
inline int power(int a,int b)
{
    if(!b)
      return 1;
    int c=power(a,b>>1);
    c=(L)c*c%q;
    if(b&1)
      c=(L)c*a%q;
    return c;
}
inline void FFT(int a[],int p)
{
    int i,j,k,v,w,x,y;
    for(i=0;i<r;i++)
      if(i<rev[i])
        swap(a[i],a[rev[i]]);
    for(i=1;i<=t;i++)
      for(j=0,v=power(u[p],1<<t-i);j<r;j+=(1<<i))
        for(k=j,w=1;k<j+(1<<i-1);k++,w=(L)w*v%q)
          {
           x=a[k];
           y=(L)a[k+(1<<i-1)]*w%q;
           a[k]=(x+y>=q?(x+y-q):(x+y));
           a[k+(1<<i-1)]=(x-y<0?(x-y+q):(x-y));
          }
    k=power(r,q-2);
    if(p)
      for(i=0;i<r;i++)
        a[i]=(L)a[i]*k%q;
}
inline void mul(int a[],int b[])
{
    int i;
    FFT(a,0);
    FFT(b,0);
    for(i=0;i<r;i++)
      a[i]=(L)a[i]*b[i]%q;
    FFT(a,1);
    for(i=m+1;i<r;i++)
      a[i]=0;
}
inline void dp(int i,int j)
{
    int k,l;
    f[i][0]=1;
    for(k=1;k<=m;k++)
      f[i][k]=(L)f[i][k-1]*x[i]%q*orzfang[k]%q;
    for(k=a[i];k>0;k=d[k])
      if(b[k]!=j)
        {
         dp(b[k],i);
         for(l=1;l<m;l++)
           f[b[k]][l]=(L)f[b[k]][l]*c[k]%q;
         f[b[k]][m]=0;
         mul(f[i],f[b[k]]);
        }
    p=(p+f[i][m])%q;
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int i,j,k,l,v;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	  scanf("%d",&x[i]);
	for(i=1;i<n;i++)
	  {
       scanf("%d%d%d%d",&j,&k,&l,&v);
       b[2*i-1]=k;
       c[2*i-1]=(L)l*power(v,q-2)%q;
       d[2*i-1]=a[j];
       a[j]=2*i-1;
       b[2*i]=j;
       c[2*i]=(L)l*power(v,q-2)%q;
       d[2*i]=a[k];
       a[k]=2*i;
      }
    for(r=1,t=0;r<=2*m;r<<=1,t++);
    u[0]=power(3,q-1>>t);
    u[1]=power(u[0],q-2);
    for(i=1;i<r;i++)
      rev[i]=(rev[i>>1]>>1)+((i&1)<<t-1);
    for(i=1;i<=m;i++)
      orzfang[i]=power(i,q-2);
    dp(1,0);
    for(i=1;i<=m;i++)
      p=(L)p*i%q;
    p=(p+q)%q;
    printf("%d\n",p);
	return 0;
}

