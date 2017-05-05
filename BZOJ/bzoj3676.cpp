#include<bits/stdc++.h>
using namespace std;
#define N 301234
#define Z 26
#define ll long long
int n,cnt,sn,lst,siz[N],len[N],fail[N],s[N],ch[N][Z];
char str[N];
int node(int x){
	len[cnt]=x;
	return cnt++;
}
void init(){
	node(0);
	node(-1);
	fail[0]=1;s[0]=-1;
}
int trans(int x,int p){
	while(s[p-len[x]-1]!=s[p])
		x=fail[x];
	return x;
}
int insert(int x){
	int i,j;
	s[++sn]=x;
	j=trans(lst,sn);
	if(!ch[j][x]){
		i=node(len[j]+2);
		fail[i]=ch[trans(fail[j],sn)][x];
		ch[j][x]=i;
	}
	siz[lst=ch[j][x]]++;
}
int main(){
	int i;
	init();
	for(scanf("%s",str+1),n=strlen(str+1),i=1;i<=n;i++)
		insert(str[i]-'a');
	for(i=cnt-1;i>1;i--)siz[fail[i]]+=siz[i];
	ll ans=0;
	for(i=2;i<=cnt;i++)ans=max(ans,(ll)len[i]*siz[i]);
	printf("%lld\n",ans);
}
 
