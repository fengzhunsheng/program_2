#pragma once
#include"BinaryTree_Create.h"

int BiTree_Leaf(BiTree root)
{
	if (root == NULL)return 0;
	if (root->Lchild == NULL && root->Rchild == NULL)return 1;
	return (BiTree_Leaf(root->Lchild) + BiTree_Leaf(root->Rchild));
}

int BiTree_Depth(BiTree root)
{
	if (root == NULL)return 0;
	if (root->Lchild == NULL && root->Rchild == NULL)return 1;
	int depthL,depthR;
	depthL = BiTree_Depth(root->Lchild);
	depthR = BiTree_Depth(root->Rchild);
	return (1 + (depthL > depthR ? depthL : depthR));
}