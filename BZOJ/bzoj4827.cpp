#include<bits/stdc++.h>
#define N 833333
#define ll long long 
using namespace std;
namespace FFT{
	struct cpx {
	    double r,i;
	    cpx(double real=0.0,double image=0.0) {r=real;i=image;}
	    cpx operator +(const cpx w) {return cpx(r+w.r,i+w.i);}
	    cpx operator -(const cpx w) {return cpx(r-w.r,i-w.i);}
	    cpx operator *(const cpx w) {return cpx(r*w.r-i*w.i,r*w.i+i*w.r);}
	};
	cpx eps[2][N];
	void init_eps(int n){
		double pi=acos(-1);
		for(int i=0;i!=n;i++){
			eps[0][i]=cpx(cos(2.0*pi*i/n),sin(2.0*pi*i/n)); 
			//arti_epsilon[i]=conj(epsilon[i]);
			eps[1][i]=cpx(cos(2.0*pi*i/n),-sin(2.0*pi*i/n));
		}
	}
	void rev(int n,cpx*t){
		for(int i=0,j=0;i!=n;i++){
			if(i>j)swap(t[i],t[j]);
			for(int l=n/2;(j^=l)<l;l>>=1);
		}
	}
	void dft(int n,cpx*x,int op){
		rev(n,x);
		for(int i=2;i<=n;i<<=1){
			int m=i/2;
			for(int j=0;j<n;j+=i){
				for(int k=0;k!=m;k++){
					cpx t=x[j+m+k]*eps[op][n/i*k];
					x[j+m+k]=x[j+k]-t;
					x[j+k]=x[j+k]+t;
				}
			}
		}
		if(op==1)for(int i=0;i<n;i++)x[i].r/=n;
	} 
}
using FFT::dft;
int d,n,m,x[N],y[N],ans[N];
FFT::cpx a[N],b[N];
ll sx,sy,x2,y2;
int main(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=0;i<n;i++){
		scanf("%d",x+i);
		sx+=x[i];
	}
	for(i=0;i<n;i++){
		scanf("%d",y+i);
		y2+=y[i]*y[i];sy+=y[i];
	}
	double d1=(double)(sy-sx)/n;
	if(ceil(d1)-d1>d1-floor(d1))
		d=floor(d1);
	else d=ceil(d1);
	for(i=0;i<n;i++)x[i]+=d;
	for(i=0;i<n;i++){
		x2+=x[i]*x[i];
		a[i].r=x[i];
	}
	for(i=0;i<n+n;i++)b[n+n-i]=y[i%n];
	for(j=1;j<=(n+n+1);j<<=1);
	FFT::init_eps(j); 
	dft(j,a,0);dft(j,b,0);
	for(i=0;i<j;i++)a[i]=a[i]*b[i];
	dft(j,a,1);
	ll as=(1ll<<50);
	for(i=0;i<j;i++)ans[i]=int(a[i].r+0.5);
//	for(i=0;i<j;i++)cout<<i<<"="<<ans[i]<<endl;
	//printf("sx=%lld,sy=%lld,x2=%lld,y2=%lld\n",sx,sy,x2,y2);
	for(i=n-1;i<n+n;i++){
		//printf("%lld,%lld,%d\n",x2,y2,ans[i]);
		as=min(as,(ll)(x2+y2-2*ans[i]));
	}
	cout<<as;
	return 0;
} 
