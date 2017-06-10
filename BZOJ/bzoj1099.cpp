#include<bits/stdc++.h>
using namespace std;
#define N 501234
#define inf ~0U>>1
#define ll long long
template<typename T> 
inline bool cmin(T &a,const T &b){ 
	return a>b?a=b,1:0; 
}
int n,seg[N],rg[N],lg[N],loc[N],h[N],f[N],a[N],b[N],c[N],d[N],ans[N];
ll org,B[N],H[N];
inline int findl(ll x,int d=0){
	if(!d)x=x*n;
	int l=1,r=n,mid,t;
	while(l<=r)if(B[mid=(l+r)>>1]>=x)r=(t=mid)-1;else l=mid+1;
	return t;
}
inline int findr(ll x){
	x=x*n+n-1;
	int l=1,r=n,mid,t;
	while(l<=r)if(B[mid=(l+r)>>1]<=x)l=(t=mid)+1;else r=mid-1;
	return t;
}
#define o (l+r)/2
void build(int p,int l,int r){
	seg[p]=inf;
	if(l==r)return;
	build(p+p,l,o);
	build(p+p+1,o+1,r);
}
int mdf(int p,int l,int r,int q,int d){
	if(l==r)
		return seg[p]=d;
	if(q<=o)
		mdf(p+p,l,o,q,d);
	else
		mdf(p+p+1,o+1,r,q,d);
	return seg[p]=min(seg[p+p],seg[p+p+1]);
}
int qry(int p,int l,int r,int a,int b){
	if(l>b||r<a)  return inf;
	if(l<=a&&b<=r)return seg[p];
	return min(qry(p+p,l,o,a,b),qry(p+p+1,o+1,r,a,b));
}
int query(int l,int r,int p){
	int x=loc[p-1],y=loc[p+1],ans=inf;
	if(x>y)swap(x,y);
	if(y<l||x>r)
		cmin(ans,qry(1,1,n,l,r));
	else if(l<=x&&y<=r){
		cmin(ans,qry(1,1,n,l,x-1));
		cmin(ans,qry(1,1,n,x+1,y-1));
		cmin(ans,qry(1,1,n,y+1,r));
	}else if(l<=x){
		cmin(ans,qry(1,1,n,l,x-1));
		cmin(ans,qry(1,1,n,x+1,r));
	}else{
		cmin(ans,qry(1,1,n,l,y-1));
		cmin(ans,qry(1,1,n,y+1,r));
	}
	return ans; 
} 
#undef o
int L(int i,int j){
	if(i>n||j>n||i<1||j<1)
		return 0;
	return (h[i]-h[j]<0?h[j]-h[i]:h[i]-h[j]);
} 
int Q(int i,int j){
	return L(i-1,j)+L(i+1,j)+L(i,j-1)+L(i,j+1)-f[i]-f[j];
}
struct swp{
	int i,l,r,v,p;
	swp(int i,int l,int r,int v,int p):
		i(i),l(l),r(r),v(v),p(p){}
	swp(){}
}q[N];int qn;
bool cmp1(swp a,swp b){return a.i==b.i?a.p<b.p:a.i<b.i;}
bool cmp2(swp a,swp b){return a.i==b.i?a.p<b.p:a.i>b.i;}
template<bool(*cmp)(swp,swp)>
void gans(){
	int i,j;
	sort(q+1,q+qn+1,cmp);
	build(1,1,n);
	for(i=1;i<=qn;i++){
		if(!q[i].v)
			mdf(1,1,n,q[i].l,q[i].v);
		else{
			j=query(1,q[i].l,q[i].v);
			if(j<inf)
				cmin(ans[q[i].p],q[i].v+j);
		}
	}
}
int i;
void build11(){
	for(qn=0,i=2;i<n;i++){
		q[++qn]=swp(c[i],loc[i],0,a[i]+b[i]-h[i]*2-f[i],0);
		q[++qn]=swp(h[i],findr(c[i]),0,a[i]+b[i]-h[i]*2-f[i],i);
	}
} 
void build12(){
	for(qn=0,i=2;i<n;i++){
		q[++qn]=swp(c[i],loc[i],0,abs(a[i]-b[i])-h[i]*2-f[i],0);
		q[++qn]=swp(d[i],loc[i],0,0,n);
		q[++qn]=swp(h[i],findr(c[i]),0,a[i]+b[i]-f[i],i);
	}
} 
void build13(){
	for(qn=0,i=2;i<n;i++){
		q[++qn]=swp(d[i],loc[i],0,-h[i]*2-a[i]-b[i]-f[i],0);
		q[++qn]=swp(h[i],findr(c[i]),0,a[i]+b[i]+h[i]*2-f[i],i);
	}
} 
void build21(){
	for(qn=0,i=2;i<n;i++){
		q[++qn]=swp(c[i],loc[i],0,a[i]+b[i]-f[i],0);
		q[++qn]=swp(h[i],findl(c[i]),findr(d[i]),abs(a[i]-b[i])-h[i]*2-f[i],i);
	}
} 
void build22(){
	for(qn=0,i=2;i<n;i++){
		q[++qn]=swp(c[i],loc[i],0,abs(a[i]-b[i])-f[i],0);
		q[++qn]=swp(d[i],loc[i],0,0,n);
		q[++qn]=swp(h[i],findl(c[i]),findr(d[i]),abs(a[i]-b[i])-f[i],i);
	}
} 
void build23(){
	for(qn=0,i=2;i<n;i++){
		q[++qn]=swp(d[i],loc[i],0,-a[i]-b[i]-f[i],0);
		q[++qn]=swp(h[i],findl(c[i]),findr(d[i]),abs(a[i]-b[i])+h[i]*2-f[i],i);
	}
} 
void build31(){
	for(qn=0,i=2;i<n;i++){
		q[++qn]=swp(c[i],loc[i],0,a[i]+b[i]+h[i]*2-f[i],0);
		q[++qn]=swp(h[i],findl(d[i]),0,-a[i]-b[i]-h[i]*2-f[i],i);
	}
} 
void build32(){
	for(qn=0,i=2;i<n;i++){
		q[++qn]=swp(c[i],loc[i],0,abs(a[i]-b[i])+h[i]*2-f[i],0);
		q[++qn]=swp(d[i],loc[i],0,0,n);
		q[++qn]=swp(h[i],findl(d[i]),0,-a[i]-b[i]-f[i],i);
	}
} 
void build33(){
	for(qn=0,i=2;i<n;i++){
		q[++qn]=swp(d[i],loc[i],0,h[i]*2-a[i]-b[i]-f[i],0);
		q[++qn]=swp(h[i],findl(d[i]),0,h[i]*2-a[i]-b[i]-f[i],i);
	}
} 
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",h+i);
		org+=L(i+1,i);
	}
	if(n>2){
		f[1]=L(1,2);
		f[n]=L(n,n-1);
	    for(i=2;i<n;i++){
	    	c[i]=min(a[i]=h[i-1],b[i]=h[i+1]);
			d[i]=max(a[i],b[i]);
			f[i]=L(i,i-1)+L(i,i+1);
	    }
	    for(i=3;i<=n;i++)	cmin(ans[1],Q(1,i)),cmin(ans[i],Q(1,i));
	    for(i=2;i<n-1;i++)	cmin(ans[n],Q(i,n)),cmin(ans[i],Q(i,n));
	    for(i=1;i<n;i++)	cmin(ans[i],Q(i,i+1)),cmin(ans[i+1],Q(i,i+1));
	} 
	if(n>4){
		for(i=1;i<=n;i++)B[i]=H[i]=(ll)h[i]*n+i-1;
		sort(B+1,B+n+1);
		for(i=1;i<=n;i++)loc[i]=findl(H[i],1);
	}
	build11();gans<cmp2>();
	build12();gans<cmp1>();
	build13();gans<cmp1>();
	build21();gans<cmp2>();
	build22();gans<cmp1>();
	build23();gans<cmp1>();
	build31();gans<cmp2>();
	build32();gans<cmp1>();
	build33();gans<cmp1>();
 	for(i=1;i<=n;i++)printf("%lld\n",org+ans[i]);
	return 0;
}
 
