// Max flow with lower/upper bound on edges
// source = 1 , sink = n
const int N = 1005;
const int M = 3005;
int in[ N ] , out[ N ];
int l[ M ] , r[ M ] , a[ M ] , b[ M ];
int n, m;
int solve (int n, int m) {
	int st = 0, ed = n + 1; 
	flow.init(n + 2, st, ed);
	for (int i = 1; i <= n; i++) {
		in[i] = out[i] = 0;
	}
	for (int i = 1; i <= m; i++) {
		in[ r[ i ] ] += a[ i ];
		out[ l[ i ] ] += a[ i ];
		flow.add_edge( l[ i ] , r[ i ] , b[ i ] - a[ i ] );
		// flow from l[i] to r[i] must in [a[ i ], b[ i ]]
	}
	int nd = 0;
	for (int i = 1; i <= n; i++) {
		if (in[ i ] < out[ i ]) {
			flow.add_edge( i , ed , out[ i ] - in[ i ] );
			nd += out[ i ] - in[ i ];
		}
		if (out[ i ] < in[ i ])
			flow.add_edge( st , i , in[ i ] - out[ i ] );
	}
	// original sink to source
	flow.add_edge( n , 1 , INF );
	if( flow.flow() != nd )
		// no solution
		return -1;
	int ans = flow.E[ 1 ].back().f; // source to sink
	flow.E[ 1 ].back().f = flow.E[ n ].back().f = 0;
	// take out super source and super sink
	for (int i = 0; i < SZ(flow.E[ st ]); i++) {
		flow.E[ st ][ i ].f = 0;
		Dinic::Edge &e = flow.E[ st ][ i ];
		flow.E[ e.v ][ e.re ].f = 0;
	}
	for (int i = 0; i < SZ(flow.E[ ed ]); i++){
		flow.E[ ed ][ i ].f = 0;
		Dinic::Edge &e = flow.E[ ed ][ i ];
		flow.E[ e.v ][ e.re ].f = 0;
	}
	flow.add_edge( st , 1 , INF );
	flow.add_edge( n , ed , INF );
	return ans + flow.flow();
}

