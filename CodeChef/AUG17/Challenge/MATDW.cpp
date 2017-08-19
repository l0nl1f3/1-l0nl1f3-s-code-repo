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

const int MaxEvents = 201234; 
const int MaxType = 20, MaxN = 201234;

struct HardDrive {
	int price, r, w, cap, id;
	HardDrive() {
		price = r = w = cap = 0; id = -1;
	}
	HardDrive(int a, int b, int c, int d, int e) : price(a), r(b), w(c), cap(d), id(e) {}
}ty[MaxType];
	 
int n, m;

bool valwr(HardDrive a, HardDrive b) {
	//return a.r < b.r || (a.r == b.r && a.w < b.w);
	//return a.p < b.p;
	return a.w < b.w || (a.w == b.w && a.r < b.r);
}

bool valrw(HardDrive a, HardDrive b) {
	//return a.r < b.r || (a.r == b.r && a.w < b.w);
	//return a.p < b.p;
	return a.r < b.r|| (a.r == b.r && a.w < b.w);
}

void InputHrdDrvDetail() {
	for(int i = 0; i < m; i++) {
		int a, b, c, d;
		a = inp(); b = inp(); c = inp(); d = inp();
		ty[i] = HardDrive(a, b, c, d, i);
	}
}

void flush() {
	fflush(stdout);
} 

void buy(int hid, HardDrive &buf) {
	printf("p b %d\n", ty[hid].id);
	buf = ty[hid];
	flush();
}

void store(int hid = -1, int pid = -1) {
	printf("p s %d %d\n", hid, pid);
	flush();
}

void retrieve(int hid = -1, int pid = -1) {
	printf("p i %d %d\n", hid, pid);
	flush(); 
}

void backup(int hs, int ps, int hd, int pd, int L) {
	printf("p %d %d %d %d %d\n", hs, ps, L, hd, pd);
	flush();
}

void getNew() { 
	puts("g"); 
	flush();	
}

void EndInter() {
	puts("end");
	flush();
}

int penalty;

namespace TaskManager {
	
	HardDrive a[MaxN];
	HardDrive bak[MaxN]; int nBak;
	
	int bakp[MaxN * 10], s[MaxN], e[MaxN], h[MaxN], rel[MaxN], res[MaxN];
	int pool[MaxN * 10], st[MaxN], ed[MaxN], head[MaxN];
	int cus_st[MaxN], cus_dr[MaxN], cnt;
	
	
	int getEvent(int &id, int &q) {
		getNew();
		int option = inp(); 
		if(option < 2) 
			id = inp(), q = inp();
		else 
			id = inp();
		return option;
	}
	
	void Accident(int hid) {
		if(rel[hid] != -1) {
			backup(rel[hid], res[hid], hid, st[hid], ed[hid] - st[hid] + 1);			
			for(int i = st[hid]; i < ed[hid]; i++)
				pool[i] = bakp[res[hid] + i];
			rel[hid] = -1;
		}else {
			for(int i = st[hid]; i <= ed[hid]; i++)
				pool[i] = -1;
			head[hid] = st[hid];
		}
	}
	
	void Backup(int hid, int L, int R, int cid) {
		//bakup [L, R)
		
		int i, j;
		int q = R - L;
		
		for(i = 0; i < nBak; i++) {
			if(h[i] + q - 1 < e[i])
				break;
		}
		
		if(i == nBak) return;
		
		rel[hid] = i + cnt;
		res[hid] = h[i];
		for(j = h[i]; j < h[i] + q; j++)
			bakp[j] = cid;
			
		backup(hid, L, i + cnt, h[i], q);
		h[i] += q;
		
	}
	
	void Store(int cid, int q) {
		int i, j;
		for(i = 0; i < cnt; i++)
			if(head[i] + q - 1 < ed[i]) break;
		
		if(i == m) {
			store();
			return;
		}
		
		for(j = head[i]; j < head[i] + q; j++)
			pool[j] = cid;
		
		cus_dr[cid] = i;
		cus_st[cid] = head[i] - st[i];
		
		store(i, head[i] - st[i]);
		
		Backup(i, head[i], head[i] + q, cid);
		
		head[i] += q; 
	}

	void Retrieve(int cid, int q) {
		int u = cus_dr[cid], v = cus_st[cid];

		if(u == -1) {
			retrieve();
			return;
		}
		if(pool[st[u] + v + q] != cid) {
			retrieve();
			return;
		}
		
		retrieve(u, v + q);
	}	
	
	int main() {
		int i, j, k;
		
		memset(st, -1, sizeof(st));
		memset(cus_dr, -1, sizeof(cus_dr));
		memset(cus_st, -1, sizeof(cus_st));
		memset(rel, -1, sizeof(rel));
		
		sort(ty, ty + m, valwr);
		cnt = m;
		for(i = 0; i < cnt; i++) {
			buy(0, a[i]);
			
			if(i) st[i] = head[i] = ed[i - 1] + 1; 
			else st[i] = 0;
			
			ed[i] = st[i] + a[i].cap - 1;
		}
		
		sort(ty, ty + m, valrw);
		nBak = m;
		for(i = 0; i < nBak; i++) {
			buy(0, bak[i]);
			
			if(i) s[i] = h[i] = e[i - 1] + 1;
			else st[i] = 0;
			
			e[i] = s[i] + bak[i].cap - 1;
		}
		
		for(int T = 0; T < n; T++) {
			int cid, q;
			int O = getEvent(cid, q);
			if(O == 0)
				Store(cid, q);
			if(O == 1)
				Retrieve(cid, q);
			if(O == 2)
				Accident(cid);
		}
		
		EndInter();
		
		return 0;
	}
}

namespace ManageNothing {
	
	int getEvent(int &id, int &q) {
		getNew();
		int option = inp(); 
		if(option < 2) 
			id = inp(), q = inp();
		return option;
	}
	
	int main() {
		for(int T = 0; T < n; T++) {
			int cid, q;
			int O = getEvent(cid, q);
			if(O == 0)
				store();
			if(O == 1)
				retrieve();
		}
		
		EndInter();
		
		return 0;
	}
}
int main() {
	int i;
	
	n = inp(); m = inp();
	
	InputHrdDrvDetail();
	
	penalty = inp();
	
	//if(penalty <= 100000)
	//	ManageNothing :: main();
	//else
		TaskManager :: main();
	
	return 0;
}



