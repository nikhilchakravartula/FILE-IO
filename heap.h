#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include<limits.h>
#include<stdio.h>
#include<stdbool.h>
typedef struct
{
    unsigned long long data;
     char str[200];
}heap_node;


unsigned long long cursize=0,maxsize;

unsigned long long left(unsigned long long i)
{
    return 2*i+1;
}
unsigned long long right(unsigned long long i)
{
    return 2*i+2;
}
unsigned long long parent(unsigned long long i)
{
return (i-1)/2;
}

void swap(heap_node* arr,unsigned long long i,unsigned long long j)
{
    heap_node t=arr[i];
    arr[i]=arr[j];
    arr[j]=t;
}

void heapify(heap_node arr[],unsigned long long i)
{
    unsigned long long r=right(i),l=left(i),smallest=i;

    if(l<=cursize && arr[l].data<arr[smallest].data)
        smallest=l;
    if(r<=cursize && arr[smallest].data>arr[r].data)
        smallest=r;
    if(smallest!=i){
    swap(arr,i,smallest);
    heapify(arr,smallest);
    }

}
void heap_initialise( heap_node arr[],unsigned long long size)
{
    cursize=size-1;
    for(unsigned long long i=size/2;i>0;i--)
    {
        heapify(arr,i);
    }
     heapify(arr,0);
}

void heap_insert(heap_node* arr,heap_node* node)
{

    arr[cursize]=(*node);
    cursize++;

unsigned long long temp=cursize-1;
    while(temp!=0 && ( arr[temp].data < arr[parent(temp)].data) )
    {
        swap(arr,temp,parent(temp));
        temp=parent(temp);
    }



}

bool heap_empty()
{
    return INT_MAX==cursize;
}
heap_node pop_min(heap_node* arr)
{

    if(cursize==0)
    {
        cursize-=1;
        return arr[0];

    }
    else
    {
        heap_node t=arr[0];
        arr[0]=arr[cursize];
        cursize-=1;
        heapify(arr,0);
        return t;
    }


}


#endif // HEAP_H_INCLUDED
