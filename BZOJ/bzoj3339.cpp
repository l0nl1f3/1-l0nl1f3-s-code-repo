#include<bits/stdc++.h>
#define M 6000000
using namespace std;
int n,q,cnt,a[M],ls[M],rs[M],s[M],rot[M];
void edt(int &x,int y,int l,int r,int p,int b){
	s[x=++cnt]=s[y];
	ls[x]=ls[y];rs[x]=rs[y];
	if(l==r)s[x]=b;
	else{
		if(p<=(l+r)/2)edt(ls[x],ls[y],l,(l+r)/2,p,b);
		else edt(rs[x],rs[y],(l+r)/2+1,r,p,b);
		s[x]=min(s[ls[x]],s[rs[x]]);	
	}
}
int query(int x,int l,int r,int p){
	if(l==r)return l;
	return s[ls[x]]>=p?query(rs[x],(l+r)/2+1,r,p):
						query(ls[x],l,(l+r)/2,p);
}
int main(){
	int i,j;
	for(scanf("%d%d",&n,&q),i=1;i<=n;i++)scanf("%d",a+i);
	for(i=1;i<=n;i++)edt(rot[i],rot[i-1],0,1e8,a[i],i);
	while(q--){
		scanf("%d%d",&i,&j);
		printf("%d\n",query(rot[j],0,1e8,i));
	}
}
