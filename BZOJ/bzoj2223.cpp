#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define inf 1001001001
#define infll 1001001001001001001LL
#define ll long long
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define Ri register int
#define gc getchar()
#define il inline
il int read(){
	bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;
}
#define gi read()
#define ig read()
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
#define ZY 10234567
#define N 523456
int n,m,C,ls[ZY],rs[ZY],s[ZY],rt[N],a[N];
vector<int>vec;
void insert(int x,int &y,int l,int r,int d){
	s[y=++C]=s[x]+1;
	if(l==r)return;
	int mid=(l+r)/2;
	ls[y]=ls[x];rs[y]=rs[x];
	
	if(d<=mid)insert(ls[x],ls[y],l,mid,d);
	else insert(rs[x],rs[y],mid+1,r,d);		
}
int main(){
	n=gi;int lim=gi;
	for(int i=1;i<=n;i++){
		int x=gi; 
		insert(rt[i-1],rt[i],1,lim,x);
	}m=gi;
	while(m--){
		int l,r,mid,k,ans=0;
		l=gi;r=gi;
		int x=rt[l-1],y=rt[r],d=(r-l+1)/2;
		l=1;r=lim;
		while(l!=r){
			if(s[y]-s[x]<=d){
				l=0;break;
			}
			mid=(l+r)/2;
			if(s[ls[y]]-s[ls[x]]>d){
				r=mid;
				x=ls[x];y=ls[y];
			}else if(s[rs[y]]-s[rs[x]]>d){
				l=mid+1;x=rs[x];y=rs[y];
			}else{
				l=0;break;	
			}
		}
		printf(l?"yes ":"no ");
		if(l)printf("%d",l);puts(""); 
	}
	return 0;
}
