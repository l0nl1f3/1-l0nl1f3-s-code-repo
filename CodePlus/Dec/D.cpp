#include <bits/stdc++.h>

#define fir first
#define sec second
#define MP make_pair
#define PB push_back

using namespace std;
typedef long long LL;
typedef unsigned long long u64;

template <typename T> inline bool cmin(T & a, const T & b) { return a > b ? a = b, 1 : 0;}
template <typename T> inline bool cmax(T & a, const T & b) { return a < b ? a = b, 1 : 0;}
int read() {
	int x = 0, f = 1;char ch;
	for(ch = getchar(); !isdigit(ch); ch = getchar())
		if(ch == '-') f = -1;
	for(; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
	return x * f;
}

#define eps 1e-7
typedef double db;

const int MaxN = 101234, MaxM = 101234;

bool dcmp(db a, db b) {
	return (a - b > -eps && a - b < eps);
}
 
struct point {
	db x, y;
	bool operator < (point b) const {
		return dcmp(x, b.x) ? y < b.y : x < b.x;
	}
}; 

struct line {
	double A, B, C, k;
	line() {}
	line(db a, db b, db c) {
		A = a; B = b; C = c;
		if(dcmp(b, 0)) k = 1e50; else k = - a / b;
	} 
	bool operator < (line b) const {
		if(dcmp(k, b.k)) {
			if(!dcmp(B, 0))
				return C / B < b.C / b.B;
			return C / A > b.C / b.A;
		}
		return k < b.k;
	}
}L[MaxN];

struct ev {
	point x; int i;
	bool operator < (ev b) const {
		return x < b.x;
	}
}q[MaxM];


struct info {
	int L1, L2; point x;
	bool operator < (info b) const {
		if(dcmp(x.x, b.x.x) && dcmp(x.y, b.x.y)) {
			return L1 == b.L1 ? L2 < b.L2 : L1 < b.L1;
		}
		return x < b.x;
	}
}c[MaxN << 2];

double det(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

double F(line a, point x) {
	return a.A * x.x + a.B * x.y + a.C; 
}

point inter(line a, line b) {
	point res;
	res.y = (b.C * a.A - a.C * b.A) / (a.B * b.A - a.A * b.B);
	if(!dcmp(a.A, 0))
		res.x = -(res.y * a.B + a.C) / a.A;
	else
		res.x = -(res.y * b.B + b.C) / b.A;
	return res;	
}

int n, m, cn; db _L;

db ans[MaxN]; int xx[MaxN], yy[MaxN];

int find(point p) {
	int L = 0, R = n, mid;
	while(L < R) {
		mid = L + R >> 1;
		int id = xx[mid];
		if(F(:: L[id], p) > 0)
			R = mid;
		else
			L = mid + 1;
	}
	return L;
}

vector<int> Q[MaxN]; db S[MaxN]; point lst[MaxN];

void up(int x) {
	for(int i = 0; i < Q[x].size(); i++)	
		ans[Q[x][i]] = S[x];
	S[x] = 0; Q[x].clear();
}


int main() {
	int i, j, k;
	n = read(); m = read(); cin >> _L;
	for(i = 0; i < n; i++) {
		db x, y, z;
		scanf("%lf%lf%lf", &x, &y, &z);
		if(dcmp(y, 0)) {
			if(x > 0) x = -x, z = -z;
		}else if(y < 0) x = -x, y = -y, z = -z;
		L[i] = line(x, y, z);
	} 
	for(i = 0; i < m; i++) scanf("%lf%lf", &q[i].x.x, &q[i].x.y), q[i].i = i;
	
	L[n++] = line(-1, 0, _L);
	L[n++] = line(-1, 0, -_L);
	L[n++] = line(0, 1, -_L);
	L[n++] = line(0, 1, _L);
	sort(L, L + n);
	for(i = 0; i < n; i++) {
		for(j = i + 1; j < n; j++)
			if(!dcmp(L[i].k, L[j].k)) {
				c[cn] = (info) {i, j, inter(L[i], L[j])};++cn;
			}
	}
	sort(q, q + m); sort(c, c + cn);
	
	for(i = 0; i < n; i++) xx[i] = yy[i] = i;
	for(i = j = 0; i < cn; i++) {
		while(q[j].x < c[i].x && j < m) {
			int x = find(q[j].x); Q[x].push_back(q[j++].i);
		}
		int a = yy[c[i].L1];
		int b = yy[c[i].L2];
		double x_a = det(c[i].x, lst[a]);
		double x_b = det(lst[b], c[i].x);
		S[b] -= x_a + x_b; up(b);
		S[a] += x_a;  S[b + 1] += x_b;
		lst[a] = lst[b] = c[i].x;
		swap(xx[a], xx[b]); yy[xx[a]] = a; yy[xx[b]] = b;
 	}
 	
	for(i = 0; i < m; i++) printf("%.2lf\n", -ans[i] / 2.0);
	return 0;
}

