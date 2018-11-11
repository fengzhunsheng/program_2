#include"BinaryTree_Create.h"
#include"BinaryTree_Traveser.h"
#include"BinaryTree_Leaf_Depth.h"

BiTree CreateBiTree(int preord[], int inord[], int n);
void PreOrder    (BiTree root);
void InOrder     (BiTree root);
void PostOrder   (BiTree root);
int  BiTree_Leaf (BiTree root);
int  BiTree_Depth(BiTree root);

int main()
{
	int a[7] = { 1,2,3,4,5,6,7 };
	int b[7] = { 3,2,4,1,5,7,6 };
	BiTree pRoot;

	pRoot=CreateBiTree(a, b, 7);

	PreOrder(pRoot);
	cout << "  (PreOrder)" << endl;
	InOrder(pRoot);
	cout << "  (InOrder)"  << endl;
	PostOrder(pRoot);
	cout << "  (PostOrder)"<< endl;

	cout << "The Leaves of this tree is : " << BiTree_Leaf(pRoot)  << endl;
	cout << "The depth  of this tree is : " << BiTree_Depth(pRoot) << endl;

	system("pause");
	return 0;
}