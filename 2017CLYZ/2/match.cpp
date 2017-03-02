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
#define L 1001234 
int T,C,n,m,pn,s[L],t[L],lst[L],nxt[L],da[L],db[L],p[L]; 
bool c(int i,int j){return (da[i]>j&&da[j+1]>j)||da[j+1]==da[i];}
bool d(int i,int j){return (db[i]>j&&da[j+1]>j)||da[j+1]==db[i];}
int main(){
	FO(match);
	for(T=gi,C=gi;T--;puts("")){
		m=gi;n=gi;
		for(int i=1;i<=m;i++)t[i]=gi;
		for(int i=1;i<=n;i++)s[i]=gi;
		memset(lst,0,sizeof(lst));		
		for(int i=1;i<=n;i++)da[i]=i-lst[s[i]],lst[s[i]]=i;
		da[n+1]=db[m+1]=0; 
		for(int i=2,j=nxt[1]=0;i<=n;i++){
			while(j&&!c(i,j))j=nxt[j];
			nxt[i]=(j+=c(i,j)); 
		}memset(lst,0,sizeof(lst));
		for(int i=1;i<=m;i++)db[i]=i-lst[t[i]],lst[t[i]]=i;
		for(int i=1,j=pn=0;i<=m;i++){
			while(j&&!d(i,j))j=nxt[j];
			if((j+=d(i,j))==n)p[++pn]=i-n+1;
		}
		printf("%d\n",pn);for(int i=1;i<=pn;i++)printf("%d ",p[i]);
	}
	return 0;
}

