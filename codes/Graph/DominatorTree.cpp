const int MAXN = 100010;
struct DominatorTree{
  int n , m , s;
  vector< int > edge[ MAXN ] , re_edge[ MAXN ];
  vector< int > cov[ MAXN ];
  int dfn[ MAXN ] , nfd[ MAXN ] , cntp;
  int par[ MAXN ];
  int sdom[ MAXN ] , idom[ MAXN ];
  int mom[ MAXN ] , mn[ MAXN ];
  inline bool cmp( int u , int v ) { 
		return dfn[ u ] < dfn[ v ]; 
	}
  int eval( int u ){
    if( mom[ u ] == u ) return u;
    int res = eval( mom[ u ] );
    if(cmp( sdom[ mn[ mom[ u ] ] ] , sdom[ mn[ u ] ] ))
      mn[ u ] = mn[ mom[ u ] ];
    return mom[ u ] = res;
  }
  void init( int _n , int _m , int _s ){
    cntp = 0; n = _n; m = _m; s = _s;
    for (int i = 1; i <= n; i++) {
			edge[ i ].clear(); 
			re_edge[ i ].clear();
		}
  }
  void add_edge( int u , int v ){
    edge[ u ].pb( v );
    re_edge[ v ].pb( u );
  }
  void dfs( int u ){
    dfn[ u ] = ++cntp;
    nfd[ cntp ] = u;
    for( int v : edge[ u ] ) if( dfn[ v ] == 0 ){
      par[ v ] = u;
      dfs( v );
    }
  }
  void solve(){
    for (int i = 1; i <= n; i++) {
      dfn[ i ] = nfd[ i ] = 0;
      cov[ i ].clear();
      mom[ i ] = mn[ i ] = sdom[ i ] = i;
    }
    dfs( s );
    for (int i = n; i >= 2; i--) {
      int u = nfd[ i ];
      if( u == 0 ) continue ;
      for( int v : re_edge[ u ] ) if( dfn[ v ] ){
        eval( v );
        if( cmp( sdom[ mn[ v ] ] , sdom[ u ] ) )
          sdom[ u ] = sdom[ mn[ v ] ];
      }
      cov[ sdom[ u ] ].push_back( u );
      mom[ u ] = par[ u ];
      for( int w : cov[ par[ u ] ] ){
        eval( w );
        if( cmp( sdom[ mn[ w ] ] , par[ u ] ) )
          idom[ w ] = mn[ w ];
        else idom[ w ] = par[ u ];
      }
      cov[ par[ u ] ].clear();
    }
    for (int i = 2; i <= n; i++) {
      int u = nfd[ i ];
      if( u == 0 ) continue ;
      if( idom[ u ] != sdom[ u ] )
        idom[ u ] = idom[ idom[ u ] ];
    }
  }
} domT;
