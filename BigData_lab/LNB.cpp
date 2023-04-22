////
//链路预测算法
////

#include<math.h>
#include <fstream>
#include<iostream>
#include<time.h>
using namespace std;

#define V 380  //顶点数目+1，且顶点从1开始连续编号（即此网络的顶点编号为1-379）
#define E 914  //边的数目

const int Num_Test = (int)(0.1*E + V * (V - 1) / 2 - E);

#define Times_AUC 1000//AUC方法中比较次数
#define Times_Devision 50
#define Num_Precision 100

class LNB
{

public:
    static double s;
	static void InitializeTestSet(int p[][V], int t[][2]);
	static void show(int p[][V]);
	static void show(int p[][2], int num);
	static void show(double p[][3], int num);
	static void LoadData(int p[][V], string address);
	static void StraightInsertionSort(double p[][3], int num_test);
	static int GetNumNo0(int p[][V], int row = -1);
	static void MatrixRecover(int p[][V]);
	static int Get_Oxy(int p[][V], int k[], int x, int y);
	static double Get_s(int p[][V]);
	static int Get_Nw(int p[][V], int w);
	static double Get_Rw(int p[][V], int w);
	static double r_LNB_CN(int p[][V], int x, int y);
	static double r_LNB_AA(int p[][V], int x, int y);
	static double r_LNB_RA(int p[][V], int x, int y);
	static double r_CN(int p[][V], int x, int y);
	static double r_AA(int p[][V], int x, int y);
	static double r_RA(int p[][V], int x, int y);
	static void Get_Rank(int p[][V], int t[][2], double rank[][3], double(*r)(int(*)[V], int, int));
	static double Get_AUC(int p[][V], double rank[][3]);
	static double Get_precision(int p[][V], double rank[][3]);
};
double LNB::s = 0;

void LNB::LoadData(int p[][V], string address)
{
	ifstream infile;   //输入流
	int v, w;

	srand((unsigned int)(time(NULL)));
	infile.open("C:\\Users\\冯准生\\source\\repos\\LocalNaiveBayes\\" + address, ios::in);
	if (!infile.is_open())
		cout << "文件名输入错误" << endl;
	while (!infile.eof())            // 若未到文件结束一直循环 
	{
		infile >> v >> w;
		p[v][w] = 1;
		p[w][v] = 1;
	}
	infile.close();   //关闭文件
}

void LNB::InitializeTestSet(int p[][V], int t[][2])
{
	int i, j, k = 0;
	int num_row;
	int random;

	while (k < E * 0.1)
		for (i = 1; i <= V - 1; i++)
			for (j = i + 1; j <= V - 1; j++)
			{
				random = rand() % 100;
				if (p[i][j] == 1 && random < 10 && k < E*0.1)
				{
					t[k][0] = i;
					t[k][1] = j;
					p[i][j] = -1;
					p[j][i] = -1;
					k++;
					//cout << "after:"<<random << endl;
				}
				else if (k >= E * 0.1)break;
			}
	//cout << "first:" << k << endl;

	for (i = 1; i <= V - 1; i++)
	{
		num_row = 0;
		for (j = 1; j <= V - 1; j++)
		{
			if (p[i][j] == 1)
				num_row++;
			if (((p[i][j] < -1) || (p[i][j] == 0)) && j > i && k < Num_Test)
			{
				t[k][0] = i;
				t[k][1] = j;
				p[i][j] = 0;
				k++;
			}
			else if (p[i][j] < -1 && j <= i)
				p[i][j] = 0;
		}
		p[i][0] = num_row;
	}

	//cout <<"second:"<< k<<endl;

	LNB::s = LNB::Get_s(p);
}

double LNB::Get_precision(int p[][V], double rank[][3])
{
	int i, j = 0, m, x, y, num = 0;
	double precision_scores = 0;

	//把rank中得分为10以下的边筛出去，提高排序速度
	double(*Not0rank)[3] = new double[Num_Test][3];
	for (i = 0; i <= Num_Test; i++)
		if (rank[i][2] > 0)
		{
			for (m = 0; m <= 2; m++)
				Not0rank[j][m] = rank[i][m];
			j++;
		}

	LNB::StraightInsertionSort(Not0rank, j);
	//LNB::show(Not0rank, j);

	for (i = 0; i <= Num_Precision - 1; i++)
	{
		x = Not0rank[i][0];
		y = Not0rank[i][1];
		if (p[x][y] == -1)
			precision_scores++;
	}
	precision_scores /= Num_Precision;

	delete Not0rank;
	return precision_scores;
}

//p为全集，times为AUC比较次数
double LNB::Get_AUC(int p[][V], double rank[][3])
{
	int i, j, k, x, y;
	int n1 = 0, n2 = 0;
	double n1_scores, n2_scores;
	double AUC_scores;
	//double num = 0;

	for (k = 0; k <= Times_AUC - 1; k++)
	{
		do {
			i = rand() % ((int)(E*0.1) + 1);
			x = rank[i][0];
			y = rank[i][1];
		} while (p[x][y] != -1);
		//cout << "i:" << i << " ";
		//cout << "x:" << x << "  y:" << y << "  n1_scores:" << rank[i][2] << endl;
		n1_scores = rank[i][2];

		do {
			j = rand() % Num_Test;
			x = rank[j][0];
			y = rank[j][1];
		} while (p[x][y] != 0);
		//cout << "j:" << j << " ";
		//cout << "x:" << x << "  y:" << y << " n2_scores:" << rank[j][2] << endl;
		n2_scores = rank[j][2];

		if (n1_scores > n2_scores)
			n1++;
		else if (n1_scores == n2_scores)
			n2++;
		//cout << "n1:" << n1 << " n2:" << n2 << " k:" << k << endl;
	}
	AUC_scores = (1.0*n1 + 0.5*n2) / (1.0*Times_AUC);

	return AUC_scores;
}

double LNB::Get_Rw(int p[][V], int w)
{
	int k = p[w][0];
	int Nw = Get_Nw(p, w);
	int N0w = k * (k - 1) / 2 - Nw;
	return (Nw + 1.0) / (N0w + 1.0);
}

//返回以w为共同邻居的已连接的节点对个数
int LNB::Get_Nw(int p[][V], int w)
{
	int i, j, k = 0;
	int num = p[w][0];//与w相连的结点个数
	int num_pairs = 0;//以w为共同邻居的已连接的节点对个数
	int cn[V];//储存与w相连的结点

	for (j = 1; j <= V - 1; j++)
		if (p[w][j] == 1)
			cn[k++] = j;

	for (i = 0; i <= num - 2; i++)
		for (j = i + 1; j <= num - 1; j++)
			if (p[cn[i]][cn[j]] == 1)
				num_pairs++;

	return num_pairs;
}

double LNB::Get_s(int p[][V])
{
	double s;
	int M = (V - 1) * (V - 2) / 2;
	int MT = GetNumNo0(p);
	s = M * 1.0 / MT * 1.0 - 1.0;

	return s;
}

//数组k包含结点x和y的共同邻居，返回值为共同邻居个数
int LNB::Get_Oxy(int p[][V], int k[], int x, int y)
{
	int  j, l = 0;
	int num = 0;

	for (j = 1; j <= V - 1; j++)
	{
		if (p[x][j] == 1 && p[y][j] == 1)
		{
			num++;
			k[l++] = j;
		}
	}
	return num;
}

//恢复矩阵
void LNB::MatrixRecover(int p[][V])
{
	int i, j;
	for (i = 0; i <= V - 1; i++)
		for (j = 0; j <= V - 1; j++)
		{
			if (j == 0)
				p[i][j] = 0;
			if (p[i][j] == -1)
				p[i][j] = 1;
		}
}

//返回非零元素的个数，若设置row则返回某一行的，否则返回整个矩阵的
int LNB::GetNumNo0(int p[][V], int row)
{
	int i, j;
	int num = 0;
	if (row == -1)
	{
		for (i = 1; i <= V - 1; i++)
			for (j = 1; j <= V - 1; j++)
			{
				if (p[i][j] == 1)
					num++;
			}
		num /= 2;
	}
	else
		for (j = 1; j <= V - 1; j++)
			if (p[row][j] == 1)
				num++;
	return num;
}

//按行按列输出输出p
void LNB::show(int p[][V])
{
	int i, j;
	for (i = 1; i <= V - 1; i++)
	{
		for (j = 1; j <= V - 1; j++)
			cout << p[i][j] << " ";
		cout << endl;
	}
}

void LNB::show(int p[][2], int num)
{
	int i, j;
	for (i = 0; i <= num - 1; i++)
	{

		for (j = 0; j <= 1; j++)
			cout << p[i][j] << " ";
		cout << endl;
	}
}

void LNB::show(double p[][3], int num)
{
	int i, j;
	for (i = 0; i <= num - 1; i++)
	{
		for (j = 0; j <= 2; j++)
			cout << p[i][j] << " ";
		cout << endl;
	}
}

//rank储存测试集中的节点对，按得分降序排列，第二维第三个元素为分数
//r为函数指针，输入LNB_CN,LNB_AA,LNB_RA,CN,AA,RA,即可调用对应方法
void LNB::Get_Rank(int p[][V], int t[][2], double rank[][3], double(*r)(int(*)[V], int, int))
{
	int i;
	for (i = 0; i <= Num_Test - 1; i++)
	{
		if (t[i][0] > 0)//t数组中有些位置未赋值
		{
			rank[i][0] = t[i][0];
			rank[i][1] = t[i][1];
			rank[i][2] = r(p, t[i][0], t[i][1]);
		}
	}
	//LNB::StraightInsertionSort(rank, Num_Test);
}

double LNB::r_CN(int p[][V], int x, int y)
{
	int h[V / 2];
	return Get_Oxy(p, h, x, y);
}

double LNB::r_AA(int p[][V], int x, int y)
{
	int h[V / 2];
	int i, kw, Oxy;
	double r;

	r = 0;
	Oxy = Get_Oxy(p, h, x, y);
	for (i = 0; i <= Oxy - 1; i++)
	{
		kw = p[h[i]][0];
		r += 1.0 / log(kw);
	}

	return r;
}

double LNB::r_RA(int p[][V], int x, int y)
{
	int h[V / 2];
	int i, kw, Oxy;
	double r;

	r = 0;
	Oxy = Get_Oxy(p, h, x, y);
	//cout << " x:" << x << " y:" << y << endl;
	for (i = 0; i <= Oxy - 1; i++)
	{
		kw = p[h[i]][0];
		r += 1.0 / kw;
		//cout << kw << "  ";
	}
	//cout << " Oxy:" << Oxy << " r:" << r << endl;
	return r;
}

double LNB::r_LNB_CN(int p[][V], int x, int y)
{
	int Oxy, i;
	double s, r, Rw;
	int h[V / 2];//储存x和y的共同邻居

	s = LNB::s;
	Oxy = Get_Oxy(p, h, x, y);
	r = Oxy * log(s);
	//cout << " x:" << x << " y:" << y<<endl;
	for (i = 0; i <= Oxy - 1; i++)
	{
		Rw = Get_Rw(p, h[i]);
		r += log(Rw);
		//cout << Rw << "  ";
	}
	//cout << " Oxy:" << Oxy << " r:" << r<<endl;
	return r;
}

double LNB::r_LNB_AA(int p[][V], int x, int y)
{
	int Oxy, i, kw;
	double s, r, Rw;
	int h[V / 2];//储存x和y的共同邻居

	s = LNB::s;
	Oxy = Get_Oxy(p, h, x, y);
	r = 0;
	for (i = 0; i <= Oxy - 1; i++)
	{
		kw = p[h[i]][0];
		Rw = Get_Rw(p, h[i]);
		r += (log(s) + log(Rw)) / log(kw);
	}

	return r;
}

double LNB::r_LNB_RA(int p[][V], int x, int y)
{
	int Oxy, i, kw;
	double s, r, Rw;
	int h[V / 2];//储存x和y的共同邻居

	s = LNB::s;
	Oxy = Get_Oxy(p, h, x, y);
	r = 0;
	for (i = 0; i <= Oxy - 1; i++)
	{
		kw = p[h[i]][0];
		Rw = Get_Rw(p, h[i]);
		r += (log(s) + log(Rw)) / kw;
	}

	return r;
}

//直接插入排序,num_test为数组一维长度
void LNB::StraightInsertionSort(double p[][3], int num_test)
{
	int i, j, k;
	double temp[3];
	for (i = 1; i <= num_test - 1; i++)
	{
		j = i - 1;
		for (k = 0; k <= 2; k++)
			temp[k] = p[i][k];
		while (p[j][2] < temp[2] && j >= 0)
		{
			for (k = 0; k <= 2; k++)
				p[j + 1][k] = p[j][k];
			j--;
		}
		for (k = 0; k <= 2; k++)
			p[j + 1][k] = temp[k];
	}
}
int main()
{
	//srand不要用在循环里，就在函数开头调用一下就好了，不然会使rand使用相同的种子，产生相同的随机数列
	srand((unsigned int)(time(NULL)));

	int(*p)[V] = new int[V][V];
	int(*t)[2] = new int[Num_Test][2];
	double(*rank)[3] = new double[Num_Test][3];
	double(*rank1)[3] = new double[Num_Test][3];

	double final_scores = 0;

	string address = "netscience.txt";
	LNB::LoadData(p, address);
	for (int i = 0; i <= Times_Devision - 1; i++)
	{
		LNB::InitializeTestSet(p, t);
		//LNB::show(t, 92);
		LNB::Get_Rank(p, t, rank1, LNB::r_CN);
		//LNB::show(rank1, 20);
		LNB::Get_Rank(p, t, rank, LNB::r_LNB_CN);
		//LNB::show(rank, 20);

		//system("pause");
		double scores1 = LNB::Get_AUC(p, rank1);
		double scores = LNB::Get_AUC(p, rank);

		cout << "r:" << scores1 << "    ";
		cout << "r_LNB:" << scores <<endl;
		//system("pause");

		final_scores += scores;
		LNB::MatrixRecover(p);
	}
	final_scores /= Times_Devision;
	cout << final_scores<<endl;

	system("pause");
}
