#pragma once
#include<iostream>
using namespace std;

typedef struct BiTreeNode
{
	int data;
	struct BiTreeNode *Lchild;
	struct BiTreeNode *Rchild;
}BiTreeNode,*BiTree;

void PreInOrd(int preord[], int inord[], int PreFist, int PreLast, int InFist, int InLast, BiTree t);

BiTree CreateBiTree(int preord[], int inord[], int n)
{
	BiTree root;
	root = new BiTreeNode;
	root->Lchild = NULL;
	root->Rchild = NULL;
	root->data = 0;
	if (n <= 0)
	{
		cout << "The tree is empty!!!" << endl;
		exit(-1);
	}
	else PreInOrd(preord, inord, 0, n-1, 0, n-1, root);
	return root;
}
void PreInOrd(int preord[], int inord[], int PreFist, int PreLast, int InFist, int InLast, BiTree t)
{
	t->data = preord[PreFist];
	
	int RootIndex;
	RootIndex = InFist;
	while (inord[RootIndex] != preord[PreFist])RootIndex++;/*在中序序列中定位树的根*/
   
	/*递归调用建立左子树*/
	if (RootIndex == InFist) t->Lchild = NULL;
	else
	{
		t->Lchild = new BiTreeNode;
		PreInOrd(preord, inord, PreFist + 1, PreFist + RootIndex - InFist, InFist, RootIndex - 1, t->Lchild);
	}
	/*递归调用建立右子树*/
	if (RootIndex == InLast) t->Rchild = NULL;
	else
	{
		t->Rchild = new BiTreeNode;
		PreInOrd(preord, inord, PreFist + RootIndex - InFist + 1, PreLast, RootIndex + 1, InLast, t->Rchild);
	}
}
