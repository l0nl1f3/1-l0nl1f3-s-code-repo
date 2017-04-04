#include<bits/stdc++.h>
#define N 100000+10 
#define M 100000
using namespace std;
int n,m,b,a[N],c[N],ans[N];bitset<N>bs,rs;
struct Q{int l,r,o,x,i;}q[N];
bool cmp(Q a,Q b){return a.l/::b<b.l/::b||(a.l/::b==b.l/::b&&a.r<b.r);} 
void ins(int x){
	if(!c[x]){
		//-bs.set(x);rs.set(M-x);
			bs[x]=1;rs[M-x]=1;
	}
	c[x]++;
}
void del(int x){
	if(!--c[x]){
		bs[x]=0;rs[M-x]=0;
	}
}
int main(){
	int i,j,k,p,l;
	for(scanf("%d%d",&n,&m),b=sqrt(n),i=1;i<=n;i++)scanf("%d",a+i);
	for(i=1;i<=m;i++)scanf("%d%d%d%d",&q[i].o,&q[i].l,&q[i].r,&q[i].x),q[i].i=i;
	for(sort(q+1,q+m+1,cmp),i=j=1,k=0;i<=m;i++){
		while(k<q[i].r)ins(a[++k]);
		while(j>q[i].l)ins(a[--j]);
		while(k>q[i].r)del(a[k--]);
		while(j<q[i].l)del(a[j++]);
		p=0;
		
		if(q[i].o==1){
			if((bs&(bs<<q[i].x)).count()>0)p=1;
		} 
		if(q[i].o==2){
			if((rs&(bs<<(M-q[i].x))).count()>0)p=1;
		}
		if(q[i].o==3){
			for(l=1;l*l<M;l++)
				if(!(q[i].x%l)&&c[l]&&c[q[i].x/l])p=1;
		}
		ans[q[i].i]=p;
	}
	for(i=1;i<=m;i++)puts(ans[i]?"hana":"bi");
	return 0;
}
