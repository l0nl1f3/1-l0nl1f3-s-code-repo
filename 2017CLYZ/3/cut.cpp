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
int n,m,x[M],y[M],v[M],ans[M];
void bf20(){
	for(int i=1;i<=m;i++){
		x[i]=gi;y[i]=gi;
		string s;cin>>s;
		for(int j=0;j<s.size();j++)v[i]=(v[i]<<1)+(s[j]=='1');
	} 
	for(int s=0;s<(1<<n);s++){
		int p[21],f=1,res=0;
		for(int i=0;i<n;i++)p[i+1]=(s>>i&1);
		for(int i=1;i<=m;i++){
			if(p[x[i]]^p[y[i]])res^=v[i];
			gmax(ans[i],res);
		}
	}
	for(int i=1;i<=m;i++){
		vector<int>v;
		do{
			v.pb(ans[i]&1),ans[i]>>=1;
		}while(ans[i]);
		for(int i=v.size()-1;~i;i--)printf("%d",v[i]);
		puts("");
	}
} 
int main(){
	FO(cut);
	n=gi;m=gi;
	if(n<=20){bf20();}
	return 0;
}

