#include"linkedLisst_operation.h"

ListNodePtr List_Create(int elem[], int n);
void List_Destroy(ListNodePtr pHead);
void Lsit_Traverse(ListNodePtr pHead);
void List_Insert(ListNodePtr pHead, int pos, int elem);
int List_size(ListNodePtr pHead);

int main()
{
	int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
	ListNodePtr p;
	p = (ListNodePtr)malloc(sizeof(ListNode));
	if (p == NULL)
	{
		cout << "allocation failed!!!" << endl;
		return 0;
	}
	p = List_Create(a, 10);
	
	Lsit_Traverse(p);

	int ListLen;
	ListLen = List_size(p);
	cout << "The lenth of linked list is :" << ListLen << endl;

	List_Insert(p, 5, 6);

	Lsit_Traverse(p);

	List_Destroy(p);

	system("pause");
	return 0;
}