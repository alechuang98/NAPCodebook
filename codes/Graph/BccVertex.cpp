struct BccVertex{
	int n, nBcc, cntp, root, dfn[MXN], low[MXN];
	vector<int> E[MXN];
	vector<int> bcc[MXN];
	int top;
	int stk[MXN];
	bool is_cut[MXN];
	void init(int _n){
		n = _n;
		nBcc = cntp = 0;
		for(int i = 1; i <= n; ++i) E[i].clear();
	}
	void add_edge(int u, int v){
		E[u].pb(v);
		E[v].pb(u);
	}
	void dfs(int u, int pa){
		dfn[u] = low[u] = cntp++;
		stk[top++] = u;
		int son = 0;
		for(auto v : E[u]){
			if(v == pa) continue;
			if(dfn[v] == -1){
				son++;
				dfs(v, u);
				if(low[v] >= dfn[u]){
					is_cut[u] = 1;
					bcc[nBcc].clear();
					do{
						bcc[nBcc].pb(stk[--top]);
					} while(stk[top] != v);
					bcc[nBcc++].pb(u);
				}
			} else{
				low[u] = min(low[u], dfn[v]);
			}
		}
		if(u == root && son < 2) is_cut[u] = 0;
	}
	vector<vector<int>> solve(){
		vector<vector<int>> res;
		for(int i = 1; i <= n; ++i){
			dfn[i] = low[i] = -1;
			is_cut[i] = 0;
		}
		for(int i = 1; i <= n; ++i){
			if(dfn[i] == -1){
				top = 0;
				root = i;
				dfs(i, i);
			}
		}
		for(int i = 0; i < nBcc; ++i){
			res.pb(bcc[i]);
		}
		return res;
	}
}graph;

