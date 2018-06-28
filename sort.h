//
//  sort.h
//  test
//
//  Created by F on 14/12/13.
//  Copyright (c) 2014年 F. All rights reserved.
//

#ifndef __test__sort__
#define __test__sort__

#include <stdio.h>
template<class T>
void sort_insert(T a[],int size){
    T temp;
    int j;
    for (int i=1; i<size; i++) {
        temp=a[i];
        for (j=i-1; j>=0 && temp<a[j]; j--) {
                a[j+1]=a[j];
        }
        a[j+1]=temp;
    }
}


template <class T>
void sort_shell(T a[],int size) {
    T temp;
    int j;
    for (int step=size/2; step>0; step/=2) {
        for (int i=step; i<size; i++) {
            temp=a[i];
            for (j=i-step; j>=0 && temp<a[j]; j-=step) {
                a[j+step]=a[j];
            }
            a[j+step]=temp;
        }
    }
}


template <class T>
void sort_select(T a[],int size) {
    T min;
    int k;
    for (int i=0; i<size-1; i++) {
        k=i;
        for (int j=i+1; j<size; j++) {
            if (a[j]<a[k]) {
                k=j;
            }
        }
        min=a[k];
        a[k]=a[i];
        a[i]=min;
    }
}


template <class T>
void percolateDown(T a[],int hole,int size) {
    int child;
    T temp=a[hole];
    for (; hole*2+1<size; hole=child) {
        child=hole*2+1;
        if (child!=size-1 && a[child+1]>a[child]) {
            child++;
        }
        if (a[child]>temp) {
            a[hole]=a[child];
        }
        else {
            break;
        }
    }
    a[hole]=temp;
}
template <class T>
void sort_heap(T a[],int size) {
    for (int i=size/2-1; i>=0; i--) {
        percolateDown(a, i, size);
    }
    T temp;
    for (int i=size-1; i>0; i--) {
        temp=a[0];
        a[0]=a[i];
        a[i]=temp;
        percolateDown(a, 0, i);
    }
}

template <class T>
void sort_bubble(T a[],int size) {
    T temp;
    bool finished=0;
    for (int i=size;i>0 ; i--) {
        finished=1;
        for (int j=0; j<i-1; j++) {
            if (a[j]>a[j+1]) {
                temp=a[j+1];
                a[j+1]=a[j];
                a[j]=temp;
                finished=0;
            }
        }
        if(finished==1){
            break;
        }
    }
}




template <class T>
int  divide(T a[],int low,int high) {
    T k=a[low];
    while (low!=high) {
        while (low<high && a[high]>=k) {
            high--;
        }
        if(low<high){
            a[low]=a[high];
            low++;
        }
        while (low<high && a[low]<=k) {
            low++;
        }
        if (low<high) {
            a[high]=a[low];
            high--;
        }
    }
    a[low]=k;
    return low;
}
template <class T>
void sort_quick(T a[],int low,int high) {
    if (low>=high) {
        return;
    }
    int mid=divide(a,low,high);
    sort_quick(a, low,mid-1);
    sort_quick(a, mid+1, high);
}
template <class T>
void sort_quick(T a[],int size) {
    sort_quick(a,0,size-1);
}


template <class T>
void merge(T a[],int left,int mid,int right) {
    int i=left;
    int j=mid;
    int k=0;
    T *temp=new T[right-left+1];
    while (i<mid && j<=right) {
        if (a[i]<a[j]) {
            temp[k++]=a[i++];
        }
        else{
            temp[k++]=a[j++];
        }
    }
    while (i<mid) {
        temp[k++]=a[i++];
    }
    while (j<=right) {
        temp[k++]=a[j++];
    }
    for (int i=0; i<right-left+1; i++) {
        a[left+i]=temp[i];
    }
    delete temp;
}
template <class T>
void sort_merge(T a[],int left,int right) {
    if (left==right) {
        return;
    }
    int mid=(left+right)/2;
    sort_merge(a, left, mid);
    sort_merge(a, mid+1, right);
    merge(a, left, mid+1, right);
}
template <class T>
void sort_merge(T a[],int size) {
    sort_merge(a, 0, size-1);
}
#endif /* defined(__test__sort__) */
