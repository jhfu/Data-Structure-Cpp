//
//  binaryTree.h
//  test
//
//  Created by F on 14/10/30.
//  Copyright (c) 2014年 F. All rights reserved.
//

#ifndef __test__binaryTree__
#define __test__binaryTree__

#include <iostream>
#include "linkQueue.h"
#include "linkStack.h"
using namespace std;

template <class T>
class binaryTree {
    struct node{
        T data;
        node *left;
        node *right;
        node(const T &x,node *l=NULL,node *r=NULL):data(x),left(l),right(r){};
        node():left(NULL),right(NULL){};
        ~node(){};
    };
    node *root;
    struct stNode{
        node *Node;
        int popTimes;
        stNode(node *N=NULL):Node(N),popTimes(0){};
    };
    
    void clear(node *p){
        if (p->left!=NULL) {
            clear(p->left);
        }
        if (p->right!=NULL) {
            clear(p->right);
        }
        delete p;
    }
    int size(node *p)const{
        if (p==NULL) {
            return 0;
        }
        else{
            return 1+size(p->left)+size(p->right);
        }
        
    }
    int height(node *p)const{
        if (p==NULL) {
            return 0;
        }
        else{
            int lt=height(p->left);
            int rt=height(p->right);
            if (lt>rt) {
                return 1+lt;
            }
            else{
                return 1+rt;
            }
        }
    }
    void preOrder(node *p)const{
        if (p!=NULL) {
            cout<<p->data<<' ';
            preOrder(p->left);
            preOrder(p->right);
        }
        
    }
    void midOrder(node *p)const{
        if (p!=NULL) {
            midOrder(p->left);
            cout<<p->data<<' ';
            midOrder(p->right);
        }
    }
    void postOrder(node *p)const{
        if (p!=NULL) {
            postOrder(p->left);
            postOrder(p->right);
            cout<<p->data<<' ';
        }
    }
    
public:
    binaryTree():root(NULL){};
    binaryTree(const T &x){
        root=new node(x);
    }
    binaryTree(const node *p):root(p){};
    ~binaryTree(){clear();}
    bool isEmpty()const{return root==NULL;}
    int size()const{return size(root);}
    int height()const{return height(root);}
    
    T getRoot()const{return root->data;}
    T getLeft()const{return root->left->data;}
    T getRight()const{return root->right->data;}
    
    void makeTree(const T &x,binaryTree &lt,binaryTree &rt){
        root=new node(x,lt.root,rt.root);
        lt=NULL;
        rt=NULL;
    }
    
    void deleteLeftTree(){
        binaryTree temp=root->left;
        root->left=NULL;
        temp.clear();
    }
    
    void deleteRightTree(){
        binaryTree temp=root->right;
        root->right=NULL;
        temp.clear();
    }
    
    void clear(){
        if (root!=NULL) {
            clear(root);
        }
        root=NULL;
    }
    
    void preOrder()const{
        if (root!=NULL) {
            cout<<"DLR: ";
            preOrder(root);
            cout<<endl;
        }
    }
    void preOrderNonRecursion()const{
        linkStack<node *> s;
        node *temp;
        cout<<"DLR without recursion: ";
        s.push(root);
        while (!s.isEmpty()) {
            temp=s.pop();
            cout<<temp->data<<' ';
            if (temp->right!=NULL) {
                s.push(temp->right);
            }
            if (temp->left!=NULL) {
                s.push(temp->left);
            }
        }
        
    }
    void midOrder()const{
        if (root!=NULL) {
            cout<<"LDR: ";
            midOrder(root);
            cout<<endl;
        }
    }
    void midOrderNonRecursion()const{
        linkStack<stNode> s;
        stNode current(root);
        cout<<"LDR without recursion: ";
        s.push(current);
        while (!s.isEmpty()) {
            current=s.pop();
            current.popTimes++;
            if (current.popTimes==1) {
                s.push(current);
                if(current.Node->left!=NULL){
                    s.push(stNode(current.Node->left));
                }
            }
            else{
                cout<<current.Node->data<<' ';
                if (current.Node->right!=NULL) {
                    s.push(stNode(current.Node->right));
                }
            }
        }
        
    }
    void postOrder()const{
        if (root!=NULL) {
            cout<<"LRD: ";
            postOrder(root);
            cout<<endl;
        }
    }
//    void postOrderNonRecursion()const{
//        linkStack<stNode> s;
//        stNode current(root);
//        s.push(current);
//        cout<<"LRD without recursion: ";
//        while (!s.isEmpty()) {
//            current=s.pop();
//            current.popTimes++;
//            if (current.popTimes==1) {
//                s.push(current);
//                if (current.Node->left!=NULL) {
//                    s.push(stNode(current.Node->left));
//                }
//            }
//            else if(current.popTimes==2){
//                s.push(current);
//                if (current.Node->right!=NULL) {
//                    s.push(stNode(current.Node->right));
//                }
//            }
//
//            else{
//                cout<<current.Node->data<<' ';
//            }
//        }
//    }

    void postOrderNonRecursion()const{
        linkStack<stNode> s;
        stNode current(root);
        s.push(current);
        cout<<"LRD without recursion: ";
        while (!s.isEmpty()) {
            current=s.pop();
            current.popTimes++;
            if (current.popTimes==1) {
                s.push(current);
                if (current.Node->right!=NULL) {
                    s.push(stNode(current.Node->right));
                }
                if (current.Node->left!=NULL) {
                    s.push(stNode(current.Node->left));
                }
            }
            else if(current.popTimes==2){
                s.push(current);
                cout<<current.Node->data<<' ';
            }
        }
    }

    void createTree(T flag){
        linkQueue<node *> nodeQueue;
        cout<<"Please input root node: ";
        T rootData,leftData,rightData;
        cin>>rootData;
        root=new node(rootData);
        nodeQueue.enQueue(root);
        while (!nodeQueue.isEmpty()) {
            node *temp=nodeQueue.deQueue();
            cout<<"Please input "<<temp->data<<"`s two sons("<<flag<<"represents empty node): ";
            cin>>leftData>>rightData;
            if (leftData!=flag) {
                nodeQueue.enQueue(temp->left=new node(leftData));
            }
            if (rightData!=flag) {
                nodeQueue.enQueue(temp->right=new node(rightData));
            }
        }
        cout<<"Create completed!"<<endl;
    }    
    
};

#endif /* defined(__test__binaryTree__) */
