#include<iostream>
#include"Link_Address.h"
#include"Sequential_Search.h"
using namespace std;

int SeqSearch(int a[], int n, int key);
LinkNodePtr CreateHashLink(int Sequence[], int SeqNum);
bool SearchHashLink(int key, LinkNodePtr pHead);
void DestroyList(LinkNodePtr pHead);

int main()
{
	int array[30] =
	{ 11,18,19,25,28,26,24,29,34,21,
      32,37,35,42,48,46,43,49,6,8,
	   9,51,58,53,57,2,54,7,63,64 
	};
	
	int num;
	cin >> num;
	LinkNodePtr p = CreateHashLink(array, 30);
	if (SearchHashLink(num, p))
	{
		cout << num << " exists." << endl;
	}
	else 
	{
		cout << num << " doesnot exit." << endl;
	}
	DestroyList(p);

	system("pause");
	return 0;
}