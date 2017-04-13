#include<bits/stdc++.h>
#define N 101234
#define M 1800000
using namespace std;
int n,m,lx[N],ly[N],x[N],y[N],z[N];
struct PT{
	int cnt,ls[M],rs[M],s[M],rot[N];long long sh[M];
	void edt(int &x,int y,int l,int r,int p,int d){
		ls[x=++cnt]=ls[y];rs[x]=rs[y];
		s[x]=s[y]+1;sh[x]=sh[y]+d;if(l==r)return;
		if(p<=(l+r)/2)edt(ls[x],ls[y],l,(l+r)/2,p,d);
		else edt(rs[x],rs[y],(l+r)/2+1,r,p,d); 
	}
	long long query(int x,int y,int k){
		long long ans=0,cnt=0;
		for(int l=1,r=n,o,t;l<r;){
			o=(l+r)/2;t=s[ls[y]]-s[ls[x]]; 
			if(k<=t){
				cnt+=s[rs[y]]-s[rs[x]];
				ans+=sh[rs[y]]-sh[rs[x]];
				x=ls[x];y=ls[y];r=o;
			}else{
				cnt-=t;k-=t;
				ans-=sh[ls[y]]-sh[ls[x]];
				x=rs[x];y=rs[y];l=o+1;
			}
        }
        return ans-sh[y]/s[y]*cnt;
	}
}xt,yt;
int main(){
	int i,j,k;
	for(scanf("%d%d",&n,&m),i=1;i<=n;i++)
		scanf("%d",x+i);
	for(i=1;i<=n;i++){
		scanf("%d",&j);
		ly[i]=y[i]=x[i]-j;
		lx[i]=x[i]=x[i]+j;
	}
	sort(ly+1,ly+n+1);
	sort(lx+1,lx+n+1);
	for(i=1;i<=n;i++){
		x[i]=lower_bound(lx+1,lx+n+1,x[i])-lx;
		y[i]=lower_bound(ly+1,ly+n+1,y[i])-ly;
	}
	for(i=1;i<=n;i++){
		xt.edt(xt.rot[i],xt.rot[i-1],1,n,x[i],lx[x[i]]);
		yt.edt(yt.rot[i],yt.rot[i-1],1,n,y[i],ly[y[i]]);
	}
	for(i=1;i<=m;i++){
		scanf("%d%d",&j,&k);
		printf("%.2lf\n",(double)(xt.query(xt.rot[j-1],xt.rot[k],(k-j+2)/2)+yt.query(yt.rot[j-1],yt.rot[k],(k-j+2)/2))/2.0);
	}
	return 0;
}
