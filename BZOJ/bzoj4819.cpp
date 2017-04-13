#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 233
#define M 53333 
#define inf 1e12
#define eps 1e-10
using namespace std;
int a[N][N],b[N][N],inq[M],q[M],pv[M],pe[M],mak,n,qh,qt,s,t;double d[N];
double x[N],e[N][N],y[N],lak[N];int vis[N],link[N];
bool find(int u,int mak){
    vis[u]=mak;
    for (int i=1;i<=n;i++)
      if (vis[i+n]!=mak){
          double tmp=x[u]+y[i]-e[u][i];
          if (fabs(tmp)<eps){
              vis[i+n]=mak;
              if (link[i]==-1||find(link[i],mak)){
                  link[i]=u;return true;
              }
          }else lak[i]=min(lak[i],tmp);
      }
    return false;
}
double KM(){
    double sum=0;
    for (int i=1;i<=n;i++){
        x[i]=-inf;
        for (int j=1;j<=n;j++)
          x[i]=max(x[i],e[i][j]);
    }
    memset(y,0,sizeof(y));
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++) lak[j]=inf;
        while (true){
            ++mak;
            if (find(i,mak)) break;
            double tmp=inf;
            for (int k=1;k<=n;k++)
              if (vis[k+n]!=mak)
                tmp=min(tmp,lak[k]);
            for (int k=1;k<=n;k++)
              if (vis[k]==mak) x[k]-=tmp;
            for (int k=1;k<=n;k++)
              if (vis[k+n]==mak) y[k]+=tmp;
              else lak[k]-=tmp;
        }
    }
    for (int i=1;i<=n;i++)
      if (link[i]!=-1)
        sum+=e[link[i]][i];
    return sum;
}
double chk(double lim){
    memset(vis,0,sizeof(vis));
    mak=0;memset(link,-1,sizeof(link));
    for (int i=1;i<=n;i++)
      for (int j=1;j<=n;j++)
        e[i][j]=(double)a[i][j]-lim*(double)b[i][j];
    return KM();
}
int main(){
	freopen("ball.in","r",stdin);
	freopen("boll.out","w",stdout);
	int i,j;
	double sum=0.0;
	scanf("%d",&n);s=0;t=n+n+1;
 	for(i=1;i<=n;i++)
 		for(j=1;j<=n;j++)
 			scanf("%d",&a[i][j]),sum+=a[i][j];
 	for(i=1;i<=n;i++)
 		for(j=1;j<=n;j++)
 			scanf("%d",&b[i][j]);
	double ans=0.0;
	for(double l=0.0,r=sum,o;fabs(r-l)>eps;chk(o=(l+r)/2)>-eps?l=o,ans=max(ans,o):r=o);
	printf("%.6lf",ans); 
}
 
