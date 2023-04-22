#include"ACLLib-master/src/acllib.h"
#include<iostream>
using namespace std;
#include <time.h>
#include<stdio.h>

//���嵥λ���صı߳�
#define step 20
//��Ϸ����߶�
#define boundaryH 28
//��Ϸ�������
#define boundaryW 14
//����˹������״������Ŀ��������ת��ģ�
#define Max_Shape 19

//�������Ѿ����ڵ����ݣ���Ҫ�����ڴ���Ѿ����µĶ���˹�������Ϣ��
int WINDOW[boundaryH][boundaryW] = { 0 };

//��ת������/���ƶ��������ı�־
bool isTransform = false;
bool isToLeft = false;
bool isToRight = false;
bool Is_over = false;

//����˹������״���num����Ҫȫ�ֱ��������ڿ��Ƽ�¼�ƶ����α��Լ��߽��Ƿ���ײ�� �� ���ڼ�¼��ʱ������cnt
int num = 0, cnt = 0;
//���ڼ�¼�÷�
int score = 0;
//���ڿ��Ʒ����½����ٶ�
int speed = 8;
//λ����Ϣ�ṹ��
class Position
{
public:
	int y, x;
};

//��״��Ϣ�ṹ��
class Shape
{
public:
	int shape[4][4];
	int next;
};

//ÿ����״�ı�׼����ı�ţ����ڳ�ʼ�������������˹����ʹ��
int seq[7] = { 0,2,6,10,12,14,15 };

//ÿ������˹������״��ͼ�����ݣ�������ת��ģ�����4*4��ά�����ʾ�������������ɣ���ֱ���Թ�
Shape SHAPE[19]= {
	//l
	{
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,1
	}
	,
	//һ
{
	0,0,0,0,
	0,0,0,0,
	1,1,1,1,
	0,0,0,0,0
}
//L
,{
	0,0,0,0,
	1,0,0,0,
	1,0,0,0,
	1,1,0,0,3

}
,
{
	0,0,0,0,
	1,1,1,0,
	1,0,0,0,
	0,0,0,0,4
}

,{
	0,0,0,0,
	1,1,0,0,
	0,1,0,0,
	0,1,0,0,5

}
,
{
	0,0,0,0,
	0,0,1,0,
	1,1,1,0,
	0,0,0,0,2
}
//rL
,{
	0,0,0,0,
	0,1,0,0,
	0,1,0,0,
	1,1,0,0,7

}
,
{
	0,0,0,0,
	1,0,0,0,
	1,1,1,0,
	0,0,0,0,8

}

,{
	0,0,0,0,
	1,1,0,0,
	1,0,0,0,
	1,0,0,0,9

}

,
{
	0,0,0,0,
	1,1,1,0,
	0,0,1,0,
	0,0,0,0,6
}
//Z
,
{
	0,0,0,0,
	0,1,0,0,
	1,1,0,0,
	1,0,0,0,11
}
,
{
	0,0,0,0,
	1,1,0,0,
	0,1,1,0,
	0,0,0,0,10
}
,
//rZ
{
	0,0,0,0,
	0,1,1,0,
	1,1,0,0,
	0,0,0,0,13
}
,
{
	0,0,0,0,
	1,0,0,0,
	1,1,0,0,
	0,1,0,0,12
}
,
//��
{
	0, 0, 0, 0,
	1, 1, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,14
}
,
//T
{
	0, 0, 0, 0,
	0, 1, 0, 0,
	1, 1, 1, 0,
	0, 0, 0, 0,16
}
,
{
	0,0,0,0,
	1,0,0,0,
	1,1,0,0,
	1,0,0,0,17
}
,
{
	0, 0, 0, 0,
	1, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,18
}
,
{
	0,0, 0, 0,
	0,1, 0, 0,
	1,1, 0, 0,
	0,1, 0, 0,15
}
};
//��ǰ�����˶��Ķ���˹�����λ�ñ���posi,(��Ҫȫ�ֱ��������ڿ��Ƽ�¼�����ƶ����Ƿ���ײ��4*4���������Ͻǵ�λ��)
Position posi;

//����˹�������ɺ���
void initCube();
//��ʱ���ж�
void timeEvent(int tid);
//�����ж�
void keyEvent(int key, int event);
//����߻�����Ϣ��
void Info_Column();

int Setup()
{
	//���ɴ���
	initWindow("Russia_Cube", DEFAULT, DEFAULT, (boundaryW+20) * step, boundaryH * step);
	
	initCube();
	//ע�ᶨʱ���ж�
	registerTimerEvent(timeEvent);
	//ע������ж�
	registerKeyboardEvent(keyEvent);
	//������ʱ����50ms
	startTimer(0, 50);
	return 0;
}

void initCube() {
	//�����ʼλ�ã���Ϸ������е㴦
	//	posi = { 0,(boundaryW+5)/2 };
	posi.y = 0;
	posi.x = boundaryW / 2 - 1;
	
	//srand����������ӣ�rand���������
	srand((unsigned)time(NULL));
	num = seq[rand() % 7];
}
//��ʱ��ÿ�ж�һ���ػ�һ����Ϸ���壬��ÿ50ms�ػ�һ��
void picture_a_Cube() {
	beginPaint();
	//����
	clearDevice();
	//���廭�ʻ�ˢΪ��ɫ
	setPenColor(BLUE);
	setBrushColor(RED);

	//����Ϣ��
	Info_Column();
	//��WINDOW�ڴ��ڵĲ��һ�δ�����Ķ���˹���黭��
	for (int i = 0; i < boundaryH; i++) {
		for (int j = 0; j < boundaryW; j++) {
			if (WINDOW[i][j])rectangle(j * step, i * step, (j + 1) * step, (i + 1) * step);
		}
	}
	//��ת
	if (isTransform) {
		isTransform = false;
		//temp���ڴ洢ԭ������״
		int temp = num;
		num = SHAPE[num].next;
		//�ж��Ƿ���Խ�����ת�������ת�����ԭWINDOW�ڴ������ݳ�ͻ����
		bool isReach = false;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (SHAPE[num].shape[i][j]) {
					if (posi.y + i + 1 >= boundaryH || posi.x+j+1>boundaryW || WINDOW[posi.y + i + 1][posi.x + j]) {
						isReach = true;
						break;
					}
				}
			}
		if (isReach) num = temp; //����
	}
	//����
	if (isToLeft) {
		isToLeft = false;
		bool isReach = false;
		//�ж����ƺ��Ƿ��ͻ
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (SHAPE[num].shape[i][j]) {
					if (posi.x + j - 1 < 0 || WINDOW[posi.y + i][posi.x + j - 1]) {
						isReach = true;
						break;
					}
				}
			}
		if (!isReach) posi.x--;

	}
	//����
	if (isToRight) {
		isToRight = false;
		bool isReach = false;
		//�ж��Ƿ��ͻ
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (SHAPE[num].shape[i][j]) {
					if (posi.x + j + 1 >= boundaryW || WINDOW[posi.y + i][posi.x + j + 1]) {
						isReach = true;
						break;
					}
				}
			}
		if (!isReach) posi.x++;
	}
	//��������˹����ͼ��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (SHAPE[num].shape[i][j]) {
				rectangle((posi.x + j) * step, (posi.y + i) * step, (posi.x + j + 1) * step, (posi.y + i + 1) * step);
			}
		}
	}
	//�ж�WINDOW�����Ƿ����ĳһ�ж����ڷ��飬��������������У�����֮�ϵ���������һ��
	for (int i = 0; i<boundaryH; i++)
	{
		int count = 0;
		for (int j = 0; j < boundaryW; j++) {
			if (!WINDOW[i][j])break;
			count++;
		}
		if (count == boundaryW) {
			for (int k = i - 1; k >= 0; k--) {
				for (int j = 0; j < boundaryW; j++) {
					WINDOW[k + 1][j] = WINDOW[k][j];
				}
			}
			for (int j = 0; j < boundaryW; j++) WINDOW[0][j] = 0;
			score++;
		}
	}
	//�ж���Ϸ�Ƿ����
	for (int i = 0; i < boundaryW; i++)
	{
		if (WINDOW[4][i] == 1)
		{
			Is_over = true;
			break;
		}
	}
	if (Is_over)
	{
		setTextBkColor(BLACK);
		setTextColor(RED);
		setTextSize(40);
		char Str9[20] = "GAME OVER!!!";
		paintText(1 * step, 4 * step, Str9);

	}
	endPaint();
}
void timeEvent(int tid) {
	cnt++;
	if (Is_over)
	{
		Sleep(10000);
		exit(-1);
	}
	if (speed >= 12)
	{
		speed = 12;
	}
	else if (speed <= 1)
	{
		speed = 1;
	}
	//ÿ��50*speed ms�½�һ����λ
	if (cnt >= speed) {
		cnt = 0;
		bool isReach = true;
		//�ж��Ƿ�����½�
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (SHAPE[num].shape[i][j]) {
					if (posi.y + i + 1 >= boundaryH || WINDOW[posi.y + i + 1][posi.x + j]) {
						isReach = false;
						break;
					}
				}
			}
		if (isReach) posi.y++;
		else { //�������/�ϰ���
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++) {
					if (SHAPE[num].shape[i][j]) {
						WINDOW[posi.y + i][posi.x + j] = 1;
					}
				}
			initCube();
		}
	}
	//�ػ���Ϸ����
	picture_a_Cube();
}
void keyEvent(int key, int event) {
	//�α�
	if (key == VK_UP) {
		if (event == KEY_UP) {
			isTransform = true;
		}
	}
	//����
	if (key == VK_LEFT) {
		if (event == KEY_UP) {
			isToLeft = true;
		}
	}
	//����
	if (key == VK_RIGHT) {
		if (event == KEY_UP) {
			isToRight = true;
		}
	}
	//�����½���50ms��Ϊ10ms
	if (key == VK_DOWN) {
		if (event == KEY_DOWN) {
			startTimer(0, 10);
		}
		else if (event == KEY_UP) {
			startTimer(0, 50);
		}
	}
	if (key == VK_CONTROL)
	{
		if (event == KEY_UP)
		{
			speed++;
		}
	}
	if (key == VK_SPACE)
	{
		if (event == KEY_UP)
		{
			speed--;
		}
	}
}
void Info_Column()
{
	setPenColor(YELLOW);
	for (int i = 0; i <= boundaryW; i++)
	{
		line(i*step, 4*step, i*step, boundaryH*step);
	}
	line(0, 4 * step, boundaryW*step, 4 * step);
	//�÷����Ѷ�
	setTextBkColor(BLACK);
	setTextColor(WHITE);
	setTextSize(30);
	char Str1[20] = "�÷֣�    ";
	char Str2[20];
	char Str11[20] = "�Ѷȣ�    ";
	char Str12[20];
	sprintf_s(Str2, "%d", score);
	sprintf_s(Str12, "%d", 13-speed);
	paintText((boundaryW + 3)*step, 16 * step, Str1);
	paintText((boundaryW + 8)*step, 16 * step, Str2);
	paintText((boundaryW + 3)*step, 14 * step, Str11);
	paintText((boundaryW + 8)*step, 14 * step, Str12);

	//����˵��
	setTextBkColor(BLACK);
	setTextColor(YELLOW);
	setTextSize(20);
	char Str3[40] = "*******************************";
	paintText((boundaryW + 1)*step, 2 * step, Str3);
	char Str4[40] = "**     KEY_LEFT    ����      **";
	paintText((boundaryW + 1)*step, 3 * step, Str4);
	char Str5[40] = "**     KEY_RIHET   ����      **";
	paintText((boundaryW + 1)*step, 4 * step, Str5);
	char Str6[40] = "**     KEY_DOWN    ���¼���  **";
	paintText((boundaryW + 1)*step, 5 * step, Str6);
	char Str7[40] = "**     KEY_UP      ��ת      **";
	paintText((boundaryW + 1)*step, 6 * step, Str7);
	char Str8[40] = "**     KEY_CONTROL �Ѷȼ���  **";
	paintText((boundaryW + 1)*step, 7 * step, Str8);
	char Str9[40] = "**     KEY_SPACE   �Ѷ�����  **";
	paintText((boundaryW + 1)*step, 8 * step, Str9);
	char Str10[40] = "*******************************";
	paintText((boundaryW + 1)*step, 9 * step, Str10);
}