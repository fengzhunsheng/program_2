#pragma once
#include "struct.h"
#include "Tree.h"

class BPlusTree :
	public Tree
{
protected:
	virtual btree_node* btree_create();
	virtual btree_node* btree_node_new();
	virtual int btree_split_child(btree_node *parent, int pos, btree_node *child);
	virtual void btree_insert_nonfull(btree_node *node, int target);
	virtual void btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z);
	virtual void btree_delete_nonone(btree_node *root, int target);
	virtual int btree_search_successor(btree_node *root);
	virtual int btree_search_predecessor(btree_node *root);
	virtual void btree_shift_to_left_child(btree_node *root, int pos, btree_node *y, btree_node *z);	
	virtual void btree_shift_to_right_child(btree_node *root, int pos, btree_node *y, btree_node *z);
	virtual btree_node* btree_insert(btree_node *root, int target);
	virtual bool btree_search(btree_node *root, int target);
	virtual btree_node *btree_delete(btree_node *root, int target);
	virtual void btree_inorder_print(btree_node *root);
	virtual void btree_level_display(btree_node *root);
	virtual void del_tree(btree_node *root);
 	virtual void Save(btree_node *root);
	/**
	 * @brief print tree linearly using prev/next pointer
	 *
	 * @param root: root of tree
	 */
	void btree_linear_print(btree_node *root);

public:
	BPlusTree();
	~BPlusTree();
	void linear_print();
};

// B+树定义：

// 1）B+树包含2种类型的结点：内部结点（也称索引结点）和叶子结点。根结点本身即可以是内部结点，也可以是叶子结点。根结点的关键字个数最少可以只有1个。

// 2）B+树与B树最大的不同是内部结点不保存数据，只用于索引，所有数据（或者说记录）都保存在叶子结点中。

// 3） m阶B+树表示了内部结点最多有m-1个关键字（或者说内部结点最多有m个子树），阶数m同时限制了叶子结点最多存储m-1个记录。

// 4）内部结点中的key都按照从小到大的顺序排列，对于内部结点中的一个key，左树中的所有key都小于等于它，右子树中的key都大于它。叶子结点中的记录也按照key的大小排列。

// 5）每个叶子结点都存有相邻叶子结点的指针，叶子结点本身依关键字的大小自小而大顺序链接。