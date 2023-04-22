#include <stdio.h>
#include <stdlib.h>
#include"order_list.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	ListPtr L1; 
	L1 = (ListPtr)malloc(sizeof(Sqlist));
	int i;
	if(List_init(L1)==success)
	{
		printf("The new empty list has built.\n");
		printf("Please input the number of element of list: ");
		int num;
		scanf_s("%d", &num);
		for(i=1;i<=num;i++)
		{
			int ainterge;
			printf("Please input a interge:");
			scanf_s("%d", &ainterge);
			List_Insert(L1, i, ainterge);
		}
		int value;
		if(List_retrieve(L1,5,&value)==success)
		{
			printf("The 5th element is %d\n",value);
		}
		else
		{
			printf("range_error!\n");
		}
		int position;
		if (List_Locate(L1, 2, &position) == success)
		{
			printf("The number 2 locates in %d\n", position);
		}

		List_destroy(L1);
	}
	else
	{
		printf("erorr!");
	}
	system("pause");
	return 0;
}
