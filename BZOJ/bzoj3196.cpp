#include<bits/stdc++.h>
using namespace std;
int read(){
	int x=0,f=1;char ch;
	for(ch=getchar();!isdigit(ch);ch=getchar())
		if(ch=='-')f=-1;
	for(;isdigit(ch);x=x*10+ch-'0',ch=getchar());
	return x*f;
}
#define N 101234
#define M 8001234
int n,m,w[N],op[N][4],w1[N],w2[N],top,id,cnt;
int find(int x){
	int l=1;
	for(int o,r=id;l<=r;w2[o=(l+r)/2]<x?l=o+1:r=o-1);
	return l;
}
int ls[M],rs[M],s[M],rot[N],bit[N];
void edt(int x,int &y,int l,int r,int p,int d){
	if(!y)y=++cnt;
	ls[y]=ls[x];rs[y]=rs[x];s[y]=s[x]+d;
	if(l==r)return;
	if(p<=(l+r)/2)edt(ls[x],ls[y],l,(l+r)/2,p,d);
	else edt(rs[x],rs[y],(l+r)/2+1,r,p,d);	 
}
int build(int l,int r){
	int y=++cnt;
	if(l==r)return y;
	ls[y]=build(l,(l+r)/2);
	rs[y]=build((l+r)/2+1,r);
	return y;
}
int bit_count(int x,int o=0){
	int res=0;
	for(int r=x;r;r-=r&-r){
		if(o)res+=s[bit[r]];
		else res+=s[ls[bit[r]]];
	}
}
int bit_set(int x){
	for(int r=x;r;r-=r&-r)bit[r]=rot[r];	
}
int bit_son(int x,int o=0){
	for(int r=x;r;r-=r&-r)bit[r]= o?rs[bit[r]]:ls[bit[r]];
}
int pt_query(int x,int y,int l,int r,int p){
	if(l==r)return l<p?bit_count(y,1)-bit_count(x,1):0;
	int o=(l+r)/2;
	if(p<=o){
		bit_son(x);
		bit_son(y);
		return pt_query(x,y,l,o,p);
	}else{
		int res=bit_count(y)-bit_count(x); 
		bit_son(x,1);
		bit_son(y,1);
		return res+pt_query(x,y,o+1,r,p);
	}
}
int pt_kth(int x,int y,int l,int r,int p){
	if(l==r)return l;
	int o=(l+r)/2,L=bit_count(y)-bit_count(x);
	if(p<=L){
		bit_son(x);
		bit_son(y);
		return pt_kth(x,y,l,o,p);
	}else{
		bit_son(x,1);
		bit_son(y,1);
		return pt_kth(x,y,o+1,r,p-L);
	}
}
int pt_sum(int x,int y,int l,int r,int p){
	if(l==r)return bit_count(y,1)-bit_count(x,1);
	int o=(l+r)/2;
	if(p<=o){
		bit_son(x);
		bit_son(y);
		return pt_sum(x,y,l,o,p);
	}else{
		int res=bit_count(y)-bit_count(x); 
		bit_son(x,1);
		bit_son(y,1);
		return pt_sum(x,y,o+1,r,p);
	}
}
int main(){
	n=read();m=read();
	int i,j;
	for(i=1;i<=n;i++)w1[++top]=w[i]=read();
	for(i=1;i<=m;i++){
		int *ts=op[i];
		ts[0]=read();
		if(ts[0]==3){
			ts[1]=read();ts[3]=read();
			w1[++top]=ts[3]; 
		}else{
			ts[1]=read();ts[2]=read();ts[3]=read();
			w1[++top]=ts[3];
		}
	}
	sort(w1+1,w1+top+1);
	for(i=1;i<=top;i++)if(w1[i]!=w1[i-1])w2[++id]=w1[i];
	for(i=1;i<=n;i++)w[i]=find(w[i]);
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j+=j&-j)
			edt(rot[j],rot[j],1,id,w[i],1);
	for(i=1;i<=m;i++){
		int *o=op[i];
		if (o[0]==1){ 
			bit_set(o[1]);  
			bit_set(o[2]);  
			printf("%d\n",pt_query(o[1]-1,o[2],1,id,o[3]) + 1);  
		}  
		if(o[0]==2){ 
			bit_set(o[1]-1);  
			bit_set(o[2]);  
			printf("%d\n", w2[pt_kth(o[1]-1,o[2],1,id,o[3])]);  
		}  
		if(o[0]==3){
			for(j=o[1];j<=n;j+=j&-j)
				edt(rot[j],rot[j],1,id,w[o[1]],-1);  
			w[o[1]]=o[3];  
			for(j=o[1];j<=n;j+=j&-j)  
				edt(rot[j],rot[j],1,id,w[o[1]],1);  
		}  
		if(o[0]==4){
			bit_set(o[1]-1);  
			bit_set(o[2]);  
			int x=pt_query(o[1]-1,o[2],1,id,o[3]);  
			bit_set(o[1]-1);  
			bit_set(o[2]);  
			printf("%d\n",w2[pt_kth(o[1]-1,o[2],1,id,x)]);  
		}  
		if(o[0]==5){ 
			bit_set(o[1]-1);  
			bit_set(o[2]);  
			int x = pt_query(o[1]-1,o[2],1,id,o[3]);  
			bit_set(o[1]-1);  
			bit_set(o[2]);  
			int num=pt_sum(o[2],1,id,o[3],o[1]-1);  
			bit_set(o[1]-1);  
			bit_set(o[2]);  
			printf("%d\n", w2[pt_kth(1,id,x+num+1,o[1]-1,o[2])]);  
		}  
	}
}
