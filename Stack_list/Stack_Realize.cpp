#include<iostream>
using namespace std;

typedef struct stack
{
	int top;
	int maxSize;
	int *entry;
}Stack, *StackPtr;
void OrderStack_Init(StackPtr s, int size)
{
	s->entry = new int[size];//delete []s->entry;
	if (s->entry == NULL)
	{
		cout << "allocation failed!!£¡" << endl;
		exit(-1);
	}
	s->top = -1;
	s->maxSize = size;
}
void OrderStack_Destroy(StackPtr s)
{
	if (s->entry != NULL)
	{
		delete[]s->entry;
		s->entry = NULL;
		s->top = -1;
	}
}
void OrderStack_Push(StackPtr s, int item)
{
	if (s->top >= s->maxSize - 1)
	{
		cout << "Stack full" << endl;
		exit(-1);
	}
	else
	{
		s->top++;
		s->entry[s->top] = item;
	}
}
int OrderStack_Pop(StackPtr s)
{
	int item;
	if (s->top <= -1)
	{
		cout << "Stack empty" << endl;
		exit(-1);
	}
	else
	{
		item = s->entry[s->top];
		s->top--;
	}
	return item;
}
int main()
{
	StackPtr stackPtr;
	stackPtr = new Stack;
	OrderStack_Init(stackPtr, 10);
	int StackItem;
	for (int i = 0;i < 5; i++)
	{
		cin >> StackItem;
		OrderStack_Push(stackPtr, StackItem);
	}
	for (int i = 0; i < 5; i++)
	{
		cout << OrderStack_Pop(stackPtr)<<" ";
	}
	OrderStack_Destroy(stackPtr);
	system("pause");
	return 0;
}