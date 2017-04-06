#include<bits/stdc++.h>
#define N 310
#define ll long long
using namespace std;
ll f[2][2][2][2][N][N],k;
void swap(int &a,int &b){
	int t=a;a=b;b=t;
}
int min(int a,int b){
	return a<b?a:b;
}
ll dfs(int w,int h,int a,int b,int c,int d){
	if(w>h){
		swap(w,h);
		int _l=c,_r=d,_u=b,_d=a;
		a=_l;b=_r;c=_u;d=_d;
		if(a>b)swap(a,b);if(c>d)swap(c,d);
	}
	if(~f[a][b][c][d][w][h])return f[a][b][c][d][w][h];
	if(!(a+b+c+d))return f[a][b][c][d][w][h]=1e9;
	ll res=(ll)(w*h-k)*(w*h-k);
	if((a+b+c)||(a+b+d))
		for(int i=1;i<w;i++)res=min(res,dfs(i,h,a,b,c,0)+dfs(w-i,h,a,b,0,d));
	if((a+c+d)||(b+c+d))
		for(int i=1;i<h;i++)res=min(res,dfs(w,i,a,0,c,d)+dfs(w,h-i,0,b,c,d));
	return f[a][b][c][d][w][h]=res;
}
int main(){
	int w,h;
	cin>>w>>h>>k;memset(f,-1,sizeof(f));
	cout<<dfs(w,h,1,1,1,1);
} 
