//
//  binarySearchTree.h
//  test
//
//  Created by F on 14/11/18.
//  Copyright (c) 2014年 F. All rights reserved.
//

#ifndef __test__binarySearchTree__
#define __test__binarySearchTree__

#include <stdio.h>

template <class T>
class binarySearchTree {
    struct node{
        T data;
        node *left;
        node *right;
        node(T x,node *l=NULL,node *r=NULL):data(x),left(l),right(r){}
    };
    node *root;
    void insert(const T &x,node * &t);
    void remove(const T &x,node * &t);
    bool find(const T &x,node *t)const;
    void makeEmpty(node *&t);
    
public:
    binarySearchTree(node *t=NULL):root(t){}
    ~binarySearchTree();
    bool find(const T &x)const;
    void insert(const T &x);
    void remove(const T &x);
};

template <class T>
bool binarySearchTree<T>::find(const T &x)const {
    return find(x,root);
}
template <class T>
bool binarySearchTree<T>::find(const T &x,node *t)const {
    if (t==NULL) {
        return 0;
    }
    else if(t->data>x){
        return find(x,t->left);
    }
    else if(t->data<x){
        return find(x,t->right);
    }
    else{
        return 1;
    }
    
}

template <class T>
void binarySearchTree<T>::insert(const T &x) {
    insert(x, root);
}

template <class T>
void binarySearchTree<T>::insert(const T &x, binarySearchTree::node *&t) {
    if (t==NULL) {
        t=new node(x);
    }
    else if(x<t->data){
        insert(x, t->left);
    }
    else if(x>t->data){
        insert(x, t->right);
    }
}

template <class T>
void binarySearchTree<T>::remove(const T &x) {
    remove(x, root);
}

template <class T>
void binarySearchTree<T>::remove(const T &x, binarySearchTree::node *&t) {
    if (t==NULL) {
        return;
    }
    else if(x<t->data){
        remove(x, t->left);
    }
    else if (x>t->data){
        remove(x, t->right);
    }
    else{
        if (t->left!=NULL&&t->right!=NULL) {
            node *temp=t->right;
            while (temp->left!=NULL) {
                temp=temp->left;
            }
            t->data=temp->data;
            remove(t->data,t->right);
        }
        else{
            node *old=t;
            if (old->left==NULL) {
                t=t->right;
            }
            else{
                t=t->left;
            }
            delete old;
        }
    }
}
template <class T>
void binarySearchTree<T>::makeEmpty(binarySearchTree::node *&t) {
    if (t->left!=NULL) {
        makeEmpty(t->left);
    }
    if (t->right!=NULL) {
        makeEmpty(t->right);
    }
    delete t;
}

template <class T>
binarySearchTree<T>::~binarySearchTree () {
    makeEmpty(root);
}



#endif /* defined(__test__binarySearchTree__) */
