#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
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
#define mod 1000000007
#define cut(x) ((x)>=mod?(x)-mod:(x))
struct Num{
	int a,b;
	Num(){}Num(int a,int b):a(a),b(b){}
	Num operator *(Num y){return Num((a*(ll)y.a+5ll*b*y.b)%mod,((ll)a*y.b+(ll)b*y.a)%mod);}
	Num operator +(Num y){return Num((a+y.a)%mod,(b+y.b)%mod);}
};
struct Mat{
	Num a[2][2];
	Num *operator[](int x){return a[x];}
	Mat operator*(Mat y){
		Mat I={};
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++){
				I[i][j]=Num(0,0);
				for(int k=0;k<2;k++)
					I[i][j]=I[i][j]+a[i][k]*y[k][j];
			}
		return I;		
	}
}p,x,y,z;
Mat operator^(Mat a,int n){
	Mat I=a,res=p;
	for(;n;n>>=1,I=I*I)if(n&1)res=res*I;
	return res;
} 
int T,n,k;
int main(){
	FO(fib);
	p[0][0].a=p[1][1].a=1;
	y[0][0].a=y[0][1].a=1;
	z[0][0].a=z[0][0].b=1;
	for(T=gi;T--;){
		n=gi;k=gi;
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)x[i][j]=Num(0,0);
       	x[0][0].a=x[0][0].b=(mod+1>>1);
       	x[1][0].a=x[1][1].a=1;
		x=((y*(x^(n-1)))^k)*z;
		printf("%d\n",x[0][0].b);
	}
}
