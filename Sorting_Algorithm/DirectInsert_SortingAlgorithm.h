#pragma once
#include<iostream>
using namespace std;

void Direct_Insert_sort(int R[], int n)
{
	for (int i = 1; i < n; i++)
	{
		if (R[i] < R[i - 1])
		{
			int temp;
			temp = R[i];
			int j = i - 1;
			while (R[j]>temp)
			{
				R[j + 1] = R[j];
				j--;
			}
			R[j + 1] = temp;
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << R[i];
		if (i == n - 1)cout << endl;
		else cout << " ";
	}
	
}