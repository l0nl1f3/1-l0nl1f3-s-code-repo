作者：吉如一
链接：https://www.zhihu.com/question/59037149/answer/161810265
来源：知乎
著作权归作者所有，转载请联系作者获得授权。

#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<ctime>
using namespace std;
int getrand(){
	return (rand()<<8)+rand();
}
struct atom{
	int pd,l,r,w;
	void print(){
	//	pd=2;
		if (pd==1) printf("%d %d %d %d\n",pd,l,r,w);
		else printf("%d %d %d\n",pd,l,r);
	}
};
vector<atom>q;
int n=20000,m=10000,x[210000],pre;
void easyrand(){
	while (q.size()<m){
		int k1=getrand()%2+1,l=getrand()%n+1,r=getrand()%n+1,w=getrand()%20-10;
		if (l>r) swap(l,r);
		q.push_back((atom){k1,l,r,w});
	}
}
int y[1100000];
void killhash(int n,int m){
	n=n-pre; if (n==0) return;
	int len=1; y[1]=0;
	while (len<=n/2){
		for (int i=1;i<=len;i++) y[len+i]=y[i]^1;
		len=len*2;
	}
	for (int i=1;i<=n/2;i++) y[i+n/2]=y[i],y[i]=y[i-1]+1-y[i]*2;
	for (int i=1;i<=64;i++) y[n-i+1]=0;
	for (int i=1;i<=n;i++) x[i+pre]=y[i];
	for (int i=1;i<=m;i++){
		int k1=getrand()%2+1,l=getrand()%n+1,r=getrand()%n+1,w=1-(getrand()%2)*2;
		k1=2;
		if (l>r) swap(l,r);
		q.push_back((atom){k1,l+pre,r+pre,w});
	}
	pre+=n;
}
void add1(int n,int m){
	int len=1,now=1; y[1]=1;
	while (len<=n){
		now++; y[len+1]=now;
		for (int i=1;i<=len;i++) y[len+1+i]=y[i];
		len=len*2+1;
	}
	for (int i=1;i<=n;i++) x[i+pre]=y[i];
	for (int i=1;i<=m;i++){
		int k1=getrand()%2+1,l=getrand()%n+1,r=getrand()%n+1,w=1-(getrand()%2)*2;
		if (i<=m/2) k1=2;
		if (l>r) swap(l,r);
		q.push_back((atom){k1,l+pre,r+pre,w});
	}
	pre+=n;
}
void add2(int n,int m,int K){
	for (int i=1;i<=n;i++) y[i]=0;
	for (int i=1;i<=K;i++) y[getrand()%n+1]=getrand()%K+1;
	y[n]=1;
	for (int i=1;i<=n;i++) x[i+pre]=y[i];
	for (int i=1;i<=m;i++){
		int k1=getrand()%2+1,l=getrand()%n+1,r=getrand()%n+1,w=1-(getrand()%2)*2;
		if (i<=m/2) k1=2,r=n; else if (i<=m*3/4) k1=2;
		if (l>r) swap(l,r);
		q.push_back((atom){k1,l+pre,r+pre,w});
	}
	pre+=n;
}
void add3(int n,int m){
	for (int i=1;i<=n;i++) y[i]=getrand()%2+1;
	for (int i=1;i<=n;i++) x[i+pre]=y[i];
	for (int i=1;i<=m;i++){
		int k1=getrand()%2+1,l=getrand()%n+1,r=getrand()%n+1,w=getrand()%20-10;
		if (i<=m/2) w=1-(getrand()%2)*2;
		if (l>r) swap(l,r);
		q.push_back((atom){k1,l+pre,r+pre,w});
	}
	pre+=n;
}
int main(){
//	freopen("string3.in","w",stdout);
	srand(time(0));
	printf("%d %d\n",n,m);
	add1(60000,8000);
	add2(60000,8000,4);
	add3(40000,6000);
	killhash(n,4000);
	cerr<<n<<endl;
	easyrand();
	for (int i=1;i<=n;i++){
		printf("%d",x[i]);
		if (i<n) putchar(' '); else putchar('\n');
	}
	for (int i=0;i<m;i++) q[i].print();
	return 0;
}
