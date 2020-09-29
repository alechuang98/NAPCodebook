const int MEM = 560004;
struct Treap {
  static Treap mem[MEM], *pmem;
  Treap *l, *r;
	LL val, mxn, sum, d;
  int size, pri;
  Treap () : l(NULL), r(NULL), size(0) {}
  Treap (LL _val) : 
    l(NULL), r(NULL), val(_val), mxn(_val), sum(_val), d(0), size(1), pri(rand()){}
} Treap::mem[MEM], *Treap::pmem = Treap::mem;

int size(const Treap *t) {
    return t ? t->size : 0; 
}
LL _mxn(Treap *t) {
    return t ? t->mxn : -INF;
}
LL _sum(Treap *t) {
    return t ? t->sum : 0;
}
void pull(Treap *t) {
  if (!t) return;
  t->size = size(t->l) + size(t->r) + 1;
  t->mxn = max(t->val, max(_mxn(t->l), _mxn(t->r)));
  t->sum = t->val + _sum(t->l) + _sum(t->r);
}
void pushdown(Treap *t) {
    if (!t) return ;
    if (t->l) { 
        t->l->mxn += t->d;
        t->l->val += t->d;
				t->l->sum += size(t->l)*(t->d);
        t->l->d += t->d;
    }
    if (t->r) {
        t->r->mxn += t->d;
        t->r->val += t->d;
				t->l->sum += size(t->r)*(t->d);
        t->r->d += t->d;
    }
    t->d = 0;
}
Treap *merge(Treap *a, Treap *b) {
	if(!a || !b) return a ? a : b;
  if (a->pri > b->pri) {
		pushdown(a);
    a->r = merge(a->r, b);
		pull(a);
		return a;
  } else {
		pushdown(b);
    b->l = merge(a, b->l);
		pull(b);
		return b;
  }
}
void split_val(Treap *t, int k, Treap *&a, Treap *&b) {
  pushdown(t);
  if(!t) a = b = NULL;
  else if(t->val <= k){
    a = t;
    split_val(t->r, k, a->r, b);
    pull(a);
  } else{
    b = t;
    split_val(t->l, k, a, b->l);
    pull(b);
  }
}
void split_size(Treap *t, int k, Treap *&a, Treap *&b) {
  pushdown(t);
  if(!t) a = b = NULL;
  else if(size(t->l) + 1 <= k){
    a = t;
    split_size(t->r, k - size(t->l) - 1, a->r, b);
    pull(a);
  } else{
    b = t;
    split_size(t->l, k, a, b->l);
    pull(b);
  }
}
int main() {
	Treap *l = new (Treap::pmem++) Treap(5);
	return 0;
}

