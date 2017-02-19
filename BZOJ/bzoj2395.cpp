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
#define M 12345
int n,m,f[M];Pii res;
struct edge{int a,b,c,d,e;}e[M];
bool C(edge a,edge b){return a.c<b.c;}
bool D(edge a,edge b){return a.d<b.d;}
bool E(edge a,edge b){return a.e<b.e;}

int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
Pii fst(){
	for(int i=1;f[i]=i,i<n;i++);
	Pii ans=mp(0,0);
	for(int i=1,x,y;i<=m;i++){
		x=find(e[i].a);y=find(e[i].b);
		if(x!=y)f[x]=y,ans.fi+=e[i].c,ans.se+=e[i].d;
	}
 	ll p=ans.fi*(ll)ans.se,q=res.fi*(ll)res.se;
	if(p<q||(p==q&&ans.fi<res.fi))res=ans;
	return ans;
}
int det(Pii a,Pii b,Pii c){return (c.se-a.se)*(b.fi-a.fi)-(b.se-a.se)*(c.fi-a.fi);}
void div(Pii a,Pii b){
	for(int i=1;i<=m;i++)e[i].e=e[i].d*(a.fi-b.fi)-e[i].c*(a.se-b.se);
	sort(e+1,e+m+1,E);
	Pii c=fst();
	if(det(a,b,c)<=0)return;
	div(a,c);div(c,b);
}
int main(){
	n=gi;m=gi;res=mp(1e233,1e233);
	for(int i=1;i<=m;i++)e[i].a=gi+1,e[i].b=gi+1,e[i].c=gi,e[i].d=gi;
	Pii lb,ub;
	sort(e+1,e+m+1,C);lb=fst();
	sort(e+1,e+m+1,D);ub=fst();
	div(ub,lb);
	printf("%d %d\n",res.fi,res.se);
	return 0;
}

