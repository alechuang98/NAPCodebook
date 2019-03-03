struct Flow{
	struct Edge{
		int v, f, re;
		Edge(){};
		Edge(int _v, int _f, int _re) {
			v = _v, f = _f, re = _re;
		}
	};
	int n, s, t;
	vector<Edge> E[1007];
	bool ck[1007];
	void init(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		for (int i = 0; i < n; i++)
			E[i].clear();
	}
	void add_edge(int u, int v, int f) {
		E[u].pb({v, f, SZ(E[v])});
		E[v].pb({u, 0, SZ(E[u])-1});
	}
	int dfs(int u, int nf) {
		ck[u] = 1;
		if (u == t) return nf;
		int res = 0;
		for (auto &it : E[u]) {
			if (it.f > 0 && !ck[it.v]) {
				int tf = dfs(it.v, min(nf, it.f));
				res += tf; nf -= tf; it.f -= tf;
				E[it.v][it.re].f += tf;
				if (nf == 0) return res;
			}
		}
		return res;
	}
	int flow(int res = 0) {
		int f;
		while ( (f = dfs(s, 2147483647)) ) {
			res += f;
			for (int i = 0; i < n; i++)
				ck[i] = 0;
		}
		return res;
	}
}flow;
