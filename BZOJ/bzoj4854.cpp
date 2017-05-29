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
#define N 100
ll m,ans[N],f[N],nxt[N],bit[N];
int n,L,lst;
bool qaq(int x){for(int i=1;i<=x;i++)if(ans[i]!=ans[L-x+i])return 0;return 1;}
ll qwq(){
	for(int i=1;i<=n;i++){
		if(i<=L)f[i]=!nxt[i];
		else{
			f[i]=bit[i-L];
			for(int j=1;j<=i/2;j++){
				ll k=(L<=j)?bit[i-j-j]:((L-i+j<=0)?bit[i-j-L]:qaq(L-i+j));
				f[i]-=f[j]*k;
			}
		}
	}
	return f[n];
}
void ins(int x){
	ans[++L]=x;
	if(L==1)return;
	for(;lst&&ans[lst+1]!=ans[L];lst=nxt[lst]);
	nxt[L]=(lst+=(ans[lst+1]==ans[L]));
}
int main(){
	bit[0]=1;
	for(int i=1;i<=64;i++)bit[i]=bit[i-1]*2;
	for(int T=gi;T--;puts("")){	
		n=gi;cin>>m;L=lst=0;
		printf("%lld\n",qwq());
		for(int i=1,j;i<=n;i++){
			j=lst;ins(0);ll k=qwq();
			if(k<m)m-=k,lst=j,--L,ins(1);
		}
		for(int i=1;i<=n;i++)printf("%c",ans[i]+'a');
	}	
	return 0;
}

