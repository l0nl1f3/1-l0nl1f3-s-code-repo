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
#define N 123456
#define S 1234567 
struct Segment_Tree{
	int sum[S],en[S],tag[S];
	int d[N],_n;
	void getd(int n,int *a){_n=n;for(int i=1;d[i]=a[i],i<n;i++);}
	int build(int k,int l,int r){
		tag[k]=en[k]=sum[k]=0;
		if(l==r)return sum[k]=d[l];
		build(k+k,l,(l+r)/2);
		build(k+k+1,(l+r)/2+1,r);
		return sum[k]=sum[k+k]+sum[k+k+1]; 
	}
	void cover(int k,int l,int r,int p,int q,int d){
		if(p>r||q<l)return;
		if(p<=l&&r<=q)tag[k]=1,sum[k]=(en[k]=d)?(r-l+1):0;
		else{
			if(tag[k])pd(k,l,r);
			cover(k+k,l,(l+r)/2,p,q,d);
			cover(k+k+1,(l+r)/2+1,r,p,q,d);
			sum[k]=sum[k+k]+sum[k+k+1];
		}
	}
	void pd(int k,int l,int r){
		tag[k+k]=tag[k+k+1]=tag[k];
		tag[k]=0;
		en[k+k]=en[k+k+1]=en[k];
		en[k]?
		sum[k+k]=((l+r)/2-l+1),sum[k+k+1]=(r-(l+r)/2):
		sum[k+k]=sum[k+k+1]=0;
	}
	int query(int k,int l,int r,int p,int q){
		if(p>r||q<l)
			return 0;
		if(p<=l&&r<=q)
			return sum[k];
		else{
			if(tag[k])pd(k,l,r);
			return query(k+k,l,(l+r)/2,p,q)+query(k+k+1,(l+r)/2+1,r,p,q);
			//sum[k]=sum[k+k]+sum[k+k+1];
		}
	} 
	int query(int l,int r){if(l<=r)return query(1,1,_n,l,r);}
	void cover(int l,int r,int o){if(l<=r)cover(1,1,_n,l,r,o);}
	void debug(){
		printf("...debug");
		for(int i=1;i<=_n;i++)printf("%d ",query(i,i));
		puts("");	
	}
}T;
int n,m,k;
int a[N],b[N],l[N],r[N],op[N];
int main(){
	FO(qaq);
	n=gi;m=gi;
	for(int i=1;a[i]=gi,i<n;i++);
	for(int i=1;op[i]=gi,l[i]=gi,r[i]=gi,i<m;i++);
	k=gi;
	int lb,rb,mid;
	for(lb=1,rb=n;mid=(lb+rb)/2,lb<=rb;T.query(k,k)?lb=mid+1:rb=mid-1){
		for(int j=1;j<=n;j++)b[j]=(a[j]>mid);
		T.getd(n,b);T.build(1,1,n);
		for(int j=1;j<=m;j++){
			int ans=T.query(l[j],r[j]);
			if(!op[j]){
				T.cover(l[j],r[j]-ans,0);
				T.cover(r[j]-ans+1,r[j],1);
			}
			else{
				T.cover(l[j],l[j]+ans-1,1);
				T.cover(l[j]+ans,r[j],0);
			}
		}
	}
	cout<<lb<<endl;
	return 0;
}

