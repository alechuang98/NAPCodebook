const int MAXN = 100010;
const int LOG  = 19;
struct HLD{
	int n;
	vector<int> g[MAXN];
	int sz[MAXN], dep[MAXN];
	int ts, tid[MAXN], tdi[MAXN], tl[MAXN], tr[MAXN];
	//	ts : timestamp , useless after yutruli
	//	tid[ u ] : pos. of node u in the seq.
	//	tdi[ i ] : node at pos i of the seq.
	//	tl , tr[ u ] : subtree interval in the seq. of node u
	int prt[MAXN][LOG], head[MAXN];
	// head[ u ] : head of the chain contains u
	void dfssz(int u, int p){
		dep[u] = dep[p] + 1;
		prt[u][0] = p; sz[u] = 1; head[u] = u;
		for(int& v:g[u]) if(v != p){
			dep[v] = dep[u] + 1;
			dfssz(v, u);
			sz[u] += sz[v];
		}
	}
	void dfshl(int u){
		ts++;
		tid[u] = tl[u] = tr[u] = ts;
		tdi[tid[u]] = u;
		sort(ALL(g[u]),
				 [&](int a, int b){return sz[a] > sz[b];});
		bool flag = 1;
		for(int& v:g[u]) if(v != prt[u][0]){
			if(flag) head[v] = head[u], flag = 0;
			dfshl(v);
			tr[u] = tr[v];
		}
	}
	vector<PII> getPath(int u , int v) {
		vector<PII> res;
		while( tid[ u ] < tid[ head[ v ] ] ){
			res.pb( PII(tid[ head[ v ] ] , tid[ v ]) );
			v = prt[ head[ v ] ][ 0 ];
		}
		res.pb( PII( tid[ u ] , tid[ v ] ) );
		reverse( ALL( res ) );
		return res;
		/* res : list of intervals from u to v
		 * u must be ancestor of v
		 * usage :
		 * vector< PII >& path = tree.getPath( u , v )
		 * for( PII tp : path ) {
		 *	 int l , r;tie( l , r ) = tp;
		 *	 upd( l , r );
		 *	 uu = tree.tdi[ l ] , vv = tree.tdi[ r ];
		 *	 uu ~> vv is a heavy path on tree
		 * }
		 */
	}
} tree;
