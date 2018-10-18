struct cp{
    double a,b;
    cp(){};
    cp(double _a, double _b){
        a = _a, b = _b;
    }
    cp operator +(const cp &o){ return cp(a+o.a, b+o.b); }
    cp operator -(const cp &o){ return cp(a-o.a, b-o.b); }
    cp operator *(const cp &o){ return cp(a*o.a-b*o.b, b*o.a+a*o.b); }
    cp operator *(const double &o){ return cp(a*o, b*o); }
    cp operator !(){ return cp(a, -b); }
}w[MXN];
int pos[MXN];
void fft_init(int len){
    int j = 0;
    while((1<<j) < len) j++;
    j--;
    rep(i, len) pos[i] = pos[i>>1]>>1 | ((i&1)<<j);
    return ;
}
void fft(cp *x, int len, int sta){
    rep(i, len) if(i < pos[i]) swap(x[i], x[pos[i]]);
    w[0] = cp(1,0);
    for(unsigned i = 2; i <= len; i <<= 1){
        cp g = cp(cos(2*PI/i), sin(2*PI/i)*sta);
        for(int j = i>>1; j >= 0; j -= 2) w[j] = w[j>>1];
        for(int j = 1; j < (i>>1); j += 2) w[j] = w[j-1]*g;
        for(int j = 0; j < len; j += i){
            cp *a = x+j, *b = a+(i>>1);
            rep(l, i>>1){
                cp o = b[l]*w[l];
                b[l] = a[l]-o;
                a[l] = a[l]+o;
            }
        }
    }
  if(sta == -1) rep(i, len) x[i].a /= len, x[i].b /= len;
    return ;
}
cp xt[MXN], yt[MXN], zt[MXN];
LL st[3][MXN];
void FFT(int a, int b, int l1, int l2, int c){
    int len = 1;
    while(len <= (l1+l2)>>1) len <<= 1;
    fft_init(len);
    rep1(i, l1>>1, len) xt[i].a = xt[i].b = 0; 
    rep(i, l1) (i&1 ? xt[i>>1].b : xt[i>>1].a) = st[a][i];
    fft(xt, len, 1);

    rep1(i, l2>>1, len) yt[i].a = yt[i].b = 0; 
    rep(i, l1) (i&1 ? yt[i>>1].b : yt[i>>1].a) = st[b][i];
    fft(yt, len, 1);


    rep(i, len>>1){
        int j = len - 1&len - i;
        zt[i] = xt[i]*yt[i] - (xt[i]-!xt[j])*(yt[i]-!yt[j])*(w[i]+cp(1,0))*0.25;
    }
    rep1(i, len>>1, len){
        int j = len - 1&len - i;
        zt[i] = xt[i]*yt[i] - (xt[i]-!xt[j])*(yt[i]-!yt[j])*(cp(1,0)-w[i^len>>1])*0.25;
    }
    fft(zt, len, -1);
    rep(i, l1 + l2 - 1){
        if(i&1) st[c][i] = (LL)(zt[i>>1].b+0.5);
        else st[c][i] = (LL)(zt[i>>1].a+0.5);
    }
    return ;
}