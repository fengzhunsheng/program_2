#pragma once
#include<iostream>
using namespace std;

void Shell_Insert_Sort(int R[], int n, int d[], int t)
{
	int k, m, i, j;
	for (k = 0; k < t; k++)//第k趟，对增量为d[k]的序列进行直接插入排序
	{
		int dk = d[k];
		for (m = 0; m < dk; m++)
		{
			for (i = m + dk; i < n; i += dk)//将m为起始，增量为d[k]的子序列直接排序
			{
				if (R[i] > R[i - dk])
				{
					int temp = R[i];
					for (j = i - dk; j >= 0 && R[j] > temp; j -= dk)
					{
						R[j + dk] = R[j];
					}
					R[j + dk] = temp;
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << R[i];
		if (i == n - 1)cout << endl;
		else cout << " ";
	}
}