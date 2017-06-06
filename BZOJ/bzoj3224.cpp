#include<bits/stdc++.h>
#define N 301234 
#define ap 4
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
    if(x<0) {pc('-'); x=-x;} //如果有负数就加上 
    char *s=ib::b;
    while(x) *(++s)=x%10, x/=10;
    while(s!=ib::b) pc((*(s--))+48);
    pc('\n');
}
struct node{
	int sz,v;
	node *lc,*rc;
	node(int s,int v,node *a,node *b)
	:sz(s),v(v),lc(a),rc(b){}
	node(){}
}*rot,*npt,*fat,*st[N],t[N];
int n,q,sn;
#define new_node(s,v,a,b) (&(*st[sn++]=node(s,v,a,b)))
#define merge(a,b) new_node(a->sz+b->sz,b->v,a,b)
inline void upd(node *x){
	x->lc->sz?
		x->sz=x->lc->sz+x->rc->sz,
		x->v =x->rc->v:0;
} 
inline void mt(node *x){
	x->lc->sz>x->rc->sz*ap?
		x->rc=merge(x->lc->rc,x->rc),
		st[--sn]=x->lc,
		x->lc=x->lc->lc:
	x->rc->sz>x->lc->sz*ap?
		x->lc=merge(x->lc,x->rc->lc),
		st[--sn]=x->rc,
		x->rc=x->rc->rc:0;
}
int find(node *p,int x){
	if(p->sz==1)
		return p->v;
	return x>p->lc->sz?find(p->rc,x-p->lc->sz):find(p->lc,x);
}
int rk(node *p,int x){
	if(p->sz==1)
		return 1;
	return x>p->lc->v?rk(p->rc,x)+p->lc->sz:rk(p->lc,x);
}
void ins(node *p,int x){
	if(p->sz==1){
		p->lc=new_node(1,min(p->v,x),npt,npt);
		p->rc=new_node(1,max(p->v,x),npt,npt);
	}else{
		x>p->lc->v?
			ins(p->rc,x):
			ins(p->lc,x);
	} 
	upd(p);
	mt(p);
}
void ers(node *p,int x){
	if(p->sz==1)
		*fat= p==fat->lc?*fat->rc:*fat->lc;
	else {
		fat=p;
		x>p->lc->v?
			ers(p->rc,x):
			ers(p->lc,x);
	}
	upd(p);
	mt(p);
}
int main(){
	int i,j,k;
	n=read();
	for(i=0;i<N;i++)st[i]=&t[i];
	npt=new node(0,0,0,0);
	rot=new node(1,0x7fffffff,npt,npt);
	while(n--){
		int op,x;
		op=read();x=read();
		if(op==1)ins(rot,x);
		if(op==2)ers(rot,x);
		if(op==3)pint(rk(rot,x));
		if(op==4)pint(find(rot,x));
		if(op==5)pint(find(rot,rk(rot,x)-1));
		if(op==6)pint(find(rot,rk(rot,x+1)));
	}
	return 0;
}
