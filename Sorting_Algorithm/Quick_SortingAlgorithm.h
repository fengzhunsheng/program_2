#pragma once
#include<iostream>
using namespace std;

int Partition(int Array[], int low, int high)
{
	int pivot = Array[low];
	while (low < high)
	{
		while (low < high && Array[high] >= pivot)
		{
			high--;
		}
		Array[low] = Array[high];
		while (low < high && Array[low] <= pivot)
		{
			low++;
		}
		Array[high] = Array[low];
	}
	Array[low] = pivot;
	
	return low;	
}
void QuickSort(int Array[], int low, int high)
{
	if (low < high)
	{
		int Pivot_Position = Partition(Array, low, high);//���û��ֹ��̣���һ�λ���
		QuickSort(Array, low, Pivot_Position - 1);//��ǰ��һ���֣��ݹ���ÿ����������
		QuickSort(Array, Pivot_Position + 1, high);//�Ժ���һ���֣��ݹ���ÿ����������
	}
}
