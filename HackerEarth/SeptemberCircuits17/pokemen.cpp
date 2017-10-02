/*
4 5
1 2
4 -
8 1
-5 3
1 1 3 3 7
0 2 4 -9
1 1 3 -3 7
0 3 -3 2
1 1 4 5 6
SAMPLE OUTPUT 
13
32
37
*/
#include <bits/stdc++.h>

#define fir first
#define sec second
using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}

namespace io{
	const int L = (1 << 18) + 1;
	
	char buf[L], *S , *T, c;
	 
	char getchar() {
		if(S == T) {
			T = (S = buf) + fread(buf, 1, L, stdin);
			return (S == T ? EOF : *S++);
		}
		return *S++;
	}
	
	int inp() {
		int x = 0, f = 1; char ch;
		for(ch = getchar(); !isdigit(ch); ch = getchar())
			if(ch == '-') f = -1;
		for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
		return x * f;
	}
};

using io :: inp;

const int MaxN = 201234;
const int MaxNode = 22001234;

int n, m; 

struct Point {
	int i, x, y;
	Point() {}
	Point(int i, int x, int y) : i(i), x(x), y(y) {}
}a[MaxN];

bool cmp_x(Point a, Point b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

struct info{
	LL x; int c;
	info(LL x = 0, int c = 0) : x(x), c(c){}
};

info operator + (info a, info b) {
	return info(a.x + b.x, a.c + b.c);		
}

info operator - (info a, info b) {
	return info(a.x - b.x, a.c - b.c);		
}

int px[MaxN << 2], py[MaxN << 2], pxn, pyn;
 
int find(int p[], int n, int x) {
	return lower_bound(p + 1, p + n + 1, x) - p;
}

struct bit_seg {
	int pcnt, rot[MaxN], lc[MaxNode], rc[MaxNode], ty; info seg[MaxNode];

	#define mid (l + r >> 1)
	
	info query(int p, int l, int r, int a, int b) {
		if(!p || (b < l || a > r)) return info(0, 0);
		if(a <= l && r <= b) {
		//	printf("(%d,%d), %lld\n", l, r, seg[p].y); 
			return seg[p];
		}
		
		info ans = info(0, 0);
		if(a <= mid)
			ans = ans + query(lc[p], l, mid, a, b);
		if(b > mid)
			ans = ans + query(rc[p], mid + 1, r, a, b);
		return ans;
	}	
	
	int X, Y;
	void modify(int &p, int l, int r, int x, int d) {
		if(!p) seg[p = ++pcnt] = info(0, 0), lc[p] = rc[p] = 0;
		if(l == r) {
//			cout << "get " << r << " " << d << endl;
			d == -1 ? 
				seg[p] = seg[p] - info((!ty ? X + Y : X - Y), 1):
				seg[p] = seg[p] + info((!ty ? X + Y : X - Y), 1);
		//	cout << seg[p].x << " " << seg[p].y << " " << seg[p].c << endl;
			return;
		}
		if(x <= mid) 
			modify(lc[p], l, mid, x, d);
		else
			modify(rc[p], mid + 1, r, x, d);
		seg[p] = seg[lc[p]] + seg[rc[p]];
	}

	info query(int r, int x, int y, LL &z) {
		info ans = info(0, 0);
		for(; r; r -= r & -r) {
			ans = ans + query(rot[r], 1, (ty ? pyn : pxn), x, y);
			z += seg[rot[r]].x;
		}
		return ans;
	}
	
	void modify(int p, int x, int d = 1) {
//		cout << "~" << p << " " << x << endl;
		X = a[p].x;
		Y = a[p].y;
		
		x = !ty ? find(px, pxn, X + Y) : find(py, pyn, X - Y);
		for(; p <= n; p += p & -p)
			modify(rot[p], 1, (ty ? pyn : pxn), x, d);
	}
	
	info Query(int l, int r, int x, int y, LL & z) {
		//cout << "@@@ " << l << " " << r << " " << x << " " << y << endl;
		assert(x >= 0 && x <= 210000);
		if(l - 1) {
			info qR = query(r, x, y, z);
			z = -z;
			info qL = query(l - 1, x, y, z);
			z = -z;
			return qR - qL;
		}
		else
			return query(r, x, y, z);
	}
	
}Tx;

int o[MaxN], l[MaxN], r[MaxN], x[MaxN], y[MaxN], ox[MaxN], oy[MaxN];
LL qX[MaxN], qY[MaxN];

void Modify(int p, int x, int y, int o = 1) {
	if(o) {
		Tx.modify(p, a[p].x + a[p].y, -1);
		a[p].x = x; a[p].y = y;
		Tx.modify(p, x + y);
	}
	else{
		Tx.modify(p, a[p].x - a[p].y, -1);
		a[p].x = x; a[p].y = y; 
		Tx.modify(p, x - y); 
	} 
}

LL Query(int l, int r, int x, int y, int i, int o = 1) {
	if(o) {
		LL xdw = 0;
		info xup = Tx.Query(l, r, find(px, pxn, x + y) + 1, pxn, xdw);
		//info xdw = Tx.query(l, r, 1, find(px, pxn, x + y));
		qX[i] = xup.x - (xdw - xup.x) - (LL) (x + y) * (xup.c - (r - l + 1 - xup.c));
	} else {
		LL ydw = 0;
		info yup = Tx.Query(l, r, find(py, pyn, x - y) + 1, pyn, ydw);
		//info ydw = Tx.query(l, r, 1, find(py, pyn, x - y));
		qY[i] = yup.x - (ydw - yup.x) - (LL) (x - y) * (yup.c - (r - l + 1 - yup.c));
	}

	/*LL qX = 0, qY = 0;
	for(int i = l; i <= r; i++) {
		int X = a[i].x + a[i].y;
		int Y = a[i].x - a[i].y;
		if(X > (x + y))
			qX += X;
		if(Y > (x - y))
			qY += Y;
	}*/
	
	//cout << "yup = " << qY << endl;
	//return (qX + qY) / 2; 
}

int main() {
	int i;
	n = inp(); m = inp();
	for(i = 1; i <= n; i++) {
		a[i].x = ox[i] = inp();
		a[i].y = oy[i] = inp();
		a[i].i = i;
	//	Tx.modify(i, a[i].x + a[i].y);
	//	Ty.modify(i, a[i].x - a[i].y);
	}
	
	px[++pxn] = py[++pyn] = 2e9 + 10;
	for(i = 1; i <= m; i++) {
		if(o[i] = inp()) {
			l[i] = inp(); r[i] = inp(); x[i] = inp(); y[i] = inp();
			px[++pxn] = x[i] + y[i];
			py[++pyn] = x[i] - y[i];
		}else {
			l[i] = inp(), x[i] = inp(), y[i] = inp();
		}
	} 
	
	sort(px + 1, px + pxn + 1); pxn = unique(px + 1, px + pxn + 1) - px - 1;
	sort(py + 1, py + pyn + 1); pyn = unique(py + 1, py + pyn + 1) - py - 1;
	
	for(i = 1; i <= n; i++) {
		Tx.modify(i, a[i].x + a[i].y);
	}

	for(i = 1; i <= m; i++) {
		if(o[i])
			Query(l[i], r[i], x[i], y[i], i);
		else
			Modify(l[i], x[i], y[i]); 
	}
	
	for(i = 1; i <= n; i++) a[i] = Point(i, ox[i], oy[i]); 
	
	Tx.ty = 1;
	memset(Tx.rot, 0, sizeof(Tx.rot));
	Tx.pcnt = 0;
	
	for(i = 1; i <= n; i++) {
		Tx.modify(i, a[i].x - a[i].y);
	}
	
	for(i = 1; i <= m; i++) {
		if(o[i])
			Query(l[i], r[i], x[i], y[i], i, 0);
		else
			Modify(l[i], x[i], y[i], 0); 
	}
	
	for(i = 1; i <= m; i++) if(o[i]) printf("%lld\n", (qY[i] + qX[i]) / 2); 
	return 0;
}
