#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 888888
struct cpx {
    double r,i;
    cpx(double real=0.0,double image=0.0) {r=real;i=image;}
    cpx operator *(const int w) {return cpx(r*w,i*w);}
	cpx operator +(const cpx w) {return cpx(r+w.r,i+w.i);}
    cpx operator -(const cpx w) {return cpx(r-w.r,i-w.i);}
    cpx operator *(const cpx w) {return cpx(r*w.r-i*w.i,r*w.i+i*w.r);}
};
cpx w[N],iw[N];
void init_epsilon(int n){
	double pi=acos(-1);
	for(int i=0;i!=n;i++){
		w[i]=cpx(cos(2.0*pi*i/n),sin(2.0*pi*i/n)); 
		//arti_epsilon[i]=conj(epsilon[i]);
		iw[i]=cpx(cos(2.0*pi*i/n),-sin(2.0*pi*i/n));
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
int n,m,r,s[N],t[N];char a[N],b[N];
cpx c[N],a1[N],b1[N],a2[N],b2[N],a3[N],b3[N],ans[N];
void fft(cpx *a,cpx *b,int cn){
	dft(r,a,w);dft(r,b,w);
	for(int i=0;i<r;i++)c[i]=a[i]*b[i];
	dft(r,c,iw);
	for(int i=0;i<r;i++)c[i].r/=r,c[i].i/=r;
	for(int i=0;i<r;i++)ans[i]=ans[i]+c[i]*cn;
} 
int main(){
	scanf("%s%s",a,b);n=strlen(a);m=strlen(b);
	for(int i=1;i<=m/2;i++)swap(b[i-1],b[m-i]);
	for(int i=0;i<n;i++){
		s[i]=a[i];t[i]=(b[i]!='?'?b[i]:0);
		a1[i]=s[i]*s[i]*s[i];b1[i]=t[i];
		a2[i]=s[i]*s[i];b2[i]=t[i]*t[i];
		a3[i]=s[i];b3[i]=t[i]*t[i]*t[i];
	}
	for(r=1;r<=n+n;r+=r);
	init_epsilon(r);
	fft(a1,b1,1);
	fft(a2,b2,-2);
	fft(a3,b3,1);
	//假装做完了 
}
