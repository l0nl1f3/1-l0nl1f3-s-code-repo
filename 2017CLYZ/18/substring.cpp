//当P中任意一个字符串成为T的子串后A就会停止输入，求当他停止输入时字符串的期望长度 
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
#define fil(x) memset((x),0,sizeof((x)))
#define gmax(a,b) (a)=max((a),(b))	
#define gmin(a,b) (a)=min((a),(b))
#define infll 1001001001001001001LL
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
il int read(){bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;}
#define gi read()
#define N 200
#define mod 1000000007
int T,n; 
int Fp(int a,int n){
	int res=1;
	a<0?a+=mod:(a>=mod)?a-=mod:0; 
	for(;n;n>>=1,a=(ll)a*a%mod)if(n&1)res=(ll)res*a%mod;
	return res;
}
int a[N][N],x[N];
void swap(int x,int y,int r){for(int i=0;i<r;i++)swap(a[i][x],a[i][y]);}
void gauss(int row,int col){
	int r=0,c=0;
	for(;r<row&&c<col;r++,c++){
		int pivot=r;
		for(int i=r+1;i<row;i++)if(abs(a[i][c])>abs(a[pivot][c]))pivot=i;
		if(pivot!=r)swap(a[pivot],a[r]);
		if(!a[r][c]){r--;continue;}
		for(int i=r+1;i<row;i++){
			if(!a[i][c])continue;
			int t1=a[r][c],t2=a[i][c];
			for(int j=c;j<=col;j++){
				a[i][j]=((ll)a[i][j]*t1-(ll)a[r][j]*t2)%mod;
				if(a[i][j]<0)a[i][j]+=mod;
			}
		}
	}
	for(int i=r;i<row;i++)if(a[i][col])return;
	for(int i=0,j;i<col&&j<row;i++){
		if(!a[i][i]){
			for(j=i+1;j<col;j++)if(a[i][j])break;
			if(j<col)swap(i,j,row);
		}
	}
	for(int i=col-1;~i;i--){
		ll t=a[i][col];
		for(int j=i+1;j<col;j++)t=((t-a[i][j]*(ll)x[j]%mod)%mod+mod)%mod;
		x[i]=t*Fp(a[i][i],mod-2)%mod;
	}
}
struct ACM{
	#define SZ N 
	int qs[SZ],ch[SZ][29],fail[SZ],cnt[SZ],e,rot,h,t;
	void init(){e=rot=1;fil(ch);fil(cnt);fil(fail);fil(x);fil(a);}
	void insert(char* s){
	    int cur=rot;
	    for(int i=0;s[i];i++){
	        int c=s[i]-'a';
	        if(!ch[cur][c])ch[cur][c]=++e;
	        cur=ch[cur][c];
	    }
	    cnt[cur]++;
	}
	void bfail(){
	    h=t=0; fail[rot]=rot;
	    for(int i=0;i<26;i++){
	        if(!ch[rot][i]) {
	            ch[rot][i]=rot;continue;
	        }
	        fail[ch[rot][i]]=rot;
	        qs[t++]=ch[rot][i];
	    }
	    while(h!=t){
	        int cur=qs[h++];
	        for(int c=0;c<26;c++){
	            if(!ch[cur][c]) ch[cur][c]=ch[fail[cur]][c];
	            else{
	                fail[ch[cur][c]]=ch[fail[cur]][c];
	                qs[t++]=ch[cur][c];
	            }
	        }
	    }
	}
	int dp(){
		for(int i=1;i<=e;i++){
			if(cnt[i]){
				a[i-1][i-1]=1;a[i-1][e]=0;
				continue; 
			} 
			a[i-1][i-1]=a[i-1][e]=26;
			for(int j=0;j<26;j++)a[i-1][ch[i][j]-1]--;
		}
		gauss(e,e);
		return x[0]; 
	}
}zzq;char s[N];
int main(){
	FO(substring);T=gi;
	while(T--){
    	n=gi;
    	zzq.init();
    	for(int i=1;i<=n;i++)scanf("%s",s),zzq.insert(s);
    	zzq.bfail();
    	cout<<zzq.dp()<<endl;
	}
	return 0;
}

