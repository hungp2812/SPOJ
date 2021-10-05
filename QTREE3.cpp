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

const int N = 1e5 + 5;

int n, q, par[N], nxt[N], sz[N];
vector<int> adj[N];

void pre_dfs(int u, int p) {
	par[u] = p, nxt[u] = u, sz[u] = 1;
	for (auto v : adj[u]) if (v != p) {
		pre_dfs(v, u);
		sz[u] += sz[v];
	}
	for (auto &v : adj[u]) if (v == p) {
		swap(v, adj[u].back()), adj[u].pop_back(); break ;
	}
	for (auto &v : adj[u]) 
		if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
}

int tin[N], timer, val[N];

void dfs_hld(int u) {
	tin[u] = ++ timer;
	val[timer] = u;
	for (auto v : adj[u]) {
		if (v == adj[u][0])
			nxt[v] = nxt[u]; 
		dfs_hld(v);
	}
}

int st[N << 2];

#define left id << 1, tl, tm
#define right id << 1 | 1, tm + 1, tr

void update(int p, int id = 1, int tl = 1, int tr = n) {
	if (tl == tr) {
		st[id] ^= 1;
	} else {
		int tm = tl + tr >> 1;
		(p > tm ? update(p, right)
				: update(p, left));
		st[id] = st[id << 1] + st[id << 1 | 1];
	}
}

int query(int l, int r, int id = 1, int tl = 1, int tr = n) {
	if (tl > r || l > tr) return -1;
	if (l <= tl && tr <= r){
		if (!st[id]) return -1;
		while (tl != tr) {
			int tm = tl + tr >> 1;
			if (st[id << 1])
				tr = tm, id = id << 1;
			else
				tl = tm + 1, id = id << 1 | 1;
		}
		return tl;
	}
	int tm = tl + tr >> 1;
	int res = query(l, r, left);
	return (~res ? res : query(l, r, right));
}

void Hollwo_Pelw() {
	cin >> n >> q, timer = 0;
	for (int i = 1; i <= n; i++) adj[i].clear();
	for (int i = 1, u, v; i < n; i++)
		cin >> u >> v, adj[u].push_back(v), adj[v].push_back(u);
	pre_dfs(1, 1), dfs_hld(1);
	
	fill(st + 1, st + 4 * n + 5, 0);

	for (int t, v; q --; ) {
		cin >> t >> v;
		if (t == 0) {
			update(tin[v]);
		} else {
			int res = -1;
			while (1) {
				int t = query(tin[nxt[v]], tin[v]);
				// cout << t << ' ';
				if (t != -1) res = val[t];
				if (nxt[v] == 1) break ;
				v = par[nxt[v]];
			}
			cout << res << '\n';
		}
	}
}
