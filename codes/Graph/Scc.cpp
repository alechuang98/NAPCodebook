struct Scc{
	int n, cntp, num;
	int in[MXN], re[MXN], gp[MXN];
	vector<int>edge[MXN], re_edge[MXN];
	void pre(int u){
		in[u] = 1;
		for (int v : edge[u]) {
			if (in[v]) continue;
			pre(v);
		}
		re[++cntp] = u;
		return ;
	}
	void dfs(int u){
		in[u] = 1;
		gp[u] = num;
		for (int v : re_edge[u]) {
			if (in[v]) continue;
			dfs(v);
		}
		return ;
	}
	void add_edge(int u, int v){
		edge[u].pb(v);
		re_edge[v].pb(u);
		return ;
	}
	void init(int _n){
		n = _n;
		for (int i = 1; i <= n; i++) {
			edge[i].clear();
			re_edge[i].clear();
		}
		return ;
	}
	void solve(){
		cntp = num = 0;
		fill(in + 1, in + n + 1, 0);
		for (int i = 1; i <= n; i++) {
			if (!in[i]) pre(i);
		}
		fill(in + 1, in + n + 1, 0);
		reverse( re + 1, re + n + 1 );
		for (int i = 1; i <= n; i++) { 
			int p = re[i];
			if(!in[p]){
				num++; dfs(p);
			}
		}
		return ;
	}
};
