#include "BPlusTree.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <queue>

#ifdef WIN32
	#include <io.h>
#endif

#ifdef LINUX
	#include <unistd.h>
#endif

btree_node* BPlusTree::btree_node_new()
{
    btree_node *node = (btree_node *)malloc(sizeof(btree_node));
    if(nullptr == node) {
        return nullptr;
    }

    for(int i = 0; i < 2 * M -1; i++) {
        node->k[i] = 0;
    }

    for(int i = 0; i < 2 * M; i++) {
        node->p[i] = nullptr;
    }

    node->num = 0;
    node->is_leaf = true;
	node->prev = nullptr;
	node->next = nullptr;
	return node; 
}

btree_node *BPlusTree::btree_create()
{
    btree_node *node = btree_node_new();
    if(nullptr == node) {
        return nullptr;
    }

	node->next = node;
	node->prev = node;

    return node;
}

int BPlusTree::btree_split_child(btree_node *parent, int pos, btree_node *child)
{
    btree_node *new_child = btree_node_new();
    if(nullptr == new_child) {
        return -1;
    }

    new_child->is_leaf = child->is_leaf;
    new_child->num = M - 1;
    
    for(int i = 0; i < M - 1; i++) {
        new_child->k[i] = child->k[i+M];
    }

    if(false == new_child->is_leaf) {
        for(int i = 0; i < M; i++) {
            new_child->p[i] = child->p[i+M];
        }
    }

    child->num = M - 1;
	if(true == child->is_leaf) {
		child->num++;  // if leaf, keep the middle ele, put it in the left
	}

    for(int i = parent->num; i > pos; i--) {
        parent->p[i+1] = parent->p[i];
    }
    parent->p[pos+1] = new_child;

    for(int i = parent->num - 1; i >= pos; i--) {
        parent->k[i+1] = parent->k[i];
    }
    parent->k[pos] = child->k[M-1];
    
    parent->num += 1;

	// update link
	if(true == child->is_leaf) {
		new_child->next = child->next;
		child->next->prev = new_child;
		new_child->prev = child;
		child->next = new_child;
	}
	return 1;
}

void BPlusTree::btree_insert_nonfull(btree_node *node, int target)
{
    if(true == node->is_leaf) {
        int pos = node->num;
        while(pos >= 1 && target < node->k[pos-1]) {
            node->k[pos] = node->k[pos-1];
            pos--;
        }

        node->k[pos] = target;
        node->num += 1;
		btree_node_num+=1;
		
    } else {
        int pos = node->num;
        while(pos > 0 && target < node->k[pos-1]) {
            pos--;
        }

        if(2 * M -1 == node->p[pos]->num) {
            btree_split_child(node, pos, node->p[pos]);
            if(target > node->k[pos]) {
                pos++;
            }
        }
        
        btree_insert_nonfull(node->p[pos], target);
    }
}

btree_node* BPlusTree::btree_insert(btree_node *root, int target)
{
    if(nullptr == root) {
        return nullptr;
    }

    if(2 * M - 1 == root->num) {
        btree_node *node = btree_node_new();
        if(nullptr == node) {
            return root;
        }
        
        node->is_leaf = false;
        node->p[0] = root;
        btree_split_child(node, 0, root);
        btree_insert_nonfull(node, target);
        return node;
    } else {
        btree_insert_nonfull(root, target);    
        return root;
    }
}

bool BPlusTree::btree_search(btree_node *root, int target)
{
	if(root == nullptr)
	{
		return false;
	}

	int i = 0;
	while(i < root->num && target > root->k[i])
	{
		++i;
	}
	if(root->is_leaf)
	{
		if(target == root->k[i])
		{
			return true;
		}
		else return false;
	}
	else
	{
		return btree_search(root->p[i], target);
	}
}

void BPlusTree::btree_merge_child(btree_node *root, int pos, btree_node *leftchild, btree_node *rightchild)
{
	if(true == leftchild->is_leaf) {
		leftchild->num = 2 * M - 2;
		for(int i = M; i < 2 * M - 1; i++) {
			leftchild->k[i-1] = rightchild->k[i-M];
		}
	} else {
		leftchild->num = 2 * M - 1;
		for(int i = M; i < 2 * M - 1; i++) {
			leftchild->k[i] = rightchild->k[i-M];
		}
		leftchild->k[M-1] = root->k[pos];
		for(int i = M; i < 2 * M; i++) {
			leftchild->p[i] = rightchild->p[i-M];
		}
	}

	for(int j = pos + 1; j < root->num; j++) {
		root->k[j-1] = root->k[j];
		root->p[j] = root->p[j+1];
	}

	root->num -= 1;

	// update link
	if(true == leftchild->is_leaf) {
		leftchild->next = rightchild->next;
		rightchild->next->prev = leftchild;
	}

	free(rightchild);
}

btree_node *BPlusTree::btree_delete(btree_node *root, int target)
{
	if(1 == root->num) {
		btree_node *y = root->p[0];
		btree_node *z = root->p[1];
		if(nullptr != y && nullptr != z &&
				M - 1 == y->num && M - 1 == z->num) {
			btree_merge_child(root, 0, y, z);
			free(root);
			btree_delete_nonone(y, target);
			return y;
		} else {
			btree_delete_nonone(root, target);
			return root;
		}
	} else {
		btree_delete_nonone(root, target);	
		return root;
	}
}

void BPlusTree::btree_delete_nonone(btree_node *root, int target)
{
	if(true == root->is_leaf) 
	{
		int i = 0;
		while(i < root->num && target > root->k[i]) i++;

		if(target == root->k[i]) 
		{
			for(int j = i + 1; j < root->num; j++) {
				root->k[j-1] = root->k[j];
			}
			root->num -= 1;
			btree_node_num -= 1;
			
		} 
		else 
		{
			printf("target not found\n");
		}
	} 
	else
	{
		int i = 0;
		btree_node *leftSibling = nullptr, *curNode = nullptr, *rightSibling = nullptr;
		while(i < root->num && target > root->k[i]) i++;
		
		curNode = root->p[i];
		if(i < root->num) {
			rightSibling = root->p[i+1];
		}
		if(i > 0) {
			leftSibling = root->p[i-1];
		}

		if(curNode->num == M - 1) {
			if(i > 0 && leftSibling->num > M - 1) {
				btree_shift_to_right_child(root, i-1, leftSibling, curNode);
			} else if(i < root->num && rightSibling->num > M - 1) {
				btree_shift_to_left_child(root, i, curNode, rightSibling);
			} else if(i > 0) {
				btree_merge_child(root, i-1, leftSibling, curNode);
				curNode = leftSibling;
			} else {
				btree_merge_child(root, i, curNode, rightSibling);
			}
			btree_delete_nonone(curNode, target);
		} else {
			btree_delete_nonone(curNode, target);
		}
	}
}

int BPlusTree::btree_search_predecessor(btree_node *root)
{
	btree_node *y = root;
	while(false == y->is_leaf) {
		y = y->p[y->num];
	}
	return y->k[y->num-1];
}

int BPlusTree::btree_search_successor(btree_node *root) 
{
	btree_node *z = root;
	while(false == z->is_leaf) {
		z = z->p[0];
	}
	return z->k[0];
}

void BPlusTree::btree_shift_to_right_child(btree_node *root, int pos, btree_node *leftChild, btree_node *rightChild)
{
	rightChild->num += 1;

	for(int i = rightChild->num -1; i > 0; i--) {
		rightChild->k[i] = rightChild->k[i-1];
	}

	if(false == rightChild->is_leaf) {
		rightChild->k[0] = root->k[pos];
		root->k[pos] = leftChild->k[leftChild->num-1];
	} else {
		rightChild->k[0] = leftChild->k[leftChild->num-1];
		root->k[pos] = leftChild->k[leftChild->num-2];
	}


	if(false == rightChild->is_leaf) {
		for(int i = rightChild->num; i > 0; i--) {
			rightChild->p[i] = rightChild->p[i-1];
		}
		rightChild->p[0] = leftChild->p[leftChild->num];
	} 

	leftChild->num -= 1;
}

void BPlusTree::btree_shift_to_left_child(btree_node *root, int pos, btree_node *leftChild, btree_node *rightchild)
{
	leftChild->num += 1;

	if(false == rightchild->is_leaf) {
		leftChild->k[leftChild->num-1] = root->k[pos];
		root->k[pos] = rightchild->k[0];
	} else {
		leftChild->k[leftChild->num-1] = rightchild->k[0];
		root->k[pos] = rightchild->k[0];
	}

	for(int j = 1; j < rightchild->num; j++) {
		rightchild->k[j-1] = rightchild->k[j];
	}

	if(false == rightchild->is_leaf) {
		leftChild->p[leftChild->num] = rightchild->p[0];
		for(int j = 1; j <= rightchild->num; j++) {
			rightchild->p[j-1] = rightchild->p[j];
		}
	} 

	rightchild->num -= 1;
}

void BPlusTree::btree_inorder_print(btree_node *root) 
{
    if(nullptr != root) {
        btree_inorder_print(root->p[0]);
        for(int i = 0; i < root->num; i++) {
            printf("%d ", root->k[i]);
          // 	fwrite(&root,sizeof(root),1,fp);
            btree_inorder_print(root->p[i+1]);
        }
    }
}

void BPlusTree::btree_linear_print(btree_node *root) 
{
	if(nullptr != root) {
		btree_node *leftmost = root;
		while(false == leftmost->is_leaf) {
			leftmost = leftmost->p[0];
		}
		
		btree_node *iter = leftmost;
		do {
			for(int i = 0; i < iter->num; i++) {
            	printf("%d ", iter->k[i]);
            //	fwrite(&root,sizeof(root),1,fp);
			}
			iter = iter->next;
        } while(iter != leftmost);
		printf("\n");
	}
}

void BPlusTree::Save(btree_node *root) 
{
//	fwrite(root,sizeof(root),1,pfile);
}

void BPlusTree::btree_level_display(btree_node *root) 
{
	// just for simplicty, can't exceed 200 nodes in the tree
	std::queue<btree_node *> treeQueue;
	treeQueue.push(root);

	while(!treeQueue.empty()) {
		int count = treeQueue.size();
		for(int i  = 0 ; i < count; ++i)
		{
			btree_node *node = treeQueue.front();
			treeQueue.pop();

			printf("[");
			for(int i = 0; i < node->num; i++) {
				printf("%d ", node->k[i]);
			}
			printf("]");
			

			for(int i = 0; i <= node->num; i++) {
				if(nullptr != node->p[i]) {
					treeQueue.push(node->p[i]);               
				}
			}
		}
		printf("\n");
		
	}
	printf("\n");
}

void BPlusTree::linear_print()
{
	btree_linear_print(roots);
}

BPlusTree::BPlusTree()
{
	// 先判断文件是否存在
 	// windows下，是io.h文件，linux下是 unistd.h文件 
  	// int access(const char *pathname, int mode);
   	if(-1==access("define.Bdb",F_OK))
    {
	   	// 不存在 ,创建 
//	   	pfile = fopen("bplus.bp","w");
   		roots = btree_create();
	}
 	else
  	{
//	   	pfile = fopen("bplus.bp","r+");
	   	roots = btree_create();
//	   	fread(roots,sizeof(roots),1,pfile);
   	}
}

void BPlusTree::del_tree(btree_node *root)
{
	if(root != nullptr)
	{
		for(int i = 0; i <= root->num; ++i)
		{
			if(root->p[i] != nullptr)
			{
				del_tree(root->p[i]);
			}
		}
		delete root;
	}
}

BPlusTree::~BPlusTree()
{
	del_tree(roots);
}