#include"DirectInsert_SortingAlgorithm.h"
#include"Shell_Insert_SortingAlgorithm.h"
#include"BubbleModified_SortingAldorithm.h"
#include"Quick_SortingAlgorithm.h"

int main()
{
	const int n = 20;
	int a[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	QuickSort(a, 0, n-1);
	for (int i = 0; i < n; i++)
	{
		cout << a[i];
		if (i == n-1)cout << endl;
		else cout << " ";
	}
	system("pause");
	return 0;
}