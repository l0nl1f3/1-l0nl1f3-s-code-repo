#include<bits/stdc++.h>
using namespace std;
#define N 1001234
#define Z 26
char h[N];
int n,ch[N][Z],s[N],nxt[N],id[N],rot=1,cnt=1;
struct edge{int to,nxt;}e[N];int ecnt,lst[N];
void ins(int a,int b){
	e[++ecnt]=(edge){b,lst[a]};lst[a]=ecnt;
}
void lnk(int a,int b){
	ins(a,b);ins(b,a);
}
int ins(char*s){
	int p=rot;
	for(int i=0,o;o=s[i]-'a',s[i];i++){
		if(!ch[p][o])
			ch[p][o]=++cnt;
		p=ch[p][o];++::s[p];
	}
	return p;
} 
	queue<int>q;
int build(){
	for(int i=0;i<Z;i++){
		if(!ch[rot][i]){
			ch[rot][i]=rot;
		}else{
			nxt[ch[rot][i]]=rot;
			q.push(ch[rot][i]);
		}
	}
	while(!q.empty()){
		int c=q.front();q.pop();
		for(int i=0;i<Z;i++){
			if(!ch[c][i]){
				ch[c][i]=ch[nxt[c]][i];
			}else{
				nxt[ch[c][i]]=ch[nxt[c]][i];
				q.push(ch[c][i]);
			}
		}
	}
	for(int i=2;i<=cnt;i++)lnk(i,nxt[i]);
}
void dfs(int x,int f){
	for(int i=lst[x],b;b=e[i].to,i;i=e[i].nxt)
		if(b!=f){
			dfs(b,x); 
			s[x]+=s[b];
		}
}
int main(){
	int i;
	for(scanf("%d",&n),i=1;i<=n;i++){
		scanf("%s",h);
		id[i]=ins(h);
	}
	build();
	dfs(1,0);
	for(i=1;i<=n;i++)printf("%d\n",s[id[i]]);
}
