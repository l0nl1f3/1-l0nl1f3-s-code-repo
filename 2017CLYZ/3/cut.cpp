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
#define M 1234 
char s[M];int mx,n,m,q;
bitset<M>a,b[M],ans,e,f;
bitset<M>bs[M],bl[M],b0[M];
void ins(int p){
	int d=-1;b[p]^=a;
	for(int i=1;i<=q;i++)if(b0[i][p])d=i,i=q+1;
	if(d>=1){
		e=a;f=b0[d];
		for(int i=d+1;i<=q;i++)if(b0[i][p])b0[i]^=f;
		for(int i=0;i<=mx;i++)if(bl[i][p])bl[i]^=f;
		b0[d].reset();
	}else{
		for(int i=0;i<=mx;i++)if(bl[i][p])d=i,i=mx+1;
		if(d>=0){
			for(int i=d+1;i<=mx;i++)if(bl[i][p])bs[i]^=bs[d],bl[i]^=bl[d];
			e=bs[d]^a;f=bl[d];
			bs[d].reset();bl[d].reset();
		}else e=b[p],f.reset(),f.set(p);
	}
	for(int i=mx;~i;i--){
		if(!e[i])continue;
		if(!bs[i][i])bs[i]=e,bl[i]=f,i=0;
		else e^=bs[i],f^=bl[i];
	}
	if(!e.any())b0[++q]=f;
}
void gv(){
	scanf("%s",s);
	int n=strlen(s);gmax(mx,n-1);
	a.reset();
	for(int i=n-1;~i;i--)a[n-i-1]=s[i]-'0';
} 
int main(){
	n=gi;m=gi;
	for(int x,y,i=1;i<=m;i++){
		x=gi-1;y=gi-1;gv();
		ins(x);ins(y);
		for(int i=mx;~i;i--)if(bs[i].any()&&!ans[i])ans^=bs[i];
		bool f=0;
		for(int i=mx;~i;i--){
			if(!ans[i])continue;
			for(int j=i;~j;j--)putchar(ans[j]?'1':'0');
			f=1;break;
		}		
		puts(f?"":"0");ans.reset();
	}
	return 0;
}

