#include<bits/stdc++.h>
#define N 101234
#define M 67108864
using namespace std;
int n,x,ans,a[N],g=M;
char pc[M+1];bool b[M+10];
int main(){
	int i,j,k;
	scanf("%d",&n);
	pc[M]=127;pc[0]=0;
	for(i=1;i<M;i++)pc[i]=pc[i>>1]+(i&1);
	for(i=1;i<=n;i++)scanf("%d",a+i);
	for(i=1;i<=n;i++){
		if(a[i]&M)
			ans|=M,a[i]^=M;
		for(int bs=511^a[i];bs;bs=(bs-1)&511)
			b[bs|a[i]]=1;
		b[a[i]]=1; 
	}
	for(i=512;i<M;i<<=1)
		for(j=0;j<M;j+=4){
			(j&i)?0:b[j|i]|=b[j];
			((j+1)&i)?0:b[(j+1)|i]|=b[(j+1)];
			((j+2)&i)?0:b[(j+2)|i]|=b[(j+2)];
			(((j+3))&i)?0:b[(j+3)|i]|=b[(j+3)];
		}
	for(i=0;i<M;i++){
		((!b[i^(M-1)])&&(pc[i]<pc[g]||(pc[i]==pc[g]&&i<g)))?g=i:0;
	}
	cout<<(g|ans); 
			
	return 0;
}
