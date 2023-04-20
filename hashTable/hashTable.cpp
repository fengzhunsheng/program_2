#include"hashTable.h"

int temp[] = { 11, 31, 61, 127, 251, 503 };
int *hashsize = temp;
int index = 0;

// 哈希函数：除留余数法
int Hash(KeyType key, int m) 
{
	return (3 * key) % m;
}

// 处理哈希冲突：线性探测
void collision(int &p, int m) 
{
	p = (p + 1) % m;
}

// 初始哈希表
Status InitHashTable(HashTable &H, int size)
{
	int i;
	H.rcd = (RcdType *)malloc(sizeof(RcdType)*size);
	H.tag = (int *)malloc(sizeof(int)*size);
	if (NULL == H.rcd || NULL == H.tag) return OVERFLOW;
	KeyType maxNum = MAXNUM;
	for (i = 0; i < size; i++) 
    {
		H.tag[i] = 0;
		H.rcd[i].key = maxNum;
	}
	H.size = size;
	H.count = 0;
	return OK;
}

// 在哈希表中查询
Status SearchHash(const HashTable &H, KeyType key, int &p, int &c) 
{
	p = Hash(key, H.size);
	c = 0;
	while ((1 == H.tag[p] && H.rcd[p].key != key) || -1 == H.tag[p]) 
    {
		collision(p, H.size);  
        c++;
        if(c >= H.count)
        {
            break;
        }
	}

	if (1 == H.tag[p] && key == H.rcd[p].key) return SUCCESS;
	else return UNSUCCESS;
}

// 重建哈希表
Status recreateHash(HashTable &H) 
{
	RcdType *orcd;
	int *otag, osize, i;
	orcd = H.rcd;
	otag = H.tag;
	osize = H.size;

	InitHashTable(H, hashsize[index++]);
	//把所有元素，按照新哈希函数放到新表中
	for (i = 0; i < osize; i++) 
    {
		if (1 == otag[i]) 
        {
			InsertHash(H, orcd[i].key);
		}
	}

    free(orcd);
    orcd = nullptr;
    free(otag);
    otag = nullptr;

	return OK;
}

// 插入哈希表
Status InsertHash(HashTable &H, KeyType key)
{
	int p, c;
	if (UNSUCCESS == SearchHash(H, key, p, c)) //没有相同key
    { 
        //插入代码
        H.rcd[p].key = key;
        H.tag[p] = 1;
        H.count++;
		if (c*1.0 / H.size < 0.5 || H.count*1.0 / H.size < 0.8) //冲突次数未达到上线
        { 
			return SUCCESS;
		}
		else recreateHash(H); //重构哈希表 
	}
	return UNSUCCESS;
}

// 删除哈希表
Status DeleteHash(HashTable &H, KeyType key) 
{
	int p, c;
	if (SUCCESS == SearchHash(H, key, p, c)) 
    {
		//删除代码
		H.tag[p] = -1;
		H.count--;
		return SUCCESS;
	}
	else return UNSUCCESS;
}

//打印哈希表
void printHash(HashTable H)
{
	int  i;
	printf("key : ");
	for (i = 0; i < H.size; i++)
		printf("%5d", H.rcd[i].key);
	printf("\n");
	printf("tag : ");
	for (i = 0; i < H.size; i++)
		printf("%5d", H.tag[i]);
	printf("\n\n");
}