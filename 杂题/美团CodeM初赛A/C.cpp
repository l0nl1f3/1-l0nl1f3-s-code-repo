#include<bits/stdc++.h>
#define FO(x) {freopen(#x".in","r",stdin);\
				freopen(#x".out","w",stdout);}
using namespace std;
typedef long long ll;
template<typename T>inline bool cmin(T &a,const T &b){	return a>b?a=b,1:0;}
template<typename T>inline bool cmax(T &a,const T &b){	return a<b?a=b,1:0;}
#define N 101234
int n,T,C,t[N],c[N];
vector<int>L,R,x; 
bool chk(double o){
	double nd=0;
	for(int j=0;j<x.size();j++)	{
		int i=x[j];
		nd+=(c[i]*o-(double)c[i]*t[i])/(T-o);
	}
	return nd<=C;
}
int main(){
	int i,j,k;double lb=1e233,rb=-1e233,o;
	scanf("%d%d%d",&n,&T,&C);
	for(i=1;i<=n;i++)scanf("%d%d",t+i,c+i);
	for(i=1,k=0;i<=n;i++){
		cmin(lb,(double)t[i]);cmax(rb,(double)t[i]);
		if(t[i]<T)L.push_back(i);
		if(t[i]>T)R.push_back(i);
		if(t[i]==T)k=1;
	}
	if(L.size()&&R.size())return puts("Impossible"),0;
	if(L.size()>R.size())x=L;else x=R;
	if(k){
		if(!x.size())return printf("Possible\n%.4lf",double(T)),0;
		else return puts("Impossible"),0;
	}
	if(R.size()){
		if(chk(lb))return printf("Possible\n%.4lf",lb),0;
		else return puts("Impossible"),0; 
	}
	if(!chk(rb))return puts("Impossible"),0;
	for(lb=rb,rb=T,i=0;i<=100;i++)
		if(chk(o=(lb+rb)/2))lb=o;else rb=o;
	printf("Possible\n%.4lf\n",o);
	return 0;
}



