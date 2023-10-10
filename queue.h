#ifndef QUEUE_H
#define QUEUE_H
struct node {
	struct node *next;
	struct node *prev;
	void *data;
};
typedef struct node Node;

struct queue {
	Node *front;
	Node *rear;
	int size;
};

typedef struct queue linked_list;

typedef struct queue Queue;

Node* createNode(void *data);
Node* addNode(Queue *q, void *data);
void swapNodes(Node *a, Node *b);
void removeNode(Queue * ll, void *data);

// Queue Implementation //
Queue *createQueue();
void enqueue(Queue *q, void * data);
void *dequeue(Queue *q);
void sort(Queue *q, int (*cmp)(void *data1, void *data2));
void displayQueue(Queue *q);

#endif

