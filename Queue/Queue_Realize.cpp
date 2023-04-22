#include<iostream>
using namespace std;

typedef struct node
{
	int entry;
	struct node *next;
}QueueNode, *QueueNodePtr;
typedef struct queue
{
	QueueNodePtr front;
	QueueNodePtr rear;
}Queue, *QueuePtr;
QueuePtr Queue_Init_Mine();
void Queue_Destroy_Mine(QueuePtr pHead);
int Queue_DeQueue_Mine(QueuePtr pHead);
void Queue_EnQueue_Mine(QueuePtr pHead, int item);

int main()
{
	QueuePtr p;
	p=Queue_Init_Mine();
	int i, num1,num2;
	for (i = 0; i < 5; i++)
	{
		cin >> num1;
		Queue_EnQueue_Mine(p, num1);
	}
	for (i = 0; i < 5; i++)
	{
		num2 = Queue_DeQueue_Mine(p);
		cout << num2 << " ";
	}
	Queue_Destroy_Mine(p);
	system("pause");
	return 0;
}

QueuePtr Queue_Init_Mine(void)
{
	QueuePtr pHead;
	pHead = new Queue;
	QueueNodePtr ptr;
	ptr = new QueueNode;
	if (ptr == NULL)
	{
		cout << "allocattion fail" << endl;
		exit(-1);
	}
	pHead->front = pHead->rear = ptr;
	ptr->next = NULL;

	return pHead;
}

void Queue_Destroy_Mine(QueuePtr pHead)
{
	QueueNodePtr pNode = pHead->front;
	QueueNodePtr qNode;
	while (pNode->next != NULL)
	{
		qNode = pNode;
		pNode = pNode->next;
		delete qNode;
	}
	delete pNode;
}
void Queue_EnQueue_Mine(QueuePtr pHead, int item)
{
	QueueNodePtr pNode;
	pNode = new QueueNode;
	if (pNode == NULL)
	{
		cout << "allocation fail" << endl;
		exit(-1);
	}
	pNode->entry = item;
	pNode->next = NULL;
	pHead->rear->next = pNode;
	pHead->rear = pNode;
}
int Queue_DeQueue_Mine(QueuePtr pHead)
{
	QueueNodePtr pNode;
	if (pHead->front->next == NULL && pHead->rear->next == NULL)
	{
		cout << "Queue is empty!!!" << endl;
		exit(-1);
	}
	pNode = pHead->front->next;
	int x;
	x = pNode->entry;
	pHead->front->next = pNode->next;
	if (pHead->rear == pNode)
	{
		pHead->rear = pHead->front;
	}
	delete pNode;
	return x;
}