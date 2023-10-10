#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"

//create a new node//
Node *createNode(void *data)
{
	Node *newNode = (Node*) malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

Node *addNode(linked_list * ll, void * data){
	Node * new_node = createNode(data);
	if(ll->size == 0)
	{
		ll->front = new_node;
		ll->rear = new_node;
		ll->size = 1 ;
	} else {
		new_node->prev = ll->rear;
		ll->rear->next = new_node;
		ll->rear = new_node;
		ll->size += 1;
	}
}

Queue * createQueue()
{
	Queue *q =  (Queue*) malloc(sizeof(Queue));
	q->front = NULL;
	q->rear = NULL;
	q->size = 0;
	return q;
}

void enqueue(Queue *q, void *data)
{
	Node *newNode = createNode(data);
	if(q->size == 0)
	{
		q->front = newNode;
		q->rear = newNode;
	} else {
		q->rear->next = newNode;
		q->rear = newNode;
	}
    q->size += 1;
}

void sort(Queue *q, int (*cmp)(void *data1, void *data2)) {
	Node *i = q->front;
	while(i!=NULL) {
		Node *j = i->next;
		while(j!=NULL) {
			void *temp1 = i->data;
			void *temp2 = j->data;
			if((*cmp)(temp1,temp2) > 0) {
				swapNodes(i,j);
			}
			j = j->next;
		}
		i = i->next;
	}
}

void swapNodes(Node *a, Node *b) {
	void *temp = a->data;
	a->data = b->data;
	b->data = temp;
}

// Dequeue function to remove process from the start of the queue //
void *dequeue(Queue *q)
{
	if(q->front != NULL) {
		Node *currentNode = q->front;
		void *data = currentNode->data;

		q->front = q->front->next; 

		if(q->rear == currentNode) {
			q->rear = NULL;
		}

		q->size--;
		free(currentNode);
		return data;
	}
    return NULL;
}

void displayQueue(Queue *q) {
	Node *ptr = (Node *)q->front;
	printf("<");
    while(ptr!=NULL) {
        printf("%c ",((Process *) ptr->data)->pid);
        printf(":");
        printf("%d ",((Process *) ptr->data)->arrival_time);
		printf(" %d ",((Process *) ptr->data)->runtime);
        printf(";");
        ptr = ptr->next;
    }
    printf(">\n");
}

