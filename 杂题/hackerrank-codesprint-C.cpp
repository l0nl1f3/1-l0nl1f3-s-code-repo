#include<bits/stdc++.h>
#define N 101234
using namespace std;
int q,id,idm[N];
map<string,int>fn;
priority_queue<int,vector<int>,greater<int> >pq[N];
int gid(string x){
	if(!fn[x])
		fn[x]=++id;
	return fn[x];
}
int main(){
	int i,j,k;
	scanf("%d",&q);
	string op,on,nn; 
	memset(idm,-1,sizeof(idm));
	for(i=1;i<=q;i++){
		cin>>op>>on;
		if(op[0]=='c'){
			j=gid(on);
			int nid=0;
			if(pq[j].size()){
				nid=pq[j].top();pq[j].pop();
			}else nid=++idm[j];
			cout<<"+ "<<on;
			if(nid)cout<<"("<<nid<<")\n";
			else cout<<"\n"; 
		}else if(op[0]=='d'){
			string onn="";
			for(int i=0;i<on.size();i++)
				if(on[i]=='(')break;
				else onn=onn+on[i];
			j=gid(onn);int k=0;
			for(int i=0;i<on.size();i++)
				if(isdigit(on[i]))k=k*10+on[i]-'0';
			pq[j].push(k);
			cout<<"- "<<on<<"\n";
		}else if(op[0]=='r'){
			cin>>nn;
			string onn="";
			for(int i=0;i<on.size();i++)
				if(on[i]=='(')break;
				else onn=onn+on[i];
			j=gid(onn);int k=0;
			for(int i=0;i<on.size();i++)
				if(isdigit(on[i]))k=k*10+on[i]-'0';
			pq[j].push(k);
			cout<<"r "<<on; 
			on=nn;
			j=gid(on);
			int nid=0;
			if(pq[j].size()){
				nid=pq[j].top();pq[j].pop();
			}else nid=++idm[j];
			cout<<" -> "<<on;
			if(nid)cout<<"("<<nid<<")\n";
			else cout<<"\n"; 
		}
	}
	return 0;
}
