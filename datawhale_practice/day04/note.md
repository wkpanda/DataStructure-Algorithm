# Queue Data Structure

A Queue is a linear structure which follows a particular order in which the operations are performed. The order is First In First Out (FIFO). A good example of a queue is any queue of consumers for a resource where the consumer that came first is served first. The difference between stacks and queues is in removing. In a stack we remove the item the most recently added; in a queue, we remove the item the least recently added.

![queue](https://media.geeksforgeeks.org/wp-content/cdn-uploads/gq/2014/02/Queue.png)

## Variables used

- queue[]: Array in which queue is simulated
- arraySize: Maximum number of elements that can be stored in a 
- front: Points at the index where the next deletion will be performed
- rear: Points at the index where the next insertion will be performed
## Functions supported
### Enqueue
If the queue if not full, this funcion adds element to the end of the queue,else prints "OverFlow".
```c
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
```
### Dequeue
If the queue is not empty, this function removes the element from the front of the queue, else it prints "queue is full".
```c
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
```

### Front
This function returns the front element of the queue.
```c
int Front(int queue[],int front)
{
    return queue[front];
}
```

### Size
This function returns the size of a queue or the number of elements in a queue.
```c
int size(int front, int rear) {
    return (rear - front);
}
```

### IsEmpty
If a queue is empty, this function returns 'true', else it returns 'false'.
```c
bool isEmpty(int front, int rear) {
    return (front == rear);
}
```

![queue](https://he-s3.s3.amazonaws.com/media/uploads/cf1e1c1.png)

## Circular queues

A circular queue is an improvement over the standard queue structure. In a standard queue, when an element is deleted, the vacant space is not reutilized. However, in a circular queue, vacant spaces are reutilized.

While inserting elements, when you reach the end of an array and you need to insert another element, you must insert that element at the beginning (given that the first element has been deleted and the space is vacant).

![circularqueues](https://he-s3.s3.amazonaws.com/media/uploads/51fe410.png)

### Functions supports
### Enqueue
```c
void enqueue(int queue[], int element, int& rear, int arraySize, int& count) {
    if(count == arraySize)            // Queue is full
            printf(“OverFlow\n”);
    else{
        queue[rear] = element;
        rear = (rear + 1)%arraySize;
        count = count + 1;
    }
}
```
### Dequeue
```c
void dequeue(int queue[], int& front, int rear, int& count) {
    if(count == 0)            // Queue is empty
        printf(“UnderFlow\n”);
    else {
        queue[front] = 0;        // Delete the front element
        front = (front + 1)%arraySize;
        count = count - 1;
    }
}
```

### Front
```c
int Front(int queue[], int front) {
    return queue[front];
}
```

### Size
```c
int size(int count) {
    return count;
}
```

### IsEmpty
```c
bool isEmpty(int count) {
    return (count == 0);
}
```

## Implentation Queue using Linked List
```c
// A C program to demonstrate linked list based implementation of queue 
#include <stdio.h> 
#include <stdlib.h> 

// A linked list (LL) node to store a queue entry 
struct QNode { 
	int key; 
	struct QNode* next; 
}; 

// The queue, front stores the front node of LL and rear stores the 
// last node of LL 
struct Queue { 
	struct QNode *front, *rear; 
}; 

// A utility function to create a new linked list node. 
struct QNode* newNode(int k) 
{ 
	struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode)); 
	temp->key = k; 
	temp->next = NULL; 
	return temp; 
} 

// A utility function to create an empty queue 
struct Queue* createQueue() 
{ 
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue)); 
	q->front = q->rear = NULL; 
	return q; 
} 

// The function to add a key k to q 
void enQueue(struct Queue* q, int k) 
{ 
	// Create a new LL node 
	struct QNode* temp = newNode(k); 

	// If queue is empty, then new node is front and rear both 
	if (q->rear == NULL) { 
		q->front = q->rear = temp; 
		return; 
	} 

	// Add the new node at the end of queue and change rear 
	q->rear->next = temp; 
	q->rear = temp; 
} 

// Function to remove a key from given queue q 
struct QNode* deQueue(struct Queue* q) 
{ 
	// If queue is empty, return NULL. 
	if (q->front == NULL) 
		return NULL; 

	// Store previous front and move front one node ahead 
	struct QNode* temp = q->front; 
	free(temp); 

	q->front = q->front->next; 

	// If front becomes NULL, then change rear also as NULL 
	if (q->front == NULL) 
		q->rear = NULL; 
	return temp; 
} 

// Driver Program to test anove functions 
int main() 
{ 
	struct Queue* q = createQueue();
	enQueue(q, 10);
	enQueue(q, 20);
	deQueue(q);
    deQueue(q);
	enQueue(q, 30);
	enQueue(q, 40);
	enQueue(q, 50);
	struct QNode* n = deQueue(q); 
	if (n != NULL) 
		printf("Dequeued item is %d", n->key); 
	return 0; 
} 
```
