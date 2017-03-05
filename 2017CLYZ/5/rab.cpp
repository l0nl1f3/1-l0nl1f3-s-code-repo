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
#define N 101234
#define M 201234
//dp[i] i节点的颜色
// 
int n,f[N],g[N],ch[N];vector<int>ans;
struct edge{int to,nxt;}e[M];int cnt,lst[N],s[N];//s[i]=r_i-b_i
void ins(int a,int b){e[++cnt]=(edge){b,lst[a]};lst[a]=cnt;}
void lnk(int a,int b){ins(a,b);ins(b,a);} 
int dfs0(int x,int f=0){
	s[x]=0;
	for(int i=lst[x],b;i;i=e[i].nxt){
		if((b=e[i].to)==f)continue;
		dfs0(b,x);
		if(!g[b])s[x]++; 
		if(!(g[b]-1))s[x]--; 
	}
	if(ch[x]){
		if(!s[x])g[x]=-1;
		else g[x]=(s[x]<0); 
	}
}
int dfs1(int x,int f=0){
	if(!ch[x]){
		//cout<<x<<"!@!#"<<endl;
		ans.pb(x);
	}
	for(int i=lst[x],b;i;i=e[i].nxt){
		if((b=e[i].to)!=f){
			if(!(~g[b])||!(~s[b])){
				dfs1(b,x);
			}
		}
	}
}
int main(){
	FO(rab); 
	int T=gi;
	while(T--){
		n=gi;
		ans.clear();
		memset(ch,0,sizeof(ch));
		memset(lst,0,sizeof(lst));
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		cnt=0;
		for(int i=1;i<=n;i++){
			f[i]=gi;
			if(f[i]){
				ch[f[i]]++;
				lnk(f[i],i);
			}
		}
		for(int i=1;i<=n;i++)g[i]=gi;
		dfs0(1);
		//for(int i=1;i<=n;i++)cout<<g[i]<<' ';
		//puts("");
		if(g[1]==1){puts("-1");continue;}
		if(~g[1]){
			//cout<<"branch 1\n";	
			for(int i=2;i<=n;i++)if(!ch[i]&&g[i]==-1)ans.pb(i);
		}
		else {
			//cout<<"branch 2\n";
			dfs1(1);
		}
		
		printf("%d ",ans.size());
		if(!ans.size())puts("");
		sort(ans.begin(),ans.end());
		for(int i=0;i<ans.size();i++)printf("%d%c",ans[i],"\n "[i+1<ans.size()]);		
	}
	return 0;
}

