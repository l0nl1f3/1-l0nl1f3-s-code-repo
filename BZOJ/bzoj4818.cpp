//#include<bits/stdc++.h>
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 20000010
#define P 101
#define mod 20170408
#define ll long long
using namespace std;
bool np[N];int pr[N/10],pn;
int prework(){
	np[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i])pr[++pn]=i;
		for(int j=1;i*pr[j]<N&&j<=pn;j++){
			np[i*pr[j]]=1;
			if(i%pr[j]==0)break;
		}
	}
}
int n,m,p,c[2][P],zy[P][P];
int res[P][P],tp[P][P];
int solve(int t){
	int i,j,k,r;
	for(i=0;i<p;i++)
		for(j=0;j<p;j++)
			zy[i][j]=c[t][((i-j)%p+p)%p];
	memset(res,0,sizeof(res));
	for(i=0;i<p;i++)res[i][i]=1;
	for(r=n;r;r>>=1){
		if(r&1){
			memset(tp,0,sizeof(tp));
			for(i=0;i<p;i++)
				for(j=0;j<p;j++)
					for(k=0;k<p;k++)
						tp[i][j]=(tp[i][j]+(ll)res[i][k]*zy[k][j])%mod;
			for(i=0;i<p;i++)
				for(j=0;j<p;j++)res[i][j]=tp[i][j];
		}
		memset(tp,0,sizeof(tp));
		for(i=0;i<p;i++)
			for(j=0;j<p;j++)
				for(k=0;k<p;k++)
					tp[i][j]=(tp[i][j]+(ll)zy[i][k]*zy[k][j]%mod);
		for(i=0;i<p;i++)
			for(j=0;j<p;j++)
				zy[i][j]=tp[i][j];
	}
	/*for(i=0;i<p;i++,puts(""))
		for(j=0;j<p;j++)
			printf("%d ",res[i][j]);
	puts("");*/
	return res[0][0];
}
int main(){
	prework();
	int i,j,k;
	for(scanf("%d%d%d",&n,&m,&p),i=1;i<=m;i++){
		c[0][i%p]++;
		if(np[i])c[1][i%p]++;
	}
	printf("%d",(solve(0)-solve(1)+mod)%mod);
}
