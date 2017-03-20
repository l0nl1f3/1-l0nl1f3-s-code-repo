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
#define N 205
#define M 400000 
int n,s,t,ect=1,a[N],b[N],cnt[N],lst[N],inq[N],pe[N],pv[M];ll dis[N],c[N];
struct edge{int to,nxt;ll cst;int cap;}e[M];
void ins(int a,int b,ll c,int d){e[++ect]=(edge){b,lst[a],c,d};lst[a]=ect;}
void lnk(int a,int b,ll c,int d){ins(a,b,c,d),ins(b,a,-c,0);}
queue<int>q; 
int spfa(){
	q.push(s);inq[s]=1;
	for(int i=s;i<=t;i++)dis[i]=-infll;dis[s]=0;
	while(!q.empty()){
		int c=q.front();q.pop();inq[c]=0;
		for(int i=lst[c],b;b=e[i].to,i;i=e[i].nxt){
			if(e[i].cap>0&&dis[c]+e[i].cst>dis[b]){
				dis[b]=dis[c]+e[i].cst;
				pe[b]=i;pv[i]=c;
				if(!inq[b])q.push(b),inq[b]=1; 
			}
		} 
	}
	return dis[t]>-infll;
}
ll max_cost_flow(){
	ll ans=0,sum=0;
	while(spfa()){
		int cap=inf;ll cst=0;
		for(int i=t;i!=s;i=pv[pe[i]])gmin(cap,e[pe[i]].cap);
		for(int i=t;i!=s;i=pv[pe[i]]){
			cst+=e[pe[i]].cst;
			e[pe[i]].cap-=cap;e[pe[i]^1].cap+=cap;	
		}
		if(sum+cst*cap<0){
			return ans+sum/-cst;
		}else ans+=cap,sum+=cap*cst;
	}
	return ans;
}
int main(){
	FO(qaq);t=n=gi;t++;
	for(int i=1;a[i]=gi,i<n;i++);
	for(int i=1;b[i]=gi,i<n;i++); 
	for(int i=1;c[i]=gi,i<n;i++);
	for(int i=1;i<=n;i++){
		int k=a[i];
		for(int j=2;j*j<=k;j++)while(k%j==0)k/=j,cnt[i]++;
		if((cnt[i]+=(k>1))&1)lnk(s,i,0,b[i]);
		else lnk(i,t,0,b[i]);
	}
	for(int i=1;i<=n;i++){
		if(cnt[i]&1)
		for(int j=1;j<=n;j++){
			if(~cnt[j]&1){
				if(a[j]%a[i]==0&&cnt[j]==cnt[i]+1)lnk(i,j,c[i]*c[j],inf); 
				if(a[i]%a[j]==0&&cnt[i]==cnt[j]+1)lnk(i,j,c[i]*c[j],inf);
			}
		}
	}
	cout<<max_cost_flow();
	return 0;
}

