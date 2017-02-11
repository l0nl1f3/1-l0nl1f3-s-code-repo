//一个数在取sqrt 操作loglog次
//线段树上有nlog n个节点，值域为m
//T(n)=O(nlog n loglogm) 
#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<bitset>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define fi first
#define se second
#define il inline
#define mp make_pair
#define pb push_back
#define ll long long
#define gc getchar()
#define inf 1001001001
#define Ri register int
#define Pii pair<int,int>
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define CHANGE 2
#define QUERY 1
#define N 123456
int n,q,a[N];
struct Segment_Tree{
	ll sum[N*20];bool s[N*20];
	void pu(int k){
		sum[k]=sum[k+k]+sum[k+k+1];
		s[k]=s[k+k]&s[k+k+1];
	}
	void build(int k,int l,int r){
		if(l==r)sum[k]=a[l],s[k]=(a[l]<=1);
		else{build(k+k,l,(l+r)/2);build(k+k+1,(l+r)/2+1,r);pu(k);}
	}
	ll query(int k,int l,int r,int p,int q){
		if(p>r||q<l)return 0;
		if(p<=l&&r<=q)return sum[k];
		return query(k+k,l,(l+r)/2,p,q)+query(k+k+1,(l+r)/2+1,r,p,q);
	}
	void change(int k,int l,int r,int p,int q){
		if(p>r||q<l||s[k])return;
		if(l==r){s[k]=((sum[k]=sqrt(sum[k]))<=1); return;}
		change(k+k,l,(l+r)/2,p,q);change(k+k+1,(l+r)/2+1,r,p,q);
		pu(k);
	}
	ll query(int l,int r){return query(1,1,n,l,r);}
	ll change(int l,int r){change(1,1,n,l,r);}
}T;	
int main(){
	//FO(qaq);
	n=gi;
	for(int i=1;a[i]=gi,i<n;i++);
	q=gi;T.build(1,1,n);
	for(int i=1,o,l,r;i<=q;i++){
		o=gi;l=gi;r=gi;if(l>r)swap(l,r);
		if(o==CHANGE)T.change(l,r);
		else printf("%lld\n",T.query(l,r));
	}
	return 0;
}

