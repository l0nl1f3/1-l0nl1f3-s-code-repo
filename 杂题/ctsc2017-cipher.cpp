#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define N 40001234
int n,k,S,seed,p[N];
int Rand(){
	return seed=((seed*12321)^9999)&32767;
} 
void GenData(){
	scanf("%d%d%d",&k,&seed,&S);
	n=2*k+1;int t=0;
	for(int i=1;i<=n;i++){p[i]=Rand()>>7&1;t+=p[i];}
	int i=1;
	while(t>k){
		while(!p[i])i++;
		p[i]=0;--t; 
	}
	while(t<k){
		while( p[i])i++;
		p[i]=1;++t;
	}
} 
int g[N];
void task1(){
	int offset=1,i,j,k,s=0,t=0;
	for(i=1;i<=n;i++){
		if(p[i])++t,++g[t];else --t;
		if(p[i]&&t>0)++s;
	}
	for(i=1;i<=n;i++){
		if(!p[i]){
			--offset;
			s+=g[offset];
			if(s==0)j=i;
			if(s==S)k=i;
		}
		else{
			g[offset]--;
			offset++;s--;
			s-=g[offset-1];
			g[offset-2]++;
		}
	}
	printf("%d\n%d\n",j,k);
}
void task2(){
	return; 
}
void task3(){
	int offset=n+2,i,j,k,s=0,t=0;
	memset(g,0,sizeof(g));
	for(i=1;i<=n;i++){
		if(!p[i])++t,++g[n+1+t];else --t;
		if(!p[i]&&t>0)++s;
	}
	for(i=1;i<=n;i++){
		if(p[i]){
			--offset;
			s+=g[offset];
		}
		else{
			g[offset]--;
			offset++;
			s-=g[offset-1];
			g[offset]++;
			if(s==S+1)j=i;
		}
	}
	printf("%d\n",j);
}

int main(){
	GenData();
	task1();
	task2();
	task3();
}
