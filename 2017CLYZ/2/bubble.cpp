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
#define M 30001234
#define N 1001234
#define debug 0 
int a[M],n;
il int max(int a,int b){return a>b?a:b;} 
void read32(){for(int i=1;a[i]=gi,i<n;i++);}
void pr32(int *a){for(int i=1;printf("%d ",a[i]),i<n;i++);puts("");}
bool ordchk(int *a,bool f=0){for(int i=1;i<n;i++)f|=(a[i]>a[i+1]);return !f;}
void gen32(int S,int B,int C,int D){	
	for(int i=1;i<=n;i++){
		S=((S*(ll)B)+C)%D;
		swap(a[i]=i,a[S%i+1]);
	}
}
void bf30(int *a){
	int counter=0;
	while(!ordchk(a)){
		for(int i=1;i<n;i++)if(a[i]>a[i+1])swap(a[i],a[i+1]);
		counter++;
	}
	printf("%d\n",counter);
}
int greedy(){
	int ans=0;
	for(int i=1;i<=n;i++)gmax(ans,i-a[i]); 
	printf("%d\n",ans);
}
int main(){
	FO(bubble);
	n=gi;
	int s,b,c,d;s=gi;b=gi;c=gi;d=gi;gen32(s,b,c,d);
	//read32();
	//cerr<<clock();
	if(n<=1000){bf30(a);return 0;}
	if(n<=30000000){greedy();return 0;} 
	return 0;
}

