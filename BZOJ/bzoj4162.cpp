#include<bits/stdc++.h>
#define p 1000000007
#define ll long long
#define QAQ 500 
#define N 60
using namespace std;
int n,f[N],a[N][N],b[N][N],A[N],B[N],res[QAQ],X[QAQ];string s;
int fpow(int a,int n){
	int res=1;
	for(;n;n>>=1,a=(ll)a*a%p)
		if(n&1)res=(ll)res*a%p;
	return res; 
}
int det(){
	int i,j,k,l,o;
	for(l=j=1;j<=n;j++){
		for(k=j;k<=n;k++)
			if(b[j][k])break;
		if(k==n+1){l=0;break;}
		if(k>j)for(l*=-1,o=j;o<=n;o++)swap(b[j][o],b[k][o]);
		l=(ll)l*b[j][j]%p;o=fpow(b[j][j],p-2);
		for(k=j;k<=n;k++)b[j][k]=(ll)b[j][k]*o%p;	
		for(k=j+1;k<=n;k++)if(b[k][j])
		for(o=n;o>=j;o--)b[k][o]=(b[k][o]-(ll)b[k][j]*b[j][o])%p;
	}
	return l<0?l+p:l; 
}
int C[QAQ];
void mul(int *a,int *b){
	int i,j;
	memset(C,0,sizeof(C));
	for(i=0;i<=n;i++)
		for(j=0;j<=n;j++)
			C[i+j]=(C[i+j]+(ll)a[i]*b[j])%p;
	for(i=n;~i;i--){
		ll t=(ll)C[i+n]*fpow(B[n],p-2)%p;t=p-t;
		for(j=0;j<=n;j++)
			C[i+j]=(C[i+j]+B[j]*t)%p;
	}	
	for(i=0;i<=n;i++)a[i]=C[i];
}
int M[N][N],v[N][N],t[N][N];
int main(){
	int i,j,k,l;
	cin>>s>>n;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	for(i=0;i<=n;i++){
		for(j=1;j<=n;j++)
			for(k=1;k<=n;k++)
				b[j][k]=a[j][k]-(k==j)*i;
		f[i]=det();
	}
	for(i=1;i<=n;i++)
		for(j=n;j>=i;j--)
			f[j]=(f[j]-f[j-1]+p)%p;
	for(B[0]=f[0],i=k=A[0]=1;i<=n;k=(ll)k*++i%p){
		for(j=i;j;j--)A[j]=(A[j-1]-(ll)A[j]*(i-1)%p+p)%p;
		for(f[i]=(ll)f[i]*fpow(k,p-2)%p,A[0]=j++;j<=i;j++){
			B[j]=(B[j]+(ll)A[j]*f[i]%p)%p;
		} 
	}
	for(X[res[0]=1]=1,i=s.size()-1;~i;i--){
		if(s[i]=='1')mul(res,X);
		mul(X,X);
	}
	for(i=1;i<=n;i++)v[i][i]=1;
	for(l=0;l<=n;l++){
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)M[i][j]=(M[i][j]+(ll)v[i][j]*res[l])%p;
		memset(t,0,sizeof(t));
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				for(k=1;k<=n;k++)
					t[i][j]=(t[i][j]+(ll)a[i][k]*v[k][j])%p;
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				v[i][j]=t[i][j];
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)printf("%d%c",M[i][j]," \n"[j==n]);
	return 0;	
} 
