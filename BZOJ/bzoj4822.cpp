#include<cstdio>
#include<algorithm>
#define N 1001234
#define ll long long
#define find(x)  lower_bound(ls+1,ls+ns+1,(x))-ls
using namespace std;
int n,m,qn,ns,x[N],y[N],x1[N],x2[N],y1[N],y2[N],v[N],lx[N],ly[N],ls[N];ll bit[N],ans[N];
struct Q{
	int x,y,k,i,v;
	Q(){}Q(int x,int y,int k,int i,int v):x(x),y(y),k(k),i(i),v(v){}
}q[N];
bool cmp(Q a,Q b){return a.x<b.x||(a.x==b.x&&(!a.k&&b.k));}
void add(int r,int d){for(;r<=ns;r+=r&-r)bit[r]+=d;}
ll sum(int r,ll res=0){for(;r;r-=r&-r)res+=bit[r];return res;}
int main(){
	freopen("task.in","r",stdin);
	freopen("task.out","w",stdout);
	int i,j,k;
	for(scanf("%d%d",&n,&m),i=1;i<=n;i++)scanf("%d%d%d",x+i,y+i,v+i),ls[++ns]=y[i];
	for(i=1;i<=m;i++)scanf("%d%d%d%d",x1+i,y1+i,x2+i,y2+i),ls[++ns]=y2[i],ls[++ns]=y1[i]-1;
	sort(ls+1,ls+ns+1);ns=unique(ls+1,ls+ns+1)-ls-1;
	for(i=1;i<=n;i++)q[++qn]=Q(x[i],find(y[i]),0,0,v[i]);
	for(i=1;i<=m;i++){
		j=find(y1[i]-1);k=find(y2[i]);
		q[++qn]=Q(x1[i]-1,j,1,i,0);
		q[++qn]=Q(x1[i]-1,k,-1,i,0);
		q[++qn]=Q(x2[i],j,-1,i,0);
		q[++qn]=Q(x2[i],k,1,i,0);
	}
	sort(q+1,q+qn+1,cmp);
	for(i=1;i<=qn;i++)
		if(q[i].k)ans[q[i].i]+=sum(q[i].y)*q[i].k;
		else add(q[i].y,q[i].v);
    for(i=1;i<=m;i++)printf("%lld\n",ans[i]);
	return 0;
}
