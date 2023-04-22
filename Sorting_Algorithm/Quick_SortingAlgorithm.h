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
		if(low < high)
		{
			Array[low] = Array[high];
		}
		
		while (low < high && Array[low] <= pivot)
		{
			low++;
		}
		if(low < high)
		{
			Array[high] = Array[low];
		}	
	}
	Array[low] = pivot;
	
	return low;	
}
void QuickSort(int Array[], int low, int high)
{
	if (low < high)
	{
		int Pivot_Position = Partition(Array, low, high);	//找出基准位置
		QuickSort(Array, low, Pivot_Position - 1);			//基准左侧都是小于基准的数
		QuickSort(Array, Pivot_Position + 1, high);			//基准右侧都是大于基准的数
	}
}
