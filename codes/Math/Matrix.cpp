struct Mat{
  int n, m;
  LL a[MXN][MXN];
  void init(int _n, int _m){
    n = _n, m = _m;
    rep1(i, 1, n+1) rep1(j, 1, m+1){
      a[i][j] = 0;
    }
  }
  Mat operator *(const Mat & p2){
    Mat res; res.init(n, p2.m);
    rep1(i, 1, n+1) rep1(j, 1, m+1) rep1(k, 1, p2.m+1){
      res.a[i][k] = (res.a[i][k] + a[i][j]*p2.a[j][k])%mod;
    }
    return res;
  }
  Mat operator ^(const LL & p2){
    LL t = p2 - 1;
    Mat res = *this, x = *this;
    while(t){
      if(t & 1){
        res = res*x;
      }
      t >>= 1;
      x = x*x;
    }
    return res;
  }
};
