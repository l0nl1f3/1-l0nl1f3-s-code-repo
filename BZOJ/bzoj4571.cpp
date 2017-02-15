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
#define N 223456
#define M 4001234 
#define S (1<<18)-1
int n,m,a[N];
struct PersisdentTree{
	int ls[M],rs[M],s[M],rt[N],tot;
	void insert(int x,int &y,int l,int r,int p){
		s[y=++tot]=s[x]+1;
		if(l==r)return;
		ls[y]=ls[x];rs[y]=rs[x];
		if(p<=(l+r)/2)insert(ls[x],ls[y],l,(l+r)/2,p);
		else insert(rs[x],rs[y],(l+r)/2+1,r,p);
	}
	int query(int x,int y,int l,int r,int a,int b){
		if(l>b||r<a)return 0;
		if(a<=l&&r<=b)return s[y]-s[x];
		return query(ls[x],ls[y],l,(l+r)/2,a,b)+query(rs[x],rs[y],(l+r)/2+1,r,a,b);
	}
	void insert(int p,int q){insert(rt[p-1],rt[p],0,S,q);}
	int query(int x,int y,int l,int r){return query(rt[x-1],rt[y],0,S,l,r);}
}PT;
int main(){
	FO(qaq);
	n=gi;m=gi;for(int i=1;i<=n;i++)PT.insert(i,a[i]=gi);
	for(int b,x,l,r,L,R,ans;m--;){
		b=gi;x=gi;l=gi;r=gi;ans=0;
		for(int i=17;~i;i--){
			if(!(b>>i&1))ans^=(1<<i);
            L=max(ans-x,0),R=ans+(1<<i)-1-x;  
            if(R<0||!PT.query(l,r,L,R))ans^=(1<<i);  
		}
		printf("%d\n",ans^b);
	} 
	return 0;
}

