const int MEM = 360004;
struct Treap {
  static Treap mem[MEM], *pmem;
  Treap *l, *r;
  int val;
  int size;
	int pri;
  Treap () : l(NULL), r(NULL), size(0) {}
  Treap (int _val) : 
    l(NULL), r(NULL), val(_val), size(1), pri(rand()){}
} Treap::mem[MEM], *Treap::pmem = Treap::mem;

int size(const Treap *t) {
	return t ? t->size : 0; 
}
void pull(Treap *t) {
  if (!t) return;
  t->size = size(t->l) + size(t->r) + 1;
}
Treap *merge(Treap *a, Treap *b) {
	if(!a || !b) return a ? a : b;
  if(a->pri > b->pri){
    a->r = merge(a->r, b);
		pull(a);
		return a;
  } else{
    b->l = merge(a, b->l);
		pull(b);
		return b;
  }
}
void split(Treap *t, int k, Treap *&a, Treap *&b) {
  if(!t) a = b = NULL;
  else if(t->val <= k){
    a = t;
    split(t->r, k, a->r, b);
    pull(a);
  } else{
    b = t;
    split(t->l, k, a, b->l);
    pull(b);
  }
}
