const int bsz = 1048576;
inline int rc(){ //readchar
	static char buf[bsz];
	static char *ptr = buf, *end = buf;
	if(ptr == end){
		if((end = buf + fread(buf,1,sz,stdin)) == buf) return EOF;
		ptr = buf;
	}
	return *ptr++;
}
inline int ri(int &x) { //readint
    static char c, neg;
    while((c = rc()) < '-') if(c == EOF) return 0;	
    neg = (c == '-') ? -1 : 1;
    x = (neg == 1) ? c-'0' : 0;
    while((c = rc()) >= '0')
        x = (x << 3) + (x << 1) + c-'0';
    x *= neg;
    return 1;
}

