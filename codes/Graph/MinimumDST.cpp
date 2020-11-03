tuple<int, int, int> edge[ M ];
int dis[ N ], fr[ N ], vis[ N ], id[ N ];
int sol(int n, int m, int root) {
    int ans = 0;
    while (true) {
        for (int i = 1; i <= n; i++)
            dis[i] = INF;
        for (int i = 1; i <= m; i++) {
            int u, v, w; tie(u, v, w) = edge[i]; 
            if (dis[v] > w) {
                dis[v] = w;
                fr[v] = u;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (i == root) continue ;
            ans += dis[i];
            if (dis[i] == INF) return -1;
        }
        for (int i = 1; i <= n; i++)
            id[i] = vis[i] = 0;
    
        int num = 0;
        for (int i = 1; i <= n; i++) {
            int v = i;
            while (v != root && vis[v] != i && !id[v]) {
                vis[v] = i;
                v = fr[v];
            }
            if (v != root && !id[v]) {
                id[v] = ++num;
                for (int u = fr[v]; u != v; u = fr[u]) {
                    id[u] = num;
                }
            }
        }
        if (!num) break ;
        for (int i = 1; i <= n; i++)
            if (!id[i]) id[i] = ++num;
        int nm = 0;
        for (int i = 1; i <= m; i++) {
            int u, v, w; tie(u, v, w) = edge[i];
            if (id[u] == id[v]) continue ;
            edge[++nm] = {id[u], id[v], w - dis[v]};
        }
        m = nm;
        n = num;
        root = id[root];
    }
    return ans;
}
