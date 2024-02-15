#include <stdio.h>
#include <cstddef>
#include <iostream>
using namespace std;

struct SplayTree {
    int v; // Value of node
    int size; // Subtree size
    SplayTree *c[2]; // Left child -> [0], right child -> [1]
    SplayTree *p; // Parent of node

    //constructor
    SplayTree(int _v) {
        v = _v;
        c[0] = c[1] = p = NULL;
    }

    int GetSize(SplayTree *x) {
        if (x == NULL) { return 0; }
        return x->size;
    }

    void UpdateSize() {
        size = 1 + GetSize(c[0]) + GetSize(c[1]);
    }

    void Rotate() {
        SplayTree *gp = p->p;

        bool isLeft = (p->c[0] == this); // isLeft? rightRotate else leftRotate
        p->c[!isLeft] = c[isLeft]; // swap children

        if (c[isLeft] != NULL) c[isLeft]->p = p;
        
        c[isLeft] = p;
        p->p = this;

        if (gp != NULL) {
            bool leftpar = (gp->c[0] == p);
            gp->c[!leftpar] = this;
        }

        p->UpdateSize();
        UpdateSize();

        p = gp;
    }

    void Splay() {
        while (p != NULL) {
            if (p->p != NULL) {
                bool leftpar = p->p->c[0] == p;
                bool isLeft = p->c[0] == this;

                if (leftpar == isLeft) p->Rotate();
                else Rotate();
            }

            Rotate();
        }
    }

    void Destroy() {
        SplayTree* par = p;
        if (par != NULL) {
        bool isRight = (par->c[1] == this);
        par->c[isRight] = NULL;
        }
        p = NULL;
    }

    SplayTree* FindNode(int v) {
        SplayTree *x = this;
        SplayTree *xx = NULL;
        while (x != NULL) {
        xx = x;
        if (x->v > v) { x = x->c[0]; }
        else if (x->v < v) { x = x->c[1]; }
        else return x;
        }
        return xx;
    }

    SplayTree* Search(int v) {
        SplayTree* x = FindNode(v);
        x->Splay();
        return x;
    }

    SplayTree* Insert(int v) {
        SplayTree* par = FindNode(v);
        if (par->v == v) {
            par->Splay();
            return par;
        }
        SplayTree* x = new SplayTree(v);
        if (par->v <= v) { par->c[1] = x; }
        else if (par->v > v) { par->c[0] = x; }
        
        par->UpdateSize();
        x->p = par;
        x->Splay();
        return x;
    }
};