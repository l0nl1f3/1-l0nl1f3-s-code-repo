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
#define ob pop_back
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
#define N 501234
int n,qn,f[N],L[N],R[N],o[N],x[N],y[N];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
struct SegTree{
	vector<int>s[N+N];int M;
	/*void cha(int x,int l,int r,int p,int q){
		while(!s[x].empty()){
			i=s[x].back();s[x].ob();
			gmin(L[p],L[i]);gmax(R[p],R[i]);
			f[i]=p;		
		}
		if(l==r)return;
		if(p<=(l+r)/2)cha(x+x,l,(l+r)/2,p,q);
		else cha(x+x+1,(l+r)/2+1,r,p,q);
	}*/
	void cha(int x,int p){
		for(int r=x+M,i;r;r>>=1){
			while(!s[r].empty()){
				i=s[r].back();s[r].ob();
				gmin(L[p],L[i]);gmax(R[p],R[i]);
				f[i]=p;		
			}
		} 
	}
	void ins(int a,int b,int p){
		for(int l=a+M,r=b+M;l^r^1;l>>=1,r>>=1){
			if(~l&1)s[l^1].pb(p);
			if(r&1)s[r^1].pb(p);
		}
	}
	void init(int n){for(M=1;M<n;M<<=1);}
}zkw;vector<int>v;
int main(){
	FO(interval);n=gi;
	for(int i=1;f[i]=i,i<n;i++);
	for(int i=1;i<=n;i++){
		o[i]=gi;x[i]=gi;y[i]=gi;
		if(o[i]==1)v.pb(x[i]),v.pb(y[i]);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	zkw.init(v.size()+2);
	for(int i=1;i<=n;i++){
		if(o[i]==1){
			++qn; 
			L[qn]=x[i]=lower_bound(v.begin(),v.end(),x[i])-v.begin()+1;
			R[qn]=y[i]=lower_bound(v.begin(),v.end(),y[i])-v.begin()+1;
			zkw.cha(x[i],qn);zkw.cha(y[i],qn);
			zkw.ins(L[qn],R[qn],qn);
		}else{
			x[i]=find(x[i]);y[i]=find(y[i]);
			puts(L[y[i]]<=L[x[i]]&&R[x[i]]<=R[y[i]]?"YES":"NO");
		}
	}
	return 0;
}

