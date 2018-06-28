

#include <iostream>
using namespace std;

template <class T>
class stack {
    
public:
    virtual bool isEmpty()const =0;
    virtual void push(const T &x)=0;
    virtual T pop()=0;
    virtual T read()const =0;
    virtual ~stack(){};
};


template <class T>
class linkStack:public stack<T> {
    struct node{
        T data;
        node *next;
        node(const T &x,node *n=NULL):data(x),next(n){};
        node():next(NULL){};
        ~node(){};
    };
    node *top;
public:
    linkStack(){    top=NULL;   }
    ~linkStack();
    bool isEmpty()const{    return top==NULL;   }
    void push(const T &x);
    T pop();
    T read()const;
};




template <class T>
linkStack<T>::~linkStack(){
    node *temp;
    while (top!=NULL) {
        temp=top;
        top=top->next;
        delete temp;
    }
    
}

template <class T>
void linkStack<T>:: push(const T &x) {
    node *temp;
    temp=new node(x,top);
    top=temp;
}

template <class T>
T linkStack<T>:: pop() {
    node *temp=top;
    T data=top->data;
    top=top->next;
    delete temp;
    return data;
}

template <class T>
T linkStack<T>::read()const {
    return top->data;
}


