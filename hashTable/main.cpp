#include"hashTable.h"

int main()
{
	printf("-----哈希表-----\n");
	HashTable H;
	int i;
	int size = 11;
	KeyType array[8] = { 22, 41, 53, 46, 30, 13, 12, 67 };
	KeyType key;

	//初始化哈希表
	printf("初始化哈希表\n");
	if (SUCCESS == InitHashTable(H, hashsize[index++])) printf("初始化成功\n");

	//插入哈希表
	printf("插入哈希表\n");
	for (i = 0; i <= 7; i++) {
		key = array[i];
		InsertHash(H, key);
		printHash(H);
	}

	//删除哈希表
	printf("删除哈希表中key为12的元素\n");
	int p, c;
	if (SUCCESS == DeleteHash(H, 12)) {
		printf("删除成功，此时哈希表为：\n");
		printHash(H);
	}

	//查询哈希表
	printf("查询哈希表中key为67的元素\n");
	if (SUCCESS == SearchHash(H, 67, p, c)) printf("查询成功\n");

	//再次插入，测试哈希表的重建
	printf("再次插入，测试哈希表的重建：\n");
	KeyType array1[8] = { 27, 47, 57, 47, 37, 17, 93, 67 };
	for (i = 0; i <= 7; i++) {
		key = array1[i];
		InsertHash(H, key);
		printHash(H);
	}

	// getchar();
	return 0;
}