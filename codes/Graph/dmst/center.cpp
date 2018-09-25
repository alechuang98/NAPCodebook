vector<PII>edge[MAX];
int n, rt;
int pre[MAX], dis[MAX];
struct Center{
  void dfs(int u){
    for(auto x : edge[u]){
      if(x.F == pre[u]) continue;
      pre[x.F] = u; 
      dis[x.F] = dis[u] + x.S;
      dfs(x.F);
    }
    return ;
  }
  int build(int root){
    rep1(i, 1, n+1) dis[i] = 0;
    pre[root] = -1;
    dfs(root);
    int res = 0;
    rep1(i, 1, n+1) if(dis[i] > dis[res]) res = i;
    return res;
  }
  int sol(){
    int root = build(1);
    root = build(root);
    int d = dis[root];
    PII res = MP(INF, INF);
    while(root != -1){
      res = min( res, MP( max(d - dis[root], dis[root]), root) );
      root = pre[root];
    }
    rt = res.S;
    return res.F;
  }
}center;
