int a[MXN], _a[MXN];
struct Seg{
	static Seg mem[20*MXN], *pmem;
	int siz;
	Seg *ls, *rs;
	Seg(){};
	Seg(int l, int r) : siz(0) {
		if (l == r) return ;
		int m = (l + r) >> 1;
		ls = new (pmem++) Seg(l, m);
		rs = new (pmem++) Seg(m+1, r);
	}
	Seg *ins(int l, int r, int x){
		Seg *t = new (pmem++) Seg(*this);
		t->siz++;
		if (l != r) {
			int mid = (l + r) >> 1;
			if (x <= mid) t->ls = t->ls->ins(l, mid, x);
			else t->rs = t->rs->ins(mid+1, r, x);
		}
		return t;
	}
} Seg::mem[20*MXN], *Seg::pmem = mem;
int ask(Seg *tl, Seg *tr, int l, int r, int k) {
	if (l == r) return l;
	int m = (l + r) >> 1, lsz = tr->ls->siz - tl->ls->siz;
	if (k <= lsz) return ask(tl->ls, tr->ls, l, m, k);
	else return ask(tl->rs, tr->rs, m+1, r, k - lsz);
}
Seg *seg[MXN];
int main() {
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		_a[i] = a[i];
	}
	sort(_a + 1, _a + n + 1);
	seg[0] = new (Seg::pmem++) Seg(1, n);
	for (int i = 1; i <= n; i++) {
		int x = lower_bound(_a + 1, _a + n + 1, a[i]) - _a;
		seg[i] = seg[i-1]->ins(1, n, x);
	}
	while (m--) {
		int l, r, k; scanf("%d %d %d", &l, &r, &k);
		int x = ask(seg[l-1], seg[r], 1, n, k);
		printf("%d\n", _a[x]);
	}
	return 0;
}