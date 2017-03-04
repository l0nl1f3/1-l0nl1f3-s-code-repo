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
int n,m,k;
int main(){
	freopen("room.in","w",stdout);
	n=300;m=300;k=2333;
	printf("%d %d %d\n",n,m,k);
	for(int i=1;i<=m;i++,puts("")) 
	for(int j=1;j<=m;j++)printf("%d ",((i*12+j^26)+233)^1+1231);
	
	return 0;
}

