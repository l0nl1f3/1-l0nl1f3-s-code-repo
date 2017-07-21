#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int inp() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

const int MaxN = 1001234, MaxM = 2001234, MaxV = MaxM << 1, MaxE = MaxM * 6;
struct edge{
	int to, nxt;LL v;
}e[MaxE];
int cnt, lst[MaxV]; LL dis[MaxV]; 
void ins(int a, int b, LL c){
	e[++cnt] = (edge){b, lst[a], c}; lst[a] = cnt;
}
void lnk(int a, int b, LL c){
	ins(a, b, c);
	ins(b, a, c);
}

#include<ext/pb_ds/priority_queue.hpp>
#define pa pair<LL,int>
using namespace __gnu_pbds;
typedef __gnu_pbds::priority_queue<pa, greater<pa>, pairing_heap_tag > heap;

heap::point_iterator id[MaxV];
LL dijkstra(int s, int t){
    heap q;
    for(int i = 0; i < MaxV; i++) dis[i] = 1e12;
    dis[s] = 0;id[s] = q.push(make_pair(0, s));
    while(!q.empty()){
        int c = q.top().sec; q.pop();
        for(int i = lst[c], b; b = e[i].to, i; i = e[i].nxt)
            if(cmin(dis[b], dis[c] + e[i].v))
                if(id[b] != 0)
                    q.modify(id[b], make_pair(dis[b], b));
                else 
					id[b] = q.push(make_pair(dis[b], b));
    }
    return dis[t];
}

int n, m, u[MaxM], v[MaxM]; LL w[MaxM];
struct info{
	int l, r; LL x;
};
info g[MaxE], t[MaxE]; int tn, gn;
bool cmp(info a, info b){
	return a.x < b.x;
}
#define pub push_back
int main() {
	int i, j;
	n = inp(); m = inp();
	for(i = 1; i <= m; i++){
		scanf("%d %d %lld", u + i, v + i, w + i);
		lnk(u[i], v[i], w[i]);
	}
	for(i = 1; i <= n; i++){
		for(tn = 0, j = lst[i]; j; j = e[j].nxt)
			t[++tn] = (info){(j - 1) ^ 1, j - 1, e[j].v};
		sort(t + 1, t + tn + 1, cmp);
		for(j = 1; j <= tn; j++){
			g[++gn] = t[j];
			if(j != 1) g[++gn] = (info) {t[j].r, t[j - 1].r, 0};
			if(j != tn) g[++gn] = (info) {t[j].r, t[j + 1].r, t[j + 1].x - t[j].x}; 
		}
	}
	
	int s = cnt + 1, t = s + 1;
	for(int i = lst[1]; i; i = e[i].nxt)
		g[++gn] = (info){s, i - 1, e[i].v};
	for(int i = lst[n]; i; i = e[i].nxt)
		g[++gn] = (info){i - 1, t, 0};
	cnt = 0; memset(lst, 0, sizeof(lst));
	for(int i = 1; i <= gn; i++) 
		ins(g[i].l, g[i].r, g[i].x);
		
	cout<<dijkstra(s, t); 
	return 0;
}



