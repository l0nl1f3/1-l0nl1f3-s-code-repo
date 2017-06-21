#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
using namespace std;
typedef unsigned long long u64;
u64 a,mod=1,L=1;
u64 tr[4],b[4],tmp[4];
vector <u64> ans,ans2;

u64 Mul(u64 a,u64 b) {
	if (mod<=1000000000)
		return a*b%mod;
	return b?((Mul(a,b>>16)<<16)+a*(b&65535))%mod:0;
}

void Mul(u64 *a,u64 *b) {
	static u64 c[4];
	c[0]=(Mul(a[0],b[0])+Mul(a[1],b[2]))%mod;
	c[1]=(Mul(a[0],b[1])+Mul(a[1],b[3]))%mod;
	c[2]=(Mul(a[2],b[0])+Mul(a[3],b[2]))%mod;
	c[3]=(Mul(a[2],b[1])+Mul(a[3],b[3]))%mod;
	memcpy(a,c,sizeof c);
}

void init(u64 *tr,u64 L) {
	static u64 tc[4];
	tc[0]=0; tc[1]=1; tc[2]=1; tc[3]=1;
	tr[0]=1; tr[1]=0; tr[2]=0; tr[3]=1;
	for (;L;L>>=1,Mul(tc,tc))
		if (L&1) Mul(tr,tc);
}

int main () {
	freopen("words.in","r",stdin);
	freopen("words.out","w",stdout);
	cin>>a;
	ans.push_back(0);
	for (int p=1;p<=13;p++) {
		mod*=10;
		init(tr,L);
		init(b,0);
		u64 L2=0;
		do {
			for (int i=0;i<ans.size();i++) {
				init(tmp,ans[i]+L2);
				if (tmp[2]==a%mod) ans2.push_back(ans[i]+L2);
			}
			L2+=L;
			Mul(b,tr);
		}while(b[0]!=1||b[1]!=0||b[2]!=0||b[3]!=1);
		swap(ans,ans2);
		ans2.clear();
		L=L2;
	}
	if (ans.empty()) puts("-1");
	else cout<<ans[0]<<endl;
	return 0;
}
