#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
#include <iostream>
 
namespace allocator {
 
// Array allocator.
template <class T, int MAXSIZE>
struct array {
  T v[MAXSIZE], *top;
  array() : top(v) {}
  T *alloc(const T &val = T()) { return &(*top++ = val); }
  void dealloc(T *p) {}
};
 
// Stack-based array allocator.
template <class T, int MAXSIZE>
struct stack {
  T v[MAXSIZE];
  T *spot[MAXSIZE], **top;
  stack() {
    for (int i = 0; i < MAXSIZE; ++i) spot[i] = v + i;
    top = spot + MAXSIZE;
  }
  T *alloc(const T &val = T()) { return &(**--top = val); }
  void dealloc(T *p) { *top++ = p; }
};
 
}  // namespace allocator
 
 
 
namespace splay {
 
// Abstract node struct.
template <class T>
struct node {
  T *f, *c[2];
  int size, val;
  node() {
    f = c[0] = c[1] = nullptr;
    size = 1, val = -1;
  }
  void push_down() {}
  void update() {
    size = 1;
    for (int t = 0; t < 2; ++t)
      if (c[t]) size += c[t]->size;
  }
};
 
// Abstract reversible node struct.
template <class T>
struct reversible_node : node<T> {
  int r;
  reversible_node() : node<T>() { r = 0; }
  void push_down() {
    node<T>::push_down();
    if (r) {
      for (int t = 0; t < 2; ++t)
        if (node<T>::c[t]) node<T>::c[t]->reverse();
      r = 0;
    }
  }
  void update() { node<T>::update(); }
  // Reverse the range of this node.
  void reverse() {
    std::swap(node<T>::c[0], node<T>::c[1]);
    r = r ^ 1;
  }
};
 
template <class T, int MAXSIZE = 500000,
          class alloc = allocator::array<T, MAXSIZE + 2>>
struct tree {
  alloc pool;
  T *root;
  // Get a new node from the pool.
  T *new_node(const T &val = T()) { return pool.alloc(val); }
  tree() {
    root = nullptr;
  }
  // Helper function to rotate node.
void rotate(T *n) {
    if (!n || !n->f) return; // Safety check
 
    bool dir = n == n->f->c[1]; // Direction of rotation
    T *p = n->f;
    T *g = p->f; // Grandparent
    T *c = n->c[!dir]; // Child to be swapped
 
    if (g) g->c[g->c[1] == p] = n; 
    n->f = g;
 
    n->c[!dir] = p;
    p->f = n;
 
    p->c[dir] = c;
    if (c) c->f = p;
 
    p->update(); 
    n->update();
  } 
  // Splay n so that it is under s (or to root if s is null).
  void splay(T *n, T *s = nullptr) {
    if (!n) return;
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
  // Get the size of the tree.
  int size() { return root->size - 2; }
  // Helper function to walk down the tree.
  int walk(T *n, int &v, int x, int& idx) {
      int s = n->c[0] ? n->c[0]->size : 0;
      v = n->val < x; // 0 -> left, 1 -> right
    if (v) {
      idx += s + 1;
    }
    
      return s;
  }
 
  int walkInd(T *n, int &v, int &pos) {
    //n->push_down(); 
    int s = n->c[0] ? n->c[0]->size : 0;
    (v = s < pos) && (pos -= s + 1); 
    return s; 
  }
  // Insert node n to position pos.
  void insert(T* newNode) {
    if (!root) {
        root = newNode;
        return;
    }
    T* node = root;
    T* parent = nullptr;
    while (node) {
        parent = node;
        if (newNode->val >= node->val) { // Duplicates go to the right
            node = node->c[1];
        } else {
            node = node->c[0];
        }
    }
    if (newNode->val >= parent->val) {
        parent->c[1] = newNode;
    } else {
        parent->c[0] = newNode;
    }
    newNode->f = parent;
    splay(newNode); // Splay the newly inserted node
  }
 
  // Find node with value x :)
  int findVal(int x, bool sp = true) {
    if (!root) return -1; // If the tree is empty, return -1.
 
    T *node = root;
    T *lastFound = nullptr; 
    int idx = 0; 
    int lastFoundIdx = 0; 
 
    while (node) {
        if (node->c[0]) {
            idx += node->c[0]->size; // Add the size of the left subtree.
        }
        
        if (x < node->val) {
            // Need to subtract because we might have added this subtree size prematurely.
            idx -= node->c[0] ? node->c[0]->size : 0;
            node = node->c[0];
        } else if (x > node->val) {
            // Move to the right, adding 1 for the current node.
            idx += 1;
            node = node->c[1];
        } else {
            lastFound = node; 
            lastFoundIdx = idx + 1; 
            node = node->c[0]; 
            if (!node) break; 
            idx -= node->size;
        }
    }
 
    if (lastFound && sp) splay(lastFound); // Splay the last found node (which is the first occurrence).
 
    return lastFound ? lastFoundIdx : -1; // Return the index of the first occurrence or -1 if not found.
  }
 
  T* findInd(int pos, bool sp = true) {
    if (!root || pos < 1 || pos > root->size) return nullptr; // Bounds check
 
    T* n = root;
    while (n) {
        int leftSize = n->c[0] ? n->c[0]->size : 0;
        int currentPos = leftSize + 1;
 
        if (pos < currentPos) {
            n = n->c[0];
        } else if (pos > currentPos) {
            pos -= currentPos; // Adjust 'pos' as we descend to the right
            n = n->c[1];
        } else {
            if (sp) splay(n);
            return n;
        }
    }
   
    return nullptr;
  }
  // Find the range [posl, posr) on the splay tree.
  T *find_range(int posl, int posr) {
    T *r, *l;
    if(posl - 1 < 0) {
      r = findInd(posr), l = findInd(posl, false);
    } else {
      r = findInd(posr), l = findInd(posl - 1, false);
    }
    splay(l, r);
    if (l && l->c[1])  {
      l->c[1]->push_down();
      return l->c[1];
    }
    return nullptr;
  }
  // Insert nn of size nn_size to position pos.
  void insert_range(T **nn, int nn_size, int pos) {
    T *r = findInd(pos), *l = findInd(pos - 1, false), *c = l;
    splay(l, r);
    for (int i = 0; i < nn_size; ++i) c->c[1] = nn[i], nn[i]->f = c, c = nn[i];
    for (int i = nn_size - 1; i >= 0; --i) nn[i]->update();
    l->update(), r->update(), splay(nn[nn_size - 1]);
  }
  // Helper function to dealloc a subtree.
  void dealloc(T *n) {
    if (!n) return;
    dealloc(n->c[0]);
    dealloc(n->c[1]);
    pool.dealloc(n);
  }
  // Remove from position [posl, posr).
  void erase_range(int posl, int posr) {
   if (posl >= posr || !root) return;
 
    // Special handling when the first element is to be removed.
    if (posl == 0) {
        // Find the node right after the end of the range to be removed.
        T *r = findInd(posr); 
        if (r && r->c[0]) {
            // Disconnect and deallocate the range.
            dealloc(r->c[0]);
            r->c[0] = nullptr;
            r->update();
        }
        return;
    }
 
    T *l = findInd(posl - 1); // Splay the node just before the range.
    T *r = findInd(posr, false); // Find but do not splay the node just after the range.
 
    if (r) splay(r, l);
 
    // Remove the subtree between l and r.
    if (l && r && l->c[1] == r) {
        if (r->c[0]) {
            dealloc(r->c[0]); // Deallocate the range to be removed.
            r->c[0] = nullptr;
            r->update();
        }
        l->update();
    }
  }
  void remove(int value) {
    int pos = findVal(value, false); // Find the node but don't splay it yet
    if (pos == -1) return; // Value not found
 
    // Now, splay the node to bring it to the root for removal
    T* node = findInd(pos, true);
    if (!node || node->val != value) return; 
    if (!node->c[0]) {
        root = node->c[1];
    } else {
        T* maxLeft = node->c[0];
        while (maxLeft->c[1]) maxLeft = maxLeft->c[1];
        splay(maxLeft); // Brings maxLeft to the root
        maxLeft->c[1] = node->c[1];
        if (node->c[1]) node->c[1]->f = maxLeft;
        root = maxLeft;
    }
    if (root) root->f = nullptr;
    pool.dealloc(node);
  }
};
 
}  // namespace splay
 
struct node : splay::node<node> {
    node(int x = -1) : splay::node<node>() { val = x; }
};
const int MAXN = 3e6+3;
splay::tree<node, MAXN, allocator::stack<node, MAXN + 2>> t;
 
using namespace std;
 
int main() {
    cin.tie(0);
    cin.sync_with_stdio(0);
 
    int fnum, snum;
    int count = 0;
 
    while(true) {
        //cout << "Getting first num\n"; 
        cin >> fnum; // input the first number
        //cout << fnum << "\n";
 
        if(fnum == -1) break;
 
        cin >> snum;
 
        switch(fnum) {
            case 1: { // insert value into tree
                t.insert(t.new_node(node(snum)));
                count += 1;
                break;
            }
            case 2: { // remove from list
                int temp = t.findVal(snum);
                if(temp != -1) {
                  t.remove(snum);
                  count -= 1;
                } 
                break;
            }
            case 3:  { // print n's index after sorted in ascending order
                int ind = t.findVal(snum);
                cout << ind << "\n";
                break;
            }
            default: { // print i's node value after sorted in ascending order
                int ind = snum;
                if (ind <= 0 || ind > count) {
                  cout  << -1 << "\n";
                } else {
                  node *r = t.findInd(snum);
                  cout << r->val << "\n";
                }
            }
        }  
    }
    return 0;
}
 