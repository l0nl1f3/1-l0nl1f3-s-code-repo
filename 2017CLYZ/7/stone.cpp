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
#define N 17
#define M (1<<N)
int T,n,win,ans,a[M],d[M];
#define orz void
orz fateice(){		
	ans=0;
	for(int i=1;i<(1<<n);i++){
		if((n+d[i]+1&1)&&(win^a[i])-a[i]<=a[i/2])
			if((i<<1)<(1<<n)&&(win^a[i])<a[i])ans+=2;
			else ans++;
	}
}
int main(){
	//FO(stone);
	T=gi;
	while(T--){
		n=gi;win=0; 
		for(int i=1;i<(1<<n);i++){
			a[i]=gi;d[i]=d[i>>1]+1;	
			if((d[i]&1)==(n&1))win^=a[i]; 
		}
		if(!win)puts("0");
		else{fateice();}
	}
	return 0;
}

