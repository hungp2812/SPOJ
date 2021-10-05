/*
// is short or still long ???
hollwo_pelw's template(short)
// Note : -Dhollwo_pelw_local
*/

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// #include <ext/rope>

using namespace std;
// using namespace __gnu_pbds;
// using namespace __gnu_cxx;

void FAST_IO(string filein = "", string fileout = "", string fileerr = ""){
	if (fopen(filein.c_str(), "r")){
		freopen(filein.c_str(), "r", stdin);
		freopen(fileout.c_str(), "w", stdout);
#ifdef hollwo_pelw_local
		freopen(fileerr.c_str(), "w", stderr);
#endif
	}
	cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
}

void Hollwo_Pelw();

signed main(){
#ifdef hollwo_pelw_local
	FAST_IO("input.inp", "output.out", "error.err");
	auto start = chrono::steady_clock::now();
#else
	FAST_IO("hollwo_pelw.inp", "hollwo_pelw.out");
#endif
	int testcases = 1;
	// cin >> testcases;
	for (int test = 1; test <= testcases; test++){
		// cout << "Case #" << test << ": ";
		Hollwo_Pelw();
	}
#ifdef hollwo_pelw_local
	auto end = chrono::steady_clock::now();
	cout << "\nExcution time : " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif
	return 0;
}

const int N = 3e4 + 5, M = 1e6 + 5;

int n, q, prv[M], root[N], nnode;

struct node {
	int sum, lc, rc;
	node (int _sum = 0, int _lc = 0, int _rc = 0)
		: sum(_sum), lc(_lc), rc(_rc) {}
} st[M << 1];

#define tm (tl + tr >> 1)
#define left st[id].lc, tl, tm
#define right st[id].rc, tm + 1, tr

inline int apply(int id) {
	st[++ nnode] = st[id];
	return st[nnode].sum ++, nnode;
}

inline int merge(int lc, int rc) {
	st[++ nnode] = node(
		st[lc].sum + st[rc].sum,
		lc, rc
	);
	return nnode;
}

int update(int v, int id, int tl = 1, int tr = n) {
	if (v < tl || v > tr) return id;
	if (tl == tr) {
		return apply(id);
	} else {
		return merge(update(v, left), update(v, right));
	}
}

int query(int l, int r, int id, int tl = 1, int tr = n) {
	if (l > tr || tl > r) return 0;
	if (l <= tl && tr <= r)
		return st[id].sum;
	return query(l, r, left) + query(l, r, right);
}

void Hollwo_Pelw() {
	cin >> n;
	for (int i = 1, a; i <= n; i++) {
		cin >> a, root[i] = update(prv[a], root[i - 1]), prv[a] = i;
	}
	cin >> q;
	for (int i = 1, l, r; i <= q; i++)
		cin >> l >> r, cout << r - l + 1 - query(l, r, root[r]) << '\n';
}

