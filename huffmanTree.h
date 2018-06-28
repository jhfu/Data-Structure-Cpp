//
//  huffmanTree.h
//  test
//
//  Created by F on 14/11/11.
//  Copyright (c) 2014年 F. All rights reserved.
//

#ifndef __test__huffmanTree__
#define __test__huffmanTree__

#include <stdio.h>
#include <string>
using namespace std;

template <class T>
class huffmanTree {
    struct node{
        T data;
        int weight=0;
        int parent=0;
        int left=0;
        int right=0;
    };
    node *elem;
    int length;
    
public:
    struct hfCode{
        T data;
        string code="";
    };
    huffmanTree(const T *d,const int *w,int size);
    void getCode(hfCode result[]);
    ~huffmanTree(){delete []elem;}
};


template <class T>
huffmanTree<T>::huffmanTree(const T *d,const int *w,int size) {
    length=size*2;
    elem=new node[length];
    for (int i=0; i<size; i++) {
        elem[size+i].data=d[i];
        elem[size+i].weight=w[i];
    }
    
    int min1,min2;
    int w1,w2;
    for (int i=size; i>0; i--) {
        w1=w2=999999;
        min1=min2=0;
        for (int j=i; j<length; j++) {
            if (elem[j].parent==0) {
                if (elem[j].weight<w1) {
                    min2=min1;
                    w2=w1;
                    min1=j;
                    w1=elem[j].weight;
                }
                else if (elem[j].weight<w2){
                    min2=j;
                    w2=elem[j].weight;
                }
            }
        }
        elem[i-1].weight=w1+w2;
        elem[i-1].left=min1;
        elem[i-1].right=min2;
        elem[min1].parent=i-1;
        elem[min2].parent=i-1;
    }
    {
    for (int i=1; i<length; i++) {
        cout<<elem[i].data<<'\t';
    }
    cout<<endl;
    for (int i=1; i<length; i++) {
        cout<<elem[i].weight<<'\t';
    }
    cout<<endl;
    for (int i=1; i<length; i++) {
        cout<<elem[i].parent<<'\t';
    }
    cout<<endl;
    for (int i=1; i<length; i++) {
        cout<<elem[i].left<<'\t';
    }
    cout<<endl;
    for (int i=1; i<length; i++) {
        cout<<elem[i].right<<'\t';
    }
        cout<<endl;
    }
}

template <class T>
void huffmanTree<T>::getCode(huffmanTree<T>::hfCode result[]) {
    int size=length/2;
    for (int i=0; i<size; i++) {
        result[i].data=elem[size+i].data;
        int p=elem[size+i].parent;
        int j=size+i;
        while (p) {
            if (elem[p].left==j) {
                result[i].code+='0';
            }
            else if (elem[p].right==j){
                result[i].code+='1';
            }
            j=p;
            p=elem[j].parent;
        }
    }
}
#endif /* defined(__test__huffmanTree__) */
