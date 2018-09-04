struct cp{
    double _a,_b;
    cp operator +(const cp &o)const {return (cp){_a+o._a,_b+o._b};}
    cp operator -(const cp &o)const {return (cp){_a-o._a,_b-o._b};}
    cp operator *(const cp &o)const {return (cp){_a*o._a-_b*o._b,_b*o._a+_a*o._b};}
    cp operator *(const double &o)const {return (cp){_a*o,_b*o};}
    cp operator !() const{return (cp){_a,-_b};}
}w[MAX];
int pos[MAX];
void fft_init(int len){
    int j = 0;
    while((1<<j) < len) j++;
    j--;
    for(int i=0;i<len;i++)
        pos[i] = pos[i>>1]>>1 | ((i&1)<<j);
}
void fft(cp *_x, int len, int sta){
    for(int i = 0; i < len; i++)
        if(i < pos[i]) swap(_x[i], _x[pos[i]]);
    w[0] = (cp){1,0};
    for(unsigned i = 2; i <= len; i <<= 1){
        cp g=(cp){cos(2*PI/i),sin(2*PI/i)*sta};
        for(int j = i>>1; j >= 0; j -= 2) w[j] = w[j>>1];
        for(int j = 1; j < (i>>1); j += 2)w[j] = w[j-1]*g;
        for(int j = 0; j < len; j += i){
            cp *_a = _x+j, *_b = _a+(i>>1);
            for(int l = 0; l < (i>>1); l++){
                cp o = _b[l]*w[l];
                _b[l] = _a[l]-o;
                _a[l] = _a[l]+o;
            }
        }
    }
    if(sta == -1) for(int i = 0; i < len; i++) _x[i]._a /= len, _x[i]._b /= len;
}
cp _x[MAX],_y[MAX],_z[MAX];
void FFT(int _a, int _b, int l1, int l2, int _c){
    int len = 1;
    while(len <= (l1+l2)>>1)len <<= 1;
    fft_init(len);
    for(int i = l1>>1; i<len; i++) _x[i]._a = _x[i]._b = 0;
    for(int i = l2>>1; i<len; i++) _y[i]._a = _y[i]._b = 0;
    for(int i = 0; i < l1; i++) (i&1 ? _x[i>>1]._b : _x[i>>1]._a) = st[_a][i];
    for(int i = 0; i < l2; i++) (i&1 ? _y[i>>1]._b : _y[i>>1]._a) = st[_b][i];
    fft(_x, len, 1), fft(_y, len, 1);
    for(int i = 0; i < len>>1; i++){
        int j = len - 1&len - i;
        _z[i] = _x[i]*_y[i] - (_x[i]-!_x[j])*(_y[i]-!_y[j])*(w[i]+(cp){1,0})*0.25;
    }
    for(int i = len>>1; i < len; i++){
        int j = len - 1&len -i;
        _z[i] = _x[i]*_y[i] - (_x[i]-!_x[j])*(_y[i]-!_y[j])*((cp){1,0}-w[i^len>>1])*0.25;
    }
    fft(_z, len, -1);
    for(int i = 0; i < l1 + l2 - 1;i++)
        if(i&1) st[_c][i] = (LL)(_z[i>>1]._b+0.5);
        else st[_c][i] = (LL)(_z[i>>1]._a+0.5);
}
