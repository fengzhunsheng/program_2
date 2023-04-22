#include"DirectInsert_SortingAlgorithm.h"
#include"Shell_Insert_SortingAlgorithm.h"
#include"BubbleModified_SortingAldorithm.h"
#include"Quick_SortingAlgorithm.h"
#include"Merge_sort.h"

int main()
{
	int a[] = {19,30,10,45,34,54,2,3,10,26};
	int n = sizeof(a)/sizeof(int);

	// QuickSort(a, 0, n-1);
	merge_sort(a, n);
	for (int i = 0; i < n; i++)
	{
		cout << a[i];
		if (i == n-1)cout << endl;
		else cout << " ";
	}
	
	return 0;
}