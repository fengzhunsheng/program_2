#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 40


typedef struct Sqlist
{
	int *elem;
	int length;
	int listSize;
}Sqlist,*ListPtr;
 
typedef enum Status
{
	success,fail,fatal,range_error	
} Status;

Status List_init(ListPtr L){
	Status status=fatal;
	L->elem=(int *)	malloc(LIST_INIT_SIZE*sizeof(int));
	if(L->elem!=NULL)
	{
		L->length=0;
		status=success;
	}
	return success;
}
void List_destroy(ListPtr L){
	if(L->elem!=NULL)
	{
		free(L->elem);
		L->elem=NULL;
	}
	L->length=0;
}
Status List_retrieve(ListPtr L,int pos,int *elem){
	Status status=range_error;
	int len=L->length;
	if(pos>=1 && pos<=len)
	{
		*elem=L->elem[pos];
		status=success;
	}
	return status;
}
Status List_Locate(ListPtr L,int elem,int *pos){
	Status status=range_error;
	int len=L->length;
	int i=1;
	while(i<=len && L->elem[i]!=elem)
	{
		i++;
	}
	if(i<=len)
	{
		*pos=i;
		status=success;
	}
	return status;
}
Status List_Insert(ListPtr L,int pos,int elem){
	Status status=range_error;
	int len=L->length,i;
	if(len>LIST_INIT_SIZE)
	{
		printf("error! overflow!!!");
	}
	else if(pos>=1 && pos<=len+1)
	{
		for(i=len;i>=pos;i--)
		{
			L->elem[i+1]=L->elem[i];
		}
		L->elem[pos]=elem;
		L->length++;
		status=success;
	}
	return success;
}
