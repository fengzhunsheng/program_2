#include"redBlackTree.hpp"
#include<random>
#include<ctime>

int main()
{
	cout << "---【红黑树】---" << endl;
	// 创建红黑树
	bst tree;

	// 插入元素
    default_random_engine e;
    e.seed(time(0));
    uniform_int_distribution<int> U(0,INT_MAX);
    const int size = 10e4;
    int arr2[size];
    for(int i = 0; i < size; ++i)
    {
        arr2[i] = U(e);
    }
    
    for(auto &&item:arr2)
    {
        tree.insert(item);
    }

	// 顺序打印红黑树
	cout << "插入元素后的红黑树：" << endl;
	tree.inorder();

	// 删除元素
    int arr1[] = {2, 9,123, 0, 33, 245};
    for(auto &&item:arr1)
    {
        tree.delete_value(item);
    }
	

	// 顺序打印红黑树
	cout << "删除元素 2 后的红黑树：" << endl;
	tree.inorder();

	return 0;
}