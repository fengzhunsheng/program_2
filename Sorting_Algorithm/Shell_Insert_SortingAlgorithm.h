#pragma once
#include<iostream>
using namespace std;

void Shell_Insert_Sort(int R[], int n, int d[], int t)
{
	int k, m, i, j;
	for (k = 0; k < t; k++)//��k�ˣ�������Ϊd[k]�����н���ֱ�Ӳ�������
	{
		int dk = d[k];
		for (m = 0; m < dk; m++)
		{
			for (i = m + dk; i < n; i += dk)//��mΪ��ʼ������Ϊd[k]��������ֱ������
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