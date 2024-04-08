#include <bits/stdc++.h>
#include <iostream>

using namespace std;
 
// #define cerr if (0) cerr
 
using ll = long long;
 
template <class T>
struct node {
  T *f, *c[2]; int size, x; ll sum, val; 
  node() { f = c[0] = c[1] = nullptr; size = 1; val = 0; }
  void push_down() {}
  void update() {
    size = 1, sum = x, val = 0;
    for (int t = 0; t < 2; ++t)
      if (c[t]) {
        size += c[t]->size;
        sum += c[t]->sum;
        val += c[t]->val;
      } 
    if (c[0]) val += 1LL * c[0]->size * x - c[0]->sum;
    if (c[1]) val += c[1]->sum - 1LL * c[1]->size * x;
    if (c[0] && c[1]) val += c[1]->sum * c[0]->size - c[0]->sum * c[1]->size;
  } 
};
template <class T>
struct reversible_node : node<T> {
  int r;
  reversible_node() : node<T>() { r = 0; }
  void push_down() {
    node<T>::push_down();
    if (r) {
      for (int t = 0; t < 2; ++t)
        if (node<T>::c[t]) node<T>::c[t]->reverse();
      r = 0; } }
  void update() { node<T>::update(); }
  //! Reverse the range of this node.
  void reverse() {
    std::swap(node<T>::c[0], node<T>::c[1]);
    r = r ^ 1; } };
template <class T, int MAXSIZE = 500000>
struct tree {
  T pool[2 * MAXSIZE + 2]; int cap; T *root;
  T *new_node(const T &val = T()) { return &pool[cap++]; }
  tree() { cap = 0; }
  void rotate(T *n) {
    int v = n->f->c[0] == n; T *p = n->f, *m = n->c[v];
    if (p->f) p->f->c[p->f->c[1] == p] = n;
    n->f = p->f, n->c[v] = p; p->f = n, p->c[v ^ 1] = m;
    if (m) m->f = p; p->update(), n->update(); }
  void splay(T *n, T *s = nullptr) {
    while (n->f != s) {
      T *m = n->f, *l = m->f;
      if (l == s) rotate(n);
      else if ((l->c[0] == m) == (m->c[0] == n)) rotate(m), rotate(n);
      else rotate(n), rotate(n); }
    if (!s) root = n; }
  int size() { return root->size - 2; }
  //! Insert node n to position pos.
  void insert(T *n) {
    T *c = root; 
    if (!c) { root = n; return; }
    
    int v;
    while (((v = c->x < n->x), c->c[v]) && (c=c->c[v]));
    c->c[v] = n, n->f = c, splay(n); }
  //! Find the node with x value. If sp is true, splay it.
//   T *find(int x, int sp = true) {
//     // cerr << "finding " << x << endl;
//     T *c = root; int v; 
//     while ((v = c->x < x, 1) && c->c[v] && (c = c->c[v]));
//     if (sp) splay(c);
//     return c; }
  
  T *findl(int x, int sp = true) {
    T *c = root, *r = nullptr; int v, mx = INT_MIN; 
    if (c->x <= x && c->x >= mx) {
        mx = c->x;
        r = c;
    }
    while ((v = c->x < x, 1) && c->c[v] && (c = c->c[v])) {
        if (c->x <= x && c->x >= mx) {
            mx = c->x;
            r = c;
        }
    };
    if (!c || c->x != x) c = r;
    assert(c);
    if (sp) splay(c);
    return c; 
  }
 
  T *findr(int x, int sp = true) {
    T *c = root, *r = nullptr; int v, mn = INT_MAX; 
    if (c->x >= x && c->x <= mn) {
        mn = c->x;
        r = c;
    }
    while ((v = c->x < x, 1) && c->c[v] && (c = c->c[v])) {
        if (c->x >= x && c->x <= mn) {
            mn = c->x;
            r = c;
        }
    };
    if (!c || c->x != x) c = r;
    assert(c);
    if (sp) splay(c);
    return c; 
  }
 
  //! Find the range [posl, posr) on the splay tree.
  T *find_range(int posl, int posr) {
    T *r = findr(posr), *l = findl(posl - 1, false);
    // cerr << r->x << endl;
    // cerr << l->x << endl;
    assert(l);
    assert(l != r);
    splay(l, r);
    if (l->c[1]) l->c[1]->push_down();
    return l->c[1]; }
  //! Insert nn of size nn_size to position pos.
//   void insert_range(T **nn, int nn_size, int pos) {
//     T *r = find(pos), *l = find(pos - 1, false), *c = l;
//     splay(l, r);
//     for (int i = 0; i < nn_size; ++i) c->c[1] = nn[i], nn[i]->f = c, c = nn[i];
//     for (int i = nn_size - 1; i >= 0; --i) nn[i]->update();
//     l->update(), r->update(), splay(nn[nn_size - 1]); }
  void dealloc(T *n) {
    if (!n) return;
    dealloc(n->c[0]); dealloc(n->c[1]);
    /*pool.dealloc(n);*/ }
  //! Remove from position [posl, posr).
  void erase_range(int posl, int posr) {
    T *n = find_range(posl, posr);
 
    n->f->c[1] = nullptr, n->f->update(), n->f->f->update(), n->f = nullptr;
    dealloc(n); } 
 
    void print(T* n) {
        if (!n) return;
        cerr << "(" << n->x << ", " << n->val << "): ";
        for (int i = 0; i < 2; ++i) {
            if (n->c[i]) cerr << n->c[i]->x << " ";
            else cerr << "[null] ";
        }
        cerr << endl;
 
        print(n->c[0]);
        print(n->c[1]);
    }
};
 
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
 
const int MAXN = 1e5+2;
struct mynode : node<mynode> {};
tree<mynode, MAXN> t;
 
int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);
 
    int n; cin >> n;
 
    mynode *lg = t.new_node(), *rg = t.new_node();
    lg->sum=lg->x=INT_MIN;
    rg->sum=rg->x=INT_MAX;
    t.insert(lg), t.insert(rg);
 
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
        mynode* tmp = t.new_node();
        tmp->sum = tmp->x = pos[i];
        t.insert(tmp);
    }
 
    // t.print(t.root);
    // cerr << "-------------\n";
 
    int q; cin >> q;
    while (q-- > 0) {
        int typ, a, b; cin >> typ >> a >> b;
        // cerr << "===========\n";
        // cerr << "QUERY = " << typ << " " << a << " " << b << endl;
        if (typ == 1) {
            --a;
            t.erase_range(pos[a], pos[a]+1);
            pos[a] += b;
            mynode* tmp = t.new_node();
            tmp->sum = tmp->x = pos[a];
            t.insert(tmp);
        } else if (typ == 2) {
            // cerr << "ANSWER: ";
            mynode* tmp = t.find_range(a, b+1);
            if (!tmp) cout << 0 << "\n";
            else cout << tmp->val << "\n";
        } else {
            cerr << "unrecognized type .. " << endl;
            assert(false);
        }
 
        // t.print(t.root);
    }
}