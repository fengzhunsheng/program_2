#pragma once
#include<iostream>
using namespace std;

void Bubble_Modified_Sort(int R[], int n)
{
	int i = n - 1;
	int LastExchangeIndex,temp;
	while (i > 1)
	{
		LastExchangeIndex = 1;
		for (int j = 0; j < i; j++)
		{
			if (R[j] > R[j + 1])
			{
				temp = R[j];
				R[j] = R[j + 1];
				R[j + 1] = temp;
				LastExchangeIndex = j;
			}
		}
		i = LastExchangeIndex;
	}
	for (int i = 0; i < n; i++)
	{
		cout << R[i];
		if (i == n - 1)cout << endl;
		else cout << " ";
	}
}
