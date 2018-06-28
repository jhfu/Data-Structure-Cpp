//
//  linkQueue.h
//  test
//
//  Created by F on 14/10/31.
//  Copyright (c) 2014年 F. All rights reserved.
//

#ifndef __test__linkQueue__
#define __test__linkQueue__

#include <iostream>
#include <iomanip>
using namespace std;
/************Class linkQueue Definition and Implementation ******************/

template <class T>
class queue {
    
public:
    virtual bool isEmpty()const=0;
    virtual void enQueue(const T &x)=0;
    virtual T deQueue()=0;
    virtual T getHead() const=0;
    virtual ~queue(){}
};

template <class T>
class linkQueue:public queue<T> {
    struct node{
        T data;
        node *next;
        node(const T &x,node *n=NULL):data(x),next(n){}
        node():next(NULL){}
        ~node(){}
    };
    node *head,*rear;
    
public:
    linkQueue(){head=rear=NULL;}
    ~linkQueue();
    bool isEmpty()const{return head==NULL;}
    void enQueue(const T &x);
    T deQueue();
    T getHead()const{return head->data;}
};






template <class T>
linkQueue<T>::~linkQueue() {
    node *temp;
    while (head!=NULL) {
        temp=head;
        head=head->next;
        delete temp;
    }
}

template <class T>
void linkQueue<T>::enQueue(const T &x) {
    if (head==NULL) {
        head=new node(x);
        rear=head;
    }
    else{
        node *temp=new node(x);
        rear->next=temp;
        rear=temp;
    }
}

template <class T>
T linkQueue<T>::deQueue() {
    T value=head->data;
    node *temp=head;
    head=head->next;
    if (head==NULL) {
        rear=NULL;
    }
    delete temp;
    return value;
}
#endif /* defined(__test__linkQueue__) */
