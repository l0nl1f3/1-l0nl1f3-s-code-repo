#include<bits/stdc++.h>
#define N 601234 
using namespace std;
int n,a[N],b[N];
int at,bt,nc,sa[N],sb[N],va[N],vb[N],ia[N],ib[N],pa[N],pb[N];
void fa(int x){
	if(x<0||x>at)return;
	int y=ia[sa[x]],z=0;
	if(~y){
		int a=pb[y],b=pa[x],l,r;
		l=(!x?n+1:pa[x-1]);
		r=(!y?n+1:pb[y-1]);
		if(b<a&&r>=a)
			z=min(l,r)-a;
	}
	nc+=z-va[x];
	va[x]=z;
}
void fb(int x){
	if(x<0||x>bt)return;
	int y=ib[sb[x]],z=0;
	if(~y){
		int a=pa[y],b=pb[x],l,r;
		l=(!x?n+1:pb[x-1]);
		r=(!y?n+1:pa[y-1]);
		if(a<b&&l>=b)
			z=min(l,r)-b;
	}
	nc+=z-vb[x];
	vb[x]=z;
}
void insa(int v,int p){
	int x;
	while(bt>1&&a>=sb[tb]){
		
	} 
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",a+i);
	for(i=1;i<=n;i++)scanf("%d",b+i);
	for(i=n;i>=1;i--){
		
	}
}
