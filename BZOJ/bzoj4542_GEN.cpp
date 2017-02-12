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
ll q=1000000007;
int main(){
	freopen("qaq.in","w",stdout);
	srand('S');
	cout<<q<<endl;
	int n=100000;
	for(int i=1;i<=n;i++){
		putchar(rand()%10+'0');
	}puts("");
	int m=100000;cout<<m<<endl;
	for(int i=1;i<=m;i++){
		int l=rand(),r=rand();if(l>r)swap(l,r);
		cout<<l<<" "<<r<<endl;
	}
	return 0;
}

