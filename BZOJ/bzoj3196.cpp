#include<bits/stdc++.h>
using namespace std;
namespace FF
{ 
char ch,B[1<<20],*S=B,*T=B;
#define getc() (S==T&&(T=(S=B)+fread(B,1,1<<20,stdin),S==T)?0:*S++)
#define isd(c) (c>='0'&&c<='9')
int aa,bb;int r(){
    while(ch=getc(),!isd(ch)&&ch!='-');ch=='-'?aa=bb=0:(aa=ch-'0',bb=1);
    while(ch=getc(),isd(ch))aa=aa*10+ch-'0';return bb?aa:-aa;
}
}
#define read FF::r
#define BUFSIZE 5000000
namespace fob {char b[BUFSIZE]={},*f=b,*g=b+BUFSIZE-2;}
#define pob (fwrite(fob::b,sizeof(char),fob::f-fob::b,stdout),fob::f=fob::b,0)
#define pc(x) (*(fob::f++)=(x),(fob::f==fob::g)?pob:0)
struct foce {~foce() {pob; fflush(stdout);}} _foce;
namespace ib {char b[100];}
inline void pint(int x)
{
    if(x==0) {pc(48);return;}
    //if(x<0) {pc('-'); x=-x;} //如果有负数就加上 
    char *s=ib::b;
    while(x) *(++s)=x%10, x/=10;
    while(s!=ib::b) pc((*(s--))+48);
}
#define N 101234
#define M 8001234
int n,m,w[N],op[N][4],w1[N],w2[N],top,id,cnt;
int find(int x){
	int l=1;
	for(int o,r=id;l<r;w2[o=(l+r)/2]<x?l=o+1:r=o);
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
	return res;
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
			if(ts[0]!=2)w1[++top]=ts[3];
		}
	}
	sort(w1+1,w1+top+1);
	for(w1[0]=-1<<30,i=1;i<=top;i++)if(w1[i]!=w1[i-1])w2[++id]=w1[i];
	for(i=1;i<=n;i++)w[i]=find(w[i]);
	for(i=1;i<=m;i++)if(op[i][0]!=2)
		op[i][3]=find(op[i][3]);
	rot[0]=build(1,id);
	for(i=1;i<=n;i++)rot[i]=++cnt;
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j+=j&-j)
			edt(rot[j],rot[j],1,id,w[i],1);
	for(i=1;i<=m;i++){
		int *o=op[i];
		if (o[0]==1){ 
			bit_set(o[1]-1);  
			bit_set(o[2]);  
			pint(pt_query(o[1]-1,o[2],1,id,o[3])+1);
			pc('\n');
		}  
		if(o[0]==2){ 
			bit_set(o[1]-1);  
			bit_set(o[2]);  
			pint(w2[pt_kth(o[1]-1,o[2],1,id,o[3])]);  
			pc('\n');
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
			pint(w2[pt_kth(o[1]-1,o[2],1,id,x)]);  
			pc('\n');
		}  
		if(o[0]==5){ 
			bit_set(o[1]-1);  
			bit_set(o[2]);  
			int x = pt_query(o[1]-1,o[2],1,id,o[3]);  
			bit_set(o[1]-1);  
			bit_set(o[2]);  
			int num=pt_sum(o[1]-1,o[2],1,id,o[3]);  
			bit_set(o[1]-1);  
			bit_set(o[2]);  
			pint(w2[pt_kth(o[1]-1,o[2],1,id,x+num+1)]);  
			pc('\n');
		}  
	}
}
