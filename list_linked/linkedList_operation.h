#pragma once
#include<iostream>
using namespace std;

typedef struct node
{
	int data;
	struct node *next;
}ListNode,*ListNodePtr;
ListNodePtr List_Create(int elem[], int n)
{
	ListNodePtr pHead, pNode;
	pHead = (ListNodePtr)malloc(sizeof(ListNode));
	pHead->next = NULL;
	int i = n - 1;
	while (i >= 0)
	{
		pNode = (ListNodePtr)malloc(sizeof(ListNode));
		if (pNode == NULL)
		{
			cout << "allocation failed!!!" << endl;
			exit(-1);
		}
		pNode->data = elem[i];
		pNode->next = pHead->next;
		pHead->next = pNode;
		i--;
	}
	return pHead;
}
void List_Destroy(ListNodePtr pHead)
{
	ListNodePtr pNode = pHead->next;
	while (pNode != NULL)
	{
		pHead->next = pNode->next;
		free(pNode);
		pNode = pHead->next;
	}
	free(pHead);
}
int List_size(ListNodePtr pHead)
{
	ListNodePtr pNode = pHead->next;
	int length = 0;
	while (pNode != NULL)
	{
		length++;
		pNode = pNode->next;
	}
	return length;
}
void Lsit_Traverse(ListNodePtr pHead)
{
	ListNodePtr pNode = pHead->next;
	int i = 1;
	while (pNode != NULL)
	{
		cout << "The data of " << i << " node is " << pNode->data << endl;
		pNode = pNode->next;
		i++;
	}
}
void List_Insert(ListNodePtr pHead, int pos, int elem)
{
	ListNodePtr pre=pHead->next, pNode;
	int i = 1;
	while (pre != NULL)
	{
		if (i == pos - 1)
		{
			break;
		}
		else
		{
			pre = pre->next;
			i++;
		}
	}
	if (pre == NULL)
	{
		cout << pos << "is grater than the length of linked list" << endl;
		exit(-1);
	}
	else
	{
		pNode = (ListNodePtr)malloc(sizeof(ListNode));
		pNode->data = elem;
		pNode->next = pre->next;
		pre->next = pNode;
	}
}

