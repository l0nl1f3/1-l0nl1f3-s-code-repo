//s[i...j] 与 s[j+1...k] 都是回文的三元组，求i*k的和 
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
#define N 2001234
#define mod 1000000007
#define div2 ((mod+1)/2) 
int T,n,p[N];char s[N],t[N]; 
void orz(int &x,int y){y>=mod?y-=mod:0;if((x+=(y<0?y+=mod:y))>=mod)x-=mod;}
int manacher(){
	int mx=0,id;
	memset(p,0,sizeof(p));
	for(int i=1;i<n;i++){
		p[i]=mx>i?min(mx-i,p[2*id-i]):1;
		while(s[i-p[i]]==s[i+p[i]])++p[i];
		if(mx<i+p[i])mx=i+p[i],id=i;
	} 
} 
#define FILL(x) memset((x),0,sizeof(x)) 
int ps[N],ss[N],pd[N],sd[N];
int main(){
	FO(triple);
	T=gi;
	while(T--){
		scanf("%s",t+1);
		s[(n=0)++]='@';s[n++]='#';
		for(int i=1;t[i];i++)s[n++]=t[i],s[n++]='#';s[n]=0;
		FILL(ps);FILL(ss);FILL(pd);FILL(sd);
		manacher();
		for(int i=1,l,r;i<n;i++){
			l=i-p[i]+1;r=i+p[i]-1;
            orz(ps[l],r);orz(ps[i+1],(i-l)-r);
			orz(pd[l+1],-1);orz(pd[i+1],1);
			orz(ss[i],i);orz(ss[r+1],(r-i)-i);
			orz(sd[i+1],-1);orz(sd[r+1],1);
        }
        for(int i=1;i<n;i++){
        	orz(pd[i],pd[i-1]);orz(ps[i],ps[i-1]);orz(ps[i],pd[i]);
        	orz(sd[i],sd[i-1]);orz(ss[i],ss[i-1]);orz(ss[i],sd[i]);
		}
		int ans=0;n=strlen(t+1);
		for(int i=1;i<n;i++){
			int a=i*2,b=(i+1)*2;
			ss[a]=(ll)ss[a]*div2%mod;
			ps[b]=(ll)ps[b]*div2%mod;
			orz(ans,(ll)ss[a]*ps[b]%mod);
		}
		printf("%d\n",ans);
	}
	return 0;
}
 
