#include <stdio.h>
#include <cstddef>
#include <iostream>
using namespace std;

const string EMPTY=""; // for printing
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

    SplayTree* FindMax(SplayTree* root) {
        SplayTree* x = NULL;

        while (root != NULL) {
        x = root;
        root = root->c[1];
        }

        return x;
    }

    SplayTree* Delete(int v) {
        SplayTree* x = FindNode(v);
        x->Splay();

        if (x->v != v) {
        return x;
        }

        SplayTree* leftSubTree = x->c[0];
        SplayTree* rightSubTree = x->c[1];

        x->c[0] = x->c[1] = NULL;

        if (leftSubTree != NULL)
        leftSubTree->p = NULL;
        if (rightSubTree != NULL)
        rightSubTree->p = NULL;

        if (leftSubTree != NULL) {
        SplayTree* maxNode = FindMax(leftSubTree);

        maxNode->c[1] = rightSubTree;
        maxNode->UpdateSize();

        if (rightSubTree != NULL)
            rightSubTree->p = maxNode;

        maxNode->Splay();
        return maxNode;
        }

        return rightSubTree;
    }

    pair<SplayTree*, SplayTree*> SplitByValue(int v) {
        SplayTree* x = FindNode(v);
        x->Splay();

        SplayTree *leftTree, *rightTree;

        if (x->v <= v) {
        // Destroy right edge

        leftTree = x;
        rightTree = x->c[1];

        if (x->c[1] != NULL)
            x->c[1]->Destroy();
        }

        else {
        // Destroy left edge
        leftTree = x->c[0];
        rightTree = x;

        if (x->c[0] != NULL)
            x->c[0]->Destroy();
        }

        leftTree->UpdateSize();
        rightTree->UpdateSize();
        return make_pair(leftTree, rightTree);
    }

    void Print(string prefix=EMPTY, bool isRight=false, bool isRoot=true) {
        if (c[1])
        c[1]->Print(prefix + (!isRight && !isRoot? "|  ": "   "), true, false);

        cout << prefix;
        cout << (isRoot? "---" : (isRight? ".--" : "`--"));
        cout << v << "(" << size << ")" << endl;

        if (c[0])
        c[0]->Print(prefix + (isRight? "|  ": "   "), false, false);
    }
};

int main() {
    SplayTree *root = new SplayTree(10);
    cout << "\n";

    root = root->Insert(30);
    root = root->Insert(50);
    root = root->Insert(20);
    root = root->Insert(60);
    root = root->Insert(40);
    root->Print();
}