#include<bits/stdc++.h>
using namespace std;
#define N 201234
#define db double
int i,j,k,n,m,vic[N];
struct Mat{
	db a[2][2];
	db*operator[](int b){return a[b];}
	void init(db p,db q){
		a[0][0]=p;a[0][1]=1-p;
		a[1][0]=q;a[1][1]=1-q;
	}
	Mat operator*(Mat b){
		Mat t;
		for(i=0;i<2;i++)
			for(j=0;j<2;j++){
				t[i][j]=0;
				for(k=0;k<2;k++)
					t[i][j]+=a[i][k]*b[k][j];
			}
		return t;
	}
	Mat operator+(Mat b){
		Mat t;
		for(i=0;i<2;i++)
			for(j=0;j<2;j++)t[i][j]=a[i][j]+b[i][j];
		return t;
	}
};
double ans,p[N],q[N]; 
struct tag{Mat p,s;}T[888888];
tag merge(tag p,tag l,tag r){
	return p=(tag){l.p*r.p,l.p*r.s+l.s*r.p};
} 
void build(int p,int l,int r){
	if(l==r)
		T[p].p.init(T[p].s[0][0]=::p[l],T[p].s[1][0]=::q[l]);	
	else{
		build(p+p,l,(l+r)/2);
		build(p+p+1,(l+r)/2+1,r);
		merge(T[p],T[p+p],T[p+p+1]);
	}
}
tag qry(int p,int l,int r,int a,int b){
	if(a<=l&&r<=b)return T[p];
	int o=(l+r)/2;tag ans;
	if(a<=o&&b>o)return merge(ans,qry(p+p,l,o,a,b),qry(p+p+1,o+1,r,a,b));
	return b<=o?qry(p+p,l,o,a,b):qry(p+p+1,o+1,r,a,b);
}
map<int,int>r;
void mdf(int l,int r,int o){
	int L=vic[l],R=vic[r];
	tag res=qry(1,0,n,l+1,r);
	ans+=o*res.s[L][R]/res.p[L][R];
}
int main(){
	scanf("%d%d%*s%lf",&n,&m,p+1);
	for(i=2;i<=n;i++)scanf("%lf%lf",p+i,q+i);
	r[0]=r[++n]=0; p[0]=q[0]=p[n]=q[n]=1;
	build(1,0,n);mdf(0,n,1);
	while(m--){
		char op[30];
		scanf("%s%d",op,&i);
		if(op[0]=='a'){
			scanf("%d",vic+i);
			r[i]=vic[i]=!vic[i];
			map<int,int>::iterator l,r;
			l=r=::r.lower_bound(i);--l;++r;
			mdf(l->first,r->first,-1);
			mdf(l->first,i,1);
			mdf(i,r->first,1);
		}else{
			map<int,int>::iterator l,r;
			l=r=::r.lower_bound(i);--l;++r;
			mdf(l->first,i,-1);
			mdf(i,r->first,-1);
			mdf(l->first,r->first,1);
			::r.erase(i); 
		} 
		printf("%lf\n",ans-1);
	}
}
