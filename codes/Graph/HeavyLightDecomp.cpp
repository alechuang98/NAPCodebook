struct HLD{
	int n;
	vector<int>edge[MXN];
	int siz[MXN], dep[MXN];
	int cntp, re[MXN], in[MXN], out[MXN];
  int prt[MAXN][20], head[MAXN];
	void pre(int u, int pa){
		dep[u] = dep[pa] + 1;
		prt[0][u] = pa; siz[u] = 1; head[u] = u;
		for(int v : edge[u]){
			if( v == pa ) continue;
			pre(v, u);
			siz[u] += siz[v];
		}
		return ;
	}
	void dfs(int u){
		cntp++;
		in[u] = cntp;
		re[ cntp ] = u;
		sort(ALL(g[u]), [&](int a, int b){ return siz[a] > siz[b] });
		bool f = 1;
		for(int &v : edge[u]) if(v != prt[0][u]){
			if(f) head[v] = head[u], f = 0;
			dfs(v);
		}
		out[u] = cntp;
	}
	void addEdge(int u, int v){
		edge[u].pb(v);
		edge[v].pb(u);
	}
	void init(int _n){
		n = _n;
		rep1(i, 1, n+1) edge[i].clear();
	}
	void solve(){
		pre(1, 0);
		cntp = 0;
		dfs(1);
		rep1(i, 1, 20) rep1(j, 1, n+1){
			prt[i][j] = prt[i-1][ prt[i-1][j] ];
		}
	}
	vector< PII >getpath( int u, int v ){
		vector<PII> res;
		while( in[u] < in[ head[v] ] ){
			res.pb( MP(in[ head[v] ], in[v]) );
			v = prt[ head[v] ][0];
		}
		res.pb( MP(in[u], in[v]) );
		reverse( ALL(res) );
		return res;
	}

}tree;
