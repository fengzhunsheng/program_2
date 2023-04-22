#pragma once
#include<iostream>
#include"BinaryTree_Create.h"
using namespace std;

void PreOrder(BiTree root)
{
	if (root != NULL)
	{
		cout << root->data << " ";
		PreOrder((root)->Lchild);
		PreOrder(root->Rchild);
	}
}
void InOrder(BiTree root)
{
	if (root != NULL)
	{
		InOrder(root->Lchild);
		cout << root->data << " ";
		InOrder(root->Rchild);
	}
}
void PostOrder(BiTree root)
{
	if (root != NULL)
	{
		PostOrder(root->Lchild);
		PostOrder(root->Rchild);
		cout << root->data << " ";
	}
}
