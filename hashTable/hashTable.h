#pragma once
#include<stdio.h>
#include<stdlib.h>

#define SUCCESS 1
#define UNSUCCESS 0
#define OVERFLOW -1
#define OK 1
#define ERROR -1
#define MAXNUM 9999		// 用于初始化哈希表的记录 key

typedef int Status;
typedef int KeyType;

// 哈希表中的记录类型
typedef struct {
	KeyType key;
}RcdType;

// 哈希表类型
typedef struct {
	RcdType *rcd;
	int size;
	int count;
	int *tag;
}HashTable;

// 哈希表每次重建增长后的大小
extern int *hashsize;

extern int index;

int Hash(KeyType key, int m);
void collision(int &p, int m);
Status InitHashTable(HashTable &H, int size);
Status SearchHash(const HashTable &H, KeyType key, int &p, int &c);
Status recreateHash(HashTable &H);
Status InsertHash(HashTable &H, KeyType key);
Status DeleteHash(HashTable &H, KeyType key);
void printHash(HashTable H);