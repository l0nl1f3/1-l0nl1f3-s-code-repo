#include<bits/stdc++.h>
#define N 888888
#define ll long long
using namespace std;
int n,q,a[N],tag[N][10];ll seg[N][10];
void mrg(int p){
	for(int i=0;i<10;i++)
		seg[p][i]=seg[p+p][i]+seg[p+p+1][i];
}
void put(int t,int p){
	int i,s[10];
	for(i=0;i<10;i++)s[i]=seg[t][i],seg[t][i]=0;
	for(i=0;i<10;i++)seg[t][tag[p][i]]+=seg[p][i];
	for(i=0;i<10;i++)tag[t][i]=tag[p][i];
}
void pd(int p){
	put(p+p,p);
	put(p+p+1,p);
	for(int i=0;i<10;i++)tag[p][i]=i;
}
void build(int p,int l,int r){
	for(int i=0;i<10;i++)tag[p][i]=i;
	if(l==r){
		for(int q=a[l],b=1;q;q/=10,b*=10)
			seg[p][q%10]+=b;
	}else{
		build(p+p,l,(l+r)/2);
		build(p+p+1,(l+r)/2+1,r);
		mrg(p);
	}
}
void mdf(int p,int l,int r,int a,int b,int x,int y){
	if(a>r||b<l)return;
	if(a<=l&&r<=b){
		seg[p][y]+=seg[p][x];
		seg[p][x]=0;
		for(int i=0;i<10;i++)
			if(tag[p][i]==x)tag[p][i]=y;
	}
	pd(p);
	int o=(l+r)/2; 
	mdf(p+p,l,o,a,b,x,y);
	mdf(p+p+1,o+1,r,a,b,x,y);
	mrg(p);
}
ll qry(int p,int l,int r,int a,int b){
	if(a>r||b<l)return 0;
	if(a<=l&&b<=r){
		ll res=0;
		for(int i=0;i<10;i++)
			res+=seg[p][i];
		return res;
	}
	pd(p);
	return qry(p+p,l,(l+r)/2,a,b)+qry(p+p+1,(l+r)/2+1,r,a,b);
}
int main(){
	int i,j,k;
	scanf("%d%d",&n,&q);
	for(i=1;i<=n;i++)scanf("%d",a+i);	
	build(1,1,n);
	for(;q--;){
	}
	return 0;
}
