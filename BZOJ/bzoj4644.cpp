#include<bitset> 
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std; 
#define M 1234 
char s[M];int mx,n,m,q;
bitset<M>a,b[M],ans,e,f;
bitset<M>bs[M],bl[M],b0[M];
void ins(int p){
	int d=-1;b[p]^=a;
	for(int i=1;i<=q;i++)if(b0[i][p])d=i,i=q+1;
	if(d>=1){
		e=a;f=b0[d];
		for(int i=d+1;i<=q;i++)if(b0[i][p])b0[i]^=f;
		for(int i=0;i<=mx;i++)if(bl[i][p])bl[i]^=f;
		b0[d].reset();
	}else{
		for(int i=0;i<=mx;i++)if(bl[i][p])d=i,i=mx+1;
		if(d>=0){
			for(int i=d+1;i<=mx;i++)if(bl[i][p])bs[i]^=bs[d],bl[i]^=bl[d];
			e=bs[d]^a;f=bl[d];
			bs[d].reset();bl[d].reset();
		}else e=b[p],f.reset(),f.set(p);
	}
	for(int i=mx;~i;i--){
		if(!e[i])continue;
		if(!bs[i][i])bs[i]=e,bl[i]=f,i=0;
		else e^=bs[i],f^=bl[i];
	}
	if(!e.any())b0[++q]=f;
}
void gv(){
	scanf("%s",s);
	int n=strlen(s);if(n-1>mx)mx=n-1;
	a.reset();
	for(int i=n-1;~i;i--)a[n-i-1]=s[i]-'0';
} 
int read(){
	int x=0;char ch;
	for(ch=getchar();!isdigit(ch);ch=getchar());
	for(;isdigit(ch);x=x*10+ch-'0',ch=getchar());
	return x;
}
#define gi read()
int main(){
	n=gi;n=gi;m=gi;
	for(int x,y,i=1;i<=m;i++){
		x=gi-1;y=gi-1;gv();
		ins(x);ins(y);
		for(int i=mx;~i;i--)if(bs[i].any()&&!ans[i])ans^=bs[i];
		bool f=0;
		for(int i=mx;~i;i--){
			if(!ans[i])continue;
			for(int j=i;~j;j--)putchar(ans[j]?'1':'0');
			f=1;break;
		}		
		puts(f?"":"0");ans.reset();
	}
	return 0;
}

