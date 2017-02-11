#include<map>
#include<stack>
#include<queue>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<complex>
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;
#define inf 1001001001
#define infll 1001001001001001001LL
#define ll long long
#define dbg(vari) cerr<<#vari<<" = "<<(vari)<<endl
#define gmax(a,b) (a)=max((a),(b))
#define gmin(a,b) (a)=min((a),(b))
#define Ri register int
#define gc getchar()
#define il inline
il int read(){
	bool f=true;Ri x=0;char ch;while(!isdigit(ch=gc))if(ch=='-')f=false;while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=gc;}return f?x:-x;
}
#define gi read()
#define ig read()
#define FO(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout);
#define N 888888
struct cpx {
    double r,i;
    cpx(double real=0.0,double image=0.0) {
        r=real;i=image;
    }
    cpx operator +(const cpx w) {
        return cpx(r+w.r,i+w.i);
    }
    cpx operator -(const cpx w) {
        return cpx(r-w.r,i-w.i);
    }
    cpx operator *(const cpx w) {
        return cpx(r*w.r-i*w.i,r*w.i+i*w.r);
    }
};
cpx a[N],b[N];
cpx epsilon[N],arti_epsilon[N];
void init_epsilon(int n){
	double pi=acos(-1);
	for(int i=0;i!=n;i++){
		epsilon[i]=cpx(cos(2.0*pi*i/n),sin(2.0*pi*i/n)); 
		//arti_epsilon[i]=conj(epsilon[i]);
		arti_epsilon[i]=cpx(cos(2.0*pi*i/n),-sin(2.0*pi*i/n));
	}
}
void rev(int n,cpx*t){
	for(int i=0,j=0;i!=n;i++){
		if(i>j)swap(t[i],t[j]);
		for(int l=n/2;(j^=l)<l;l>>=1);
	}
}
void dft(int n,cpx*x,cpx*w){
	rev(n,x);
	for(int i=2;i<=n;i<<=1){
		int m=i/2;
		for(int j=0;j<n;j+=i){
			for(int k=0;k!=m;k++){
				cpx t=x[j+m+k]*w[n/i*k];
				x[j+m+k]=x[j+k]-t;
				x[j+k]=x[j+k]+t;
			}
		}
	}
}
cpx c[N]; 
char s1[N],s2[N]; int C[N];
int main(){
	int _n=gi;int n=1;
	--_n;
	while(n<=_n*2)n*=2;
	for(int i=0;i<=_n;i++)a[i]=gi,b[_n-i]=gi;
	init_epsilon(n);
	dft(n,a,epsilon);
	dft(n,b,epsilon);
	for(int i=0;i<=n;i++)c[i]=a[i]*b[i];
	dft(n,c,arti_epsilon);
	for(int i=_n;i<=_n+_n;i++)printf("%d\n",(int)(c[i].r/n+0.5));
	return 0;
}

