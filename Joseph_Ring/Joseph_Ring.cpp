#include<iostream>
using namespace std;

typedef struct node
{
	int data;
	struct node *next;
}ListNode, *ListNodePtr;

ListNodePtr List_Create(int n);
void List_Destroy(ListNodePtr pHead);

int main()
{
	int AllNum, RemainNum, CircleNum;
	cout << "please input AllNum, RemainNum, CircleNum:" << endl;
	cin >> AllNum >> RemainNum >> CircleNum;
	ListNodePtr Phead,pNode,pOut;
	Phead = List_Create(AllNum);
	pNode = Phead->next;
	int remainNum=AllNum;
	while (remainNum > RemainNum)
	{
		int i = 1;
		while (i < CircleNum-1)
		{
			pNode = pNode->next;
			i++;
		}
		pOut = pNode->next;
		pNode->next = pOut->next;
		if (Phead->next == pOut)
		{
			Phead->next = pOut->next;
		}
		cout << pOut->data << " ";
		delete pOut;
		pNode = pNode->next;
		remainNum--;
	}
	List_Destroy(Phead);

	system("pause");
	return 0;
}
ListNodePtr List_Create(int n)
{
	ListNodePtr pHead, pNode;
	pHead = new ListNode;
	pHead->next = NULL;
	int i = n;
	while (i >= 1)
	{
		pNode = new ListNode;
		if (pNode == NULL)
		{
			cout << "allocation failed!!!" << endl;
			exit(-1);
		}
		pNode->data = i;
		pNode->next = pHead->next;
		pHead->next = pNode;
		i--;
	}
	ListNodePtr pTemp;
	pTemp = pHead->next;
	while (pTemp->next != NULL)
	{
		pTemp = pTemp->next;
	}
	pTemp->next = pHead->next;

	return pHead;
}
void List_Destroy(ListNodePtr pHead)
{
	ListNodePtr pNode = pHead->next;
	ListNodePtr pTemp = pNode->next;
	while (pTemp->next != pNode)
	{
		pNode->next = pTemp->next;
		delete pTemp;
		pTemp = pNode->next;
	}
	delete pTemp;
	delete pNode;
	delete pHead;
}