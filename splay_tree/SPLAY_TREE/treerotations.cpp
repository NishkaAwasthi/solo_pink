#include <bits/stdc++.h>
#include <iostream>

using namespace std;
 
using ll = long long;
 
namespace splay {
template <class T>
struct node {
    T *f, *c[2];
    int size, val;
    node(int x) {
        f = c[0] = c[1] = nullptr;
        size = 1, val = x;
    }
    void update() {
        size = 1;
        for (int t = 0; t < 2; ++t)
            if (c[t]) size += c[t]->size;
    }
};
template <class T>
struct tree {
    T *root;
    T *new_node(int x) { return new T(x); }
    tree() { root = nullptr; }
    void rotate(T *n) {
        int v = n->f->c[0] == n;
        T *p = n->f, *m = n->c[v];
        if (p->f) p->f->c[p->f->c[1] == p] = n;
        n->f = p->f, n->c[v] = p;
        p->f = n, p->c[v ^ 1] = m;
        if (m) m->f = p;
        p->update(), n->update();
    }
    void splay(T *n, T *s = nullptr) {
        while (n->f != s) {
            T *m = n->f, *l = m->f;
            if (l == s)
                rotate(n);
            else if ((l->c[0] == m) == (m->c[0] == n))
                rotate(m), rotate(n);
            else
                rotate(n), rotate(n);
        }
        if (!s) root = n;
    }
    int size() { return root->size; }
    //! Insert node n, return its order in tree
    int insert(T *n) {
        T *c = root; int v, pos = 0;
        if (!c) { root = n; return 0; }
        while ((v = (c->val < n->val), 1) &&
             (v && (++pos) && c->c[0] && (pos += c->c[0]->size), c->c[v]) &&
             (c = c->c[v]) );
        c->c[v] = n, n->f = c, splay(n);
        // cerr << "insert returns: " << pos << endl;
        return pos;
    }
    // Call merge on root of a different tree
    // Returns inversions from merging other subtree into this tree
    ll merge(T* n) {
        ll ans = 0;
        if (n->c[0]) ans += merge(n->c[0]);
        ans += root->size - insert(new_node(n->val));
        if (n->c[1]) ans += merge(n->c[1]);
        return ans;
    }
    void dealloc(T *n) {
        if (!n) return;
        dealloc(n->c[0]);
        dealloc(n->c[1]);
        delete n;
    }
};
} // namespace splay
 
struct node: splay::node<node> {
    node(int x) : splay::node<node>(x) { }
};
using tree = splay::tree<node>;
 
pair<tree, ll> readTree() {
    int x; cin >> x;
    if (x != 0) {
        tree tmp;
        tmp.insert(tmp.new_node(x));
        return { tmp, 0 };
    }
    auto l = readTree(), r = readTree();
    auto lt = l.first, rt = r.first;
    if (lt.size() < rt.size()) swap(lt, rt);
 
    ll tot = 1ll * lt.size() * rt.size();
    ll ans = lt.merge(rt.root);
    rt.dealloc(rt.root);
    ans = min(ans, tot - ans) + l.second + r.second;
    return { lt, ans };
}
 
int main() {
    int n; cin >> n;
    cout << readTree().second << endl;
}