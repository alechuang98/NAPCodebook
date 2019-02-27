vector<PII> edge[MXN];
int n, rt;
int pre[MXN], dis[MXN];
struct Center{
	void dfs(int u) {
		for (auto x : edge[u]) {
			if (x.F == pre[u]) continue;
			pre[x.F] = u;
			dis[x.F] = dis[u] + x.S;
			dfs(x.F);
		}
	}	
	int build(int root) {
		for (int i = 1; i <= n; i++) dis[i] = 0;
		pre[root] = -1;
		dfs(root);
		int res = 0;
		for (int i = 1; i <= n; i++)
			if (dis[i] > dis[res]) 
				res = i;
		return res;
	}
	int solve() {
		int root = build(1);
		root = build(root);
		int d = dis[root];
		PII res = {INF, INF};
		while (root != -1) {
			res = min( res, {max(d - dis[root], dis[root]), root} );
			root = pre[root];
		}
		rt = res.S;
		return res.F;
	}
}center;
