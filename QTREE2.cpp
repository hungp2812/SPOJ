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

const int N = 1e4 + 5;

int n, h[N], d[N], par[14][N];
vector<pair<int, int>> adj[N];

void pre_dfs(int u, int p) {
	par[0][u] = p;
	for (int i = 1; i < 14; i++)
		par[i][u] = par[i - 1][par[i - 1][u]];

	for (auto vw : adj[u]) if (vw.first != p) {
		int v = vw.first, w = vw.second;
		d[v] = d[u] + w, h[v] = h[u] + 1;
		pre_dfs(v, u);
	}
}

inline int lift(int u, int v) {
	for (int i = 13; ~i; i--)
		if (v >> i & 1) u = par[i][u];
	return u;
}

inline int lca(int u, int v) {
	if (h[u] > h[v]) swap(u, v);
	v = lift(v, h[v] - h[u]);
	
	if (u == v) return u;

	for (int i = 13; ~i; i--)
		if (par[i][u] ^ par[i][v])
			u = par[i][u], v = par[i][v];

	return par[0][u]; 
}

inline int dist(int u, int v) {
	return d[u] + d[v] - 2 * d[lca(u, v)];
}

inline int kth(int u, int v, int k) {
	int w = lca(u, v), dd = h[u] + h[v] - 2 * h[w];
	if (h[u] - h[w] >= k - 1)
		return lift(u, k - 1);
	return lift(v, dd - k + 1);
}

void Hollwo_Pelw() {
	cin >> n;
	for (int i = 1; i <= n; i++) adj[i].clear();
	for (int i = 1, u, v, w; i < n; i++)
		cin >> u >> v >> w, adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
	pre_dfs(1, 0);
	string s;
	for (int u, v, k; cin >> s; ) {
		if (s == "DONE") return ;
		if (s == "DIST") {
			cin >> u >> v;
			cout << dist(u, v) << '\n';
		} else {
			cin >> u >> v >> k;
			cout << kth(u, v, k) << '\n';
		}
	}
}
