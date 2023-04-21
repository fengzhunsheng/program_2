#pragma once
// the degree of btree
#define M 2 

typedef struct btree_nodes {
	int k[2*M-1];
	struct btree_nodes *p[2*M];
	int num;
	bool is_leaf;
	struct btree_nodes *prev;  // use one struct just for simple,B+Tree used
	struct btree_nodes *next;  // B+Tree used
	
} btree_node;


typedef struct StorageNode{
	btree_node bnode;
	int index[M];   // index_set 
}storage_node;

typedef struct StorageStruct{
	storage_node *snode;
	int len;
}storage_struct;