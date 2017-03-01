//不开O2 0.6s
//-O2 0.1s 
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
char B[1<<26],*S=B;int F(){for(;*S<'-';S++);register int x=*S++-'0';for(;*S>='0';x=(x<<3)+(x<<1)+*S++-'0');return x;}
char U[1<<26],*O=U,stk[20];
#define PuT(b) register int i=0;for(;b;stk[++i]=x%10+'0',x/=10);for(;i;*O++=stk[i--]);
void pri(register int x){if(!x)*O++='0';else{PuT(x)};}
void pr9(register int x){PuT(i<9);}
#define MoD 1000000000
#define pr(x,c) (x<0?*O++='-',x=-x:1,x>=MoD?pri(x/MoD),pr9(x%MoD):pri(x),*O++=c)
#define gi F()
#define N 1001234
vector<int> v[N];int zis[N];
bool cmp(int a,int b){return zis[a]<zis[b];}
int n,L,a[N],b[N],c[N],d[N],siz[N];
void bfs(int x){while(!b[x])v[L].pb(x),b[x]=1,x=a[x];}
int main(){
	FO(permutation);
	fread(B,1,1<<26,stdin);
	n=gi;
	for(int i=1;i<=n;i++)a[i]=gi;
	for(int i=1;i<=n;i++)if(!b[i])++L,siz[L]=L,bfs(i);
	for(int i=1;i<=n;i++)d[zis[i]=v[i].size()]++;
	for(int i=2;i<=n;i+=2)if(d[i]&1){puts("-1");return 0;}
	sort(siz+1,siz+L+1,cmp);
	for(int p=1,i,k;p<=L;p++){
		//cerr<<"QAQ"<<p;
		k=v[i=siz[p]].size();
		if(k&1)for(int j=0;j<k;j++)c[v[i][j]]=v[i][(j+k/2+1)>=k?j+k/2+1-k:j+k/2+1];
		else{
			for(int j=0;j<k;j++){
				c[v[i][j]]=v[siz[p+1]][j];
				c[v[siz[p+1]][j]]=v[i][(j+1)>=k?j+1-k:j+1];
			}p++;
		}
	}
	for(int i=1;i<=n;i++)pr(c[i],' ');
	fwrite(U,1,O-U,stdout);
}
/*
求G'^2=G的G'
奇循环X偶循环

偶循环：

分裂成两个环<->合并两个环

奇循环：

根号->分成两部分遍历
 */

