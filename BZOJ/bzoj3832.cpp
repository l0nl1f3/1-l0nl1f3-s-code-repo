#include <cstring>
#include <cstdio>
#include <algorithm>
#include<iostream>
#include <set>

using namespace std;

const int MAXN = 75005, MAXM = 1e5 + 5;

multiset<int> d;
int n, m, deg[MAXN], ord[MAXN], f[MAXN], g[MAXN];
int tot, In[MAXN], Out[MAXN], Next[MAXM * 2], Go[MAXM * 2]; 

void link_in(int u, int v) {
    Next[++ tot] = In[u], In[u] = tot, Go[tot] = v;
}

void link_out(int u, int v) {
    Next[++ tot] = Out[u], Out[u] = tot, Go[tot] = v;
}

void add(int now) {
    for (int p = Out[now]; p; p = Next[p]) 
        d.insert(f[now] + g[Go[p]] + 1);
    d.insert(f[now]);
}

void del(int now) {
    for (int p = In[now]; p; p = Next[p]) 
        d.erase(d.find(g[now] + f[Go[p]] + 1));
    d.erase(d.find(g[now]));
}

void prepare() {
    static int d[MAXN];
    int l = 0, r = 0, cnt = 0;
    for (int i = 1; i <= n; i ++) 
        if (deg[i] == 0) d[++ r] = i, ord[++ cnt] = i;
    while (l <= r) {
        int now = d[++ l];
        for (int p = Out[now]; p; p = Next[p]) {
            int v = Go[p];
            deg[v] --;
            if (deg[v] == 0) {
                ord[++ cnt] = v;
                d[++ r] = v;
            }
        }
    }
    for (int i = 1; i <= n; i ++) {
        int now = d[i];
        for (int p = Out[now]; p; p = Next[p]) 
            f[Go[p]] = max(f[now] + 1, f[Go[p]]);
    }
    
    for (int i = n; i; i --) {
        int now = d[i];
        for (int p = In[now]; p; p = Next[p]) 
            g[Go[p]] = max(g[now] + 1, g[Go[p]]);
    }
    for(int i=1;i<=n;i++)std::cout<<g[i]<<' ';
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i ++) {
        int u, v;
        scanf("%d%d", &u, &v);
        link_out(u, v);
        link_in(v, u);
        deg[v] ++;
    }
    prepare();
    for (int i = 1; i <= n; i ++) 
        d.insert(g[i]);
    int ans = n + 1, id;
    for (int i = 1; i <= n; i ++) {
        int now = ord[i];
        del(now);
        int s = *--d.end();
        if (s < ans || s == ans && now < id) ans = s, id = now;
        add(now);
    }
    printf("%d %d\n", id, ans);
}
