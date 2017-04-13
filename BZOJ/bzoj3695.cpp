#include<bits/stdc++.h>
using namespace std;
int n,x,i,v[100],h[100];
double f(double sin){
	double d=0;
	for(i=0;i<n;i++){
		double tan=sin/sqrt(1-sin*sin);
		d+=tan*h[i];
		if(i<n-1)sin=sin/v[i]*v[i+1];
		if(sin>1.0)return x+1.0;
	}
	return d;
}
double g(double sin){
	double t=0;
	for(i=0;i<n;i++){
		double cos=sqrt(1-sin*sin);
		t+=h[i]/(cos*v[i]);
		if(i<n-1)sin=sin/v[i]*v[i+1]; 
	}
	return t;
}
int main(){
	scanf("%d%d",&n,&x);
	for(i=0;i<n;i++)scanf("%d",h+i);
	for(i=0;i<n;i++)scanf("%d",v+i);
	double l=0,r=1;
	for(int j=0;j<100;j++){
		double o=(l+r)/2,d=f(o);
		if(d>x)r=o;else l=o;
	}
	printf("%.3lf",g(l));
}

