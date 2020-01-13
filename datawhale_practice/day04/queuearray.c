#include<stdio.h>
#include<stdlib.h>

void enqueue(int queue[],int element,int& rear,int arraySize)
{
    if(rear == arraySize)
    {
        printf("OverFlow\n");
    }
    else
    {
        queue[rear]=element;
        rear++;
    }
}
void dequeue(int queue[],int& front,int rear)
{
    if(front == rear)
    {
        printf("Queue if full\n");
    }
    else
    {
        queue[front]==0;
        front++;
    }       
}
int Front(int queue[],int front)
{
    return queue[front];
}
int size(int queue,int front,int rear)
{
    return (rear-front);
}
int isEmpty(int front,int rear)
{
    return (front==rear);
}

