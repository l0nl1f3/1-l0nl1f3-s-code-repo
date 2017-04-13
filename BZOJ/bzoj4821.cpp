#include<queue>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define S M+M
#define fi first
#define sx fi.fi
#define sy fi.se
#define sq se.fi
#define ml se.se
#define M 262144
#define eps 1e-9
#define se second
#define G inline
#define inf 1000000000
typedef pair<pair<double,double>,pair<double,double> > P;
int n,m,x[S],y[S];
double xs[S],ys[S],xd[S],yd[S],cx[S],cy[S],t[S],xy[S],is[S],si[S];
G int read(){
	int x=0,f=1;char ch;
	for(ch=getchar();!isdigit(ch);ch=getchar())
		if(ch=='-')f=-1;
	for(;isdigit(ch);x=x*10+ch-'0',ch=getchar());
	return x*f;
}
G void merge(int p){
	xs[p]=xs[p+p]+xs[p+p+1];
	ys[p]=ys[p+p]+ys[p+p+1];
	xy[p]=xy[p+p]+xy[p+p+1];
	t [p]=t [p+p]+t [p+p+1];
}
G void Sig_Cover(int p,int l,int r,double x,double y){
	xd[p]=yd[p]=0;cx[p]=x;cy[p]=y;
	t [p]=x*x*(r-l+1)+(x+x)*is[p]+si[p];
	xy[p]=x*y*(r-l+1)+(x+y)*is[p]+si[p];
	xs[p]=x*  (r-l+1)+is[p];
	ys[p]=y*  (r-l+1)+is[p];
}
G void Sig_Modify(int p,int l,int r,double x,double y){
	if(cx[p]!=inf||cy[p]!=inf)
		Sig_Cover(p,l,r,cx[p]+x,cy[p]+y);
	else{
		xd[p]+=x;yd[p]+=y;
	    t[p] +=x*x*(r-l+1)+2*x*xs[p];
	    xy[p]+=x*ys[p]+y*xs[p]+x*y*(r-l+1);
	    xs[p]+=x*(r-l+1);
		ys[p]+=y*(r-l+1);
	}
}
G void push_down(int p,int l,int r){
	if(xd[p]||yd[p]){
		Sig_Modify(p+p,l,(l+r)/2,    xd[p],yd[p]);
		Sig_Modify(p+p+1,(l+r)/2+1,r,xd[p],yd[p]);
		xd[p]=yd[p]=0;
	}
	if(cx[p]!=inf||cy[p]!=inf){
		Sig_Cover(p+p,l,(l+r)/2,    cx[p],cy[p]);
		Sig_Cover(p+p+1,(l+r)/2+1,r,cx[p],cy[p]);
		cx[p]=cy[p]=inf;
	}
}
void Seg_Build(int p,int l,int r){
	cx[p]=cy[p]=inf;
	if(l==r){
		xs[p]=x[r];ys[p]=y[r];
		t [p]=xs[p]*xs[p];
		xy[p]=xs[p]*ys[p];
		is[p]=r;si[p]=(long long)r*r;
	}else{
		Seg_Build(p+p,l,(l+r)/2);
		Seg_Build(p+p+1,(l+r)/2+1,r);
		merge(p);
		is[p]=is[p+p]+is[p+p+1];
		si[p]=si[p+p]+si[p+p+1];
	}
}
void Modify1(int p,int l,int r,int a,int b,double x,double y){
	if(a<=l&&r<=b)
		Sig_Modify(p,l,r,x,y);
	else{
		push_down(p,l,r);
		if(a<=(l+r)/2)
			Modify1(p+p,l,(l+r)/2,a,b,x,y);
		if(b>(l+r)/2)
			Modify1(p+p+1,(l+r)/2+1,r,a,b,x,y);
		merge(p);
	}
}
void Modify2(int p,int l,int r,int a,int b,double x,double y){
	if(a<=l&&r<=b)
		Sig_Cover(p,l,r,x,y);
	else{
		push_down(p,l,r);
		if(a<=(l+r)/2)
			Modify2(p+p,l,(l+r)/2,a,b,x,y);
		if(b>(l+r)/2)
			Modify2(p+p+1,(l+r)/2+1,r,a,b,x,y);
		merge(p);
	}
}
void query(int p,int l,int r,int a,int b,P &g){
	if(a<=l&&r<=b){
		g.sx+=xs[p];g.sy+=ys[p];
		g.sq+=t[p];g.ml+=xy[p];
	}else{
		push_down(p,l,r);
		if(a<=(l+r)/2)
			query(p+p,l,(l+r)/2,a,b,g);
		if(b>(l+r)/2)
			query(p+p+1,(l+r)/2+1,r,a,b,g);
	}
}
double analyse(int l,int r){
    P t;
	t=make_pair(make_pair(0,0),make_pair(0,0));
    double ax,ay,u,d;
    u=d=0;query(1,1,n,l,r,t);
    ax=t.sx/(r-l+1);ay=t.sy/(r-l+1);
    d=t.sq-2*ax*t.sx+ax*ax*(r-l+1);
    u=t.ml-ay*t.sx-ax*t.sy+ax*ay*(r-l+1);
    return u/d;
}
int main(){
	freopen("relative.in","r",stdin);
	freopen("relative.out","w",stdout);
	int i;
	for(n=read(),m=read(),i=1;i<=n;i++)x[i]=read();
	for(i=1;i<=n;i++)y[i]=read();
	Seg_Build(1,1,n);
	while(m--){
		int op,l,r,s,t;
		op=read();l=read();r=read();
		if(op==1)
			printf("%.10lf\n",analyse(l,r));
		if(op==2){
			s=read();t=read();
			Modify1(1,1,n,l,r,s,t);
		}
		if(op==3){
			s=read();t=read();
			Modify2(1,1,n,l,r,s,t);
		}
	}
	//cerr<<clock()<<"ms";
}
