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
	cin >> testcases;
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

const int N = 1e4 + 5, inf = 2e9;

inline int merge(const int &a, const int b) {
	return a > b ? a : b;
}

struct inter_segtree {
	constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }

	int n, sz, st[N << 2];

	inter_segtree(int n = N) {
		sz = 1 << lg2(n);
	}

	inter_segtree(int *a, int *b) {
		n = b - a, sz = 1 << lg2(n), build(a);
	}

	void build(int *a) {
		for (int p = 0; p < n; p++)
			st[p + sz] = a[p];
		for (int p = sz - 1; p; p--)
			st[p] = merge(st[p << 1], st[p << 1 | 1]);
	}

	void update(int p, int v) {
		for (st[p += sz - 1] = v; p >>= 1; )
			st[p] = merge(st[p << 1], st[p << 1 | 1]);
	}

	int query(int l, int r) {
		int lval = -inf, rval = -inf;
		for (l += sz - 1, r += sz; l < r; l >>= 1, r >>= 1) {
			if (l & 1) lval = merge(lval, st[l ++]);
			if (r & 1) rval = merge(st[-- r], rval);
		}
		return merge(lval, rval);
	}
};

int n, a[N], val[N], sz[N], nxt[N], par[N];

struct edge {
	int v, w, id;
	edge(int _v = 0, int _w = 0, int _id = 0)
		: v(_v), w(_w), id(_id) {}
};

vector<edge> adj[N];

void pre_dfs(int u, int p) {
	sz[u] = 1, nxt[u] = u, par[u] = p;
	for (auto &ed : adj[u]) if (ed.v != p) {
		val[ed.id] = ed.v;
		pre_dfs(ed.v, u);
		sz[u] += sz[ed.v];
	}

	for (auto &ed : adj[u]) if (ed.v == p) {
		swap(ed, adj[u].back()), adj[u].pop_back(); break ;
	}

	for (auto &ed : adj[u]) 
		if (sz[ed.v] > sz[adj[u][0].v]) swap(ed, adj[u][0]);
}

int tin[N], tout[N], timer;

void dfs_hld(int u, int vl = -inf) {
	tin[u] = ++ timer;
	a[timer] = vl;

	for (auto ed : adj[u]) if (ed.v != par[u]) {
		if (ed.v == adj[u][0].v)
			nxt[ed.v] = nxt[u];
		dfs_hld(ed.v, ed.w);
	}

	tout[u] = timer;
}

void Hollwo_Pelw() {
	cin >> n, timer = 0;
	for (int i = 1; i <= n; i++) adj[i].clear();
	for (int i = 1, u, v, w; i < n; i++)
		cin >> u >> v >> w, adj[u].emplace_back(v, w, i), adj[v].emplace_back(u, w, i);

	pre_dfs(1, 1), dfs_hld(1);
	inter_segtree st(a + 1, a + n + 1);

	string s;
	for (int u, v; cin >> s; ) {
		if (s == "DONE") return ;
		cin >> u >> v;
		if (s == "QUERY") {
			int res = -inf;
			while (1) {
				if (nxt[u] == nxt[v]) {
					if (tin[u] > tin[v]) swap(u, v);
					res = merge(res, st.query(tin[u] + 1, tin[v])); break ;
				}
				if (tin[nxt[u]] > tin[nxt[v]]) swap(u, v);
				res = merge(res, st.query(tin[nxt[v]], tin[v]));
				v = par[nxt[v]];
			}
			cout << res << '\n';
		} else {
			st.update(tin[val[u]], v);
		}
	}
}
