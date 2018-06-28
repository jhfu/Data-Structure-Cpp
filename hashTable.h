//
//  hashTable.h
//  test
//
//  Created by F on 14/12/10.
//  Copyright (c) 2014年 F. All rights reserved.
//

#ifndef __test__hashTable__
#define __test__hashTable__

#include <stdio.h>

template <class T>
class hashTable {

public:
    virtual bool find(const T &x)const =0;
    virtual bool insert(const T &x)=0;
    virtual bool remove(const T &x)=0;
//protected:
//    int (*key)(const T &x);
//    static int defaultKey(const int &k){return k;}
//    
};

/****************close hash table*********************/

template <class T>
class closeHashTable:public hashTable<T> {
    struct node{
        T data;
        int state=0;   //0-empty;   1-active;   2-deleted;
    };
    node *array;
    int size;
    
public:
    closeHashTable(int length=99,int (*f)(const T &x)=defaultKey);
    ~closeHashTable(){delete []array;}
    bool find(const T &x)const;
    bool insert(const T &x);
    bool remove(const T &x);
    void rehash();
protected:
    int (*key)(const T &x);
    static int defaultKey(const int &k){return k;}
    
};

template <class T>
closeHashTable<T>::closeHashTable(int length,int (*f)(const T &x)) {
    size=length;
    array=new node[size];
    key=f;
}

template <class T>
bool closeHashTable<T>::insert(const T &x) {
    int initPos=key(x)%size;
    int pos=initPos;
    do {
        if (array[pos].state!=1) {
            array[pos].data=x;
            array[pos].state=1;
            return 1;
        }
        if (array[pos].state==1&&array[pos].data==x) {
            return 0;
        }
        pos++;
        pos%=size;
    } while (pos!=initPos);
    return 0;
}


template <class T>
bool closeHashTable<T>::find(const T &x)const {
    int initPos=key(x)%size;
    int pos=initPos;
    do {
        if (array[pos].state==0) {
            return 0;
        }
        else if(array[pos].state==1&&array[pos].data==x){
            return 1;
        }
        pos++;
        pos%=size;
    } while (pos!=initPos);
    return 0;
}

template <class T>
bool closeHashTable<T>::remove(const T &x) {
    int initPos=key(x)%size;
    int pos=initPos;
    do {
        if (array[pos].state==0) {
            return 0;
        }
        else if (array[pos].data==x&&array[pos].state==1) {
            array[pos].state=2;
            return 1;
        }
        pos++;
        pos%=size;
    } while (pos!=initPos);
    return 0;
}

template <class T>
void closeHashTable<T>::rehash() {
    node *temp=array;
    array=new node[size];
    for (int i=0; i<size; i++) {
        if (temp[i].state==1) {
            insert(temp[i].data);
        }
    }
    delete []temp;
}

/****************open hash table*********************/
template <class T>
class openHashTable:public hashTable<T> {
    struct node{
        T data;
        node *next=NULL;
        node(const T &x):data(x){}
        node(){}
    };
    int size;
    node **array;
    
public:
    openHashTable(int length=99,int (*f)(const T &x)=defaultKey);
    ~openHashTable();
    bool find(const T &x)const;
    bool insert(const T &x);
    bool remove(const T &x);
protected:
    int (*key)(const T &x);
    static int defaultKey(const int &k){return k;}
};

template <class T>
openHashTable<T>::openHashTable (int length,int(*f)(const T &x)) {
    size=length;
    array=new node *[size];
    key=f;
    for (int i=0; i<size; i++) {
        array[i]=new node();
    }
}
template <class T>
openHashTable<T>::~openHashTable() {
    node *p,*q;
    for (int i=0; i<size; i++) {
        p=array[i];
        while (p!=NULL) {
            q=p->next;
            delete p;
            p=q;
        }
    }
    delete [] array;
}
template <class T>
bool openHashTable<T>::insert(const T &x) {
    node *p=array[key(x)%size];//head
    while (p->next!=NULL) {
        if (p->next->data==x) {
            return 0;
        }
        p=p->next;
    }
    p->next=new node(x);
    return 1;
}
template <class T>
bool openHashTable<T>::find(const T &x)const {
    node *p=array[key(x)%size];
    while (p->next!=NULL) {
        if (p->next->data==x) {
            return 1;
        }
        p=p->next;
    }
    return 0;
}
template <class T>
bool openHashTable<T>::remove(const T &x) {
    node *p=array[key(x)%size];
    while (p->next!=NULL) {
        if (p->next->data==x) {
            node *q=p->next;
            p->next=q->next;
            delete q;
            return 1;
        }
        p=p->next;
    }
    return 0;
}



#endif /* defined(__test__hashTable__) */
