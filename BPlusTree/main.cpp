#include <stdio.h>
#include <stdlib.h>
#include "BPlusTree.h"

int main()
{
	
	/*************************************直接调用 B+ 的调度使用****************************************/
	/************************************* Direct call B+ method ****************************************/
	BPlusTree bpt;
	
	printf("insert data:\n");
    int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 52, 23, 30, 20, 7, 14, 27, 34, 44, 51, 56};
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++) {
		bpt.insert(arr[i]);
		bpt.level_display();
    }
	printf("finish insert data:\n\n");
    // printf("no delete data:\n");
	
 	// printf("display about B+ Tree:\n");
	// bpt.level_display();
	// bpt.inorder_print();
	// printf("\n");
	// bpt.linear_print();
	// printf("\n");
	// bpt.NodeNum_print();

	printf("search data:\n");
	int tosearch[] = {12,48,50,35};
	for(int i = 0; i < sizeof(tosearch) / sizeof(int); i++)
	{
		bpt.search(tosearch[i]);
	}
	printf("finish search data:\n\n");

	printf("\ndelete data:\n");
	int todel[] = {15, 18, 19, 23, 30, 31, 32, 52, 50};
		
	for(int i = 0; i < sizeof(todel) / sizeof(int); i++) {
		printf("after delete %d\n", todel[i]);
		bpt.del(todel[i]);
		bpt.level_display();
	} 

	// bpt.NodeNum_print();
	
 	// printf("\n\ndelete after data:\n");
	
 	// printf("display about B+ Tree:\n");
	// bpt.level_display();
	// bpt.inorder_print();
	// printf("\n");
	// bpt.linear_print();
	// printf("\n");
	
    return 0;
}
