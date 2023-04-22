#pragma once
#include<iostream>
using namespace std;

typedef struct node
{
	int data;
	struct node *next;
}DataNode,*DataNodePtr;

typedef struct linknode
{
	int data;
	DataNodePtr DataNext;
	struct linknode *LinkNext;
}LinkNode,*LinkNodePtr;

LinkNodePtr CreateHashLink(int Sequence[], int SeqNum)
{
	LinkNodePtr pHead;
	pHead = new LinkNode;
	if (pHead == NULL)
	{
		cout << "allocation failed!!!" << endl;
		exit(-1);
	}
	pHead->DataNext = NULL;
	pHead->LinkNext = NULL;
	for (int i = 16; i >=0; i--)
	{
		LinkNodePtr pLinkNode;
		pLinkNode = new LinkNode;
		pLinkNode->data = i;
		pLinkNode->DataNext = NULL;
		pLinkNode->LinkNext = pHead->LinkNext;
		pHead->LinkNext = pLinkNode;
	}
	for (int i = 0; i < SeqNum; i++)
	{
		int key;
		key = Sequence[i] % 17;
		LinkNodePtr pTemp=pHead->LinkNext;
		while (pTemp->data != key)
		{
			pTemp = pTemp->LinkNext;
		}
		DataNodePtr pDataNode;
		pDataNode = new DataNode;
		pDataNode->data = Sequence[i];
		pDataNode->next = pTemp->DataNext;
		pTemp->DataNext = pDataNode;
	}

	return pHead;
}
bool SearchHashLink(int key,LinkNodePtr pHead)
{
	int Address;
	Address = key % 17;
	LinkNodePtr pLinkTemp=pHead->LinkNext;
	while (pLinkTemp->data != Address)
	{
		pLinkTemp = pLinkTemp->LinkNext;
	}
	DataNodePtr pDataTemp=pLinkTemp->DataNext;
	while (pDataTemp != NULL)
	{
		if (pDataTemp->data == key)return true;
		pDataTemp = pDataTemp->next;
	}
	return false;
}
void DestroyList(LinkNodePtr pHead)
{
	LinkNodePtr pLinkTemp1=pHead->LinkNext;
	while (pLinkTemp1 != NULL)
	{
		LinkNodePtr pLinkTemp2 = pLinkTemp1;
		pLinkTemp1 = pLinkTemp2->LinkNext;
		DataNodePtr pDataTemp1 = pLinkTemp2->DataNext;
		delete pLinkTemp2;
		while (pDataTemp1 != NULL)
		{
			DataNodePtr pDataTemp2 = pDataTemp1;
			pDataTemp1 = pDataTemp2->next;
			delete pDataTemp2;
		}
	}
}