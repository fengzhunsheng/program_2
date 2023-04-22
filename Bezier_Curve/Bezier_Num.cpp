#include <gl/glut.h>
#include <math.h>
#include <Windows.h>
#include<iostream>
using namespace std;

int fac(int n, int m);
//����һ������࣬���ڴ洢���е������
class Point
{
public:
	int x, y;
	void setxy(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};
int CLEAR_NUM = 0;
//��ǰ����±�
static int PointNum = 0;
//����������
const int POINTMAX = 20;
//�����û�����Ŀ��Ƶ���
int POINTNUM = 2;
//���ڴ洢��ļ���,��Ϊ���ƵĶ���4����ı��������ߣ����������СΪ4
static Point points[POINTMAX];
int a[POINTMAX], b[POINTMAX], c[POINTMAX];

//��ʼ������
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0); //�趨����Ϊ��ɫ
	glColor3f(0.0, 0.0, 0.0); //��ͼ��ɫΪ��ɫ
	glPointSize(4.0); //�趨��Ĵ�СΪ2*2���ص�
	glMatrixMode(GL_PROJECTION); // �趨���ʵľ���
	glLoadIdentity(); // ��һ���޲ε���ֵ�������书������һ��4��4�ĵ�λ�������滻��ǰ����
					  //ʵ���Ͼ��ǶԵ�ǰ������г�ʼ����Ҳ����˵��
					  //������ǰ�����˶��ٴξ���任���ڸ�����ִ�к󣬵�ǰ������ָ���һ����λ����
					  //���൱��û�н����κξ���任״̬
	gluOrtho2D(0.0, 600.0, 0.0, 480.0); //ƽ��ͶӰ���ĸ������ֱ���x,y��Χ
}

//���Ƶ�
void setPoint(Point p) {
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
	glFlush();
}

// ����ֱ��
void setline(Point p1, Point p2) {
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
	glFlush();
}

// ��ⱴ���������ϵĵ�����
Point setBezier(double t) {
	Point p;
	p.x = 0;
	p.y = 0;
	for (int i = 0; i < POINTNUM; i++)
	{
		a[i] = fac(POINTNUM - 1, i);
		b[i] = POINTNUM - 1 - i;
		c[i] = i;
	}
	for (int i = 0; i < POINTNUM; i++)
	{
		p.x += a[i] * pow(1 - t, b[i])*pow(t, c[i])*points[i].x;
		p.y += a[i] * pow(1 - t, b[i])*pow(t, c[i])*points[i].y;
	}
	return p;
}

//display����
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

// ����¼�
void mymouseFunction(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) // �����갴�£����������Ҽ���
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		if (CLEAR_NUM == 1)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			CLEAR_NUM =0;
		}
		points[PointNum].setxy(x, 480 - y); // ����������������ʱ��
											 // ���õ����ɫ�����Ƶ�
		glColor3f(1.0, 0.0, 0.0);
		setPoint(points[PointNum]);
		// �����ߵ���ɫ��������
		glColor3f(1.0, 0.0, 0.0);
		if (PointNum > 0) setline(points[PointNum - 1], points[PointNum]);

		//����ﵽ��POINTNUM������Ʊ��������ߣ�����֮�������������
		if (PointNum >= POINTNUM-1) //��>��������Ϊ�û������뼸�����ͻȻ��С���Ƶ����Ŀ
		{	                        //��ʱ�ܹ�������ǰPOINTNUM���������Ƶı���������
			//���Ʊ���������   
			glColor3f(0.0, 0.0, 1.0); // �趨���������ߵ���ɫ

			Point p_current = points[0]; //��Ϊ���
			for (double t = 0.0; t <= 1.0; t += 0.04)
			{
				Point P = setBezier(t);
				setline(p_current, P);
				p_current = P;
			}
			PointNum = 0;
		}
		else PointNum++;
	}
}
void MyKeyFunction(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		POINTNUM++;
		if (POINTNUM > 20)POINTNUM = 20;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		POINTNUM--;
		if (POINTNUM < 2)POINTNUM = 2;
	}
	else if (key == GLUT_KEY_F1)
	{
		CLEAR_NUM = 1;
	}
		
	system("cls");
	cout << "************************************" << endl;
	cout << "**  KEY_UP    ���ӿ��Ƶ����      **" << endl;
	cout << "**  KEY_DOWN  ���ӿ��Ƶ����      **" << endl;
	cout << "**  KEY_F1    ��һ�λ���ʱ��ս���**" << endl;
	cout << "************************************" << endl;
	cout << "��ĸ�����" << POINTNUM << endl;
}

int main(int argc, char *argv[])
{
	cout << "************************************" << endl;
	cout << "**  KEY_UP    ���ӿ��Ƶ����      **" << endl;
	cout << "**  KEY_DOWN  ���ӿ��Ƶ����      **" << endl;
	cout << "**  KEY_F1    ��һ�λ���ʱ��ս���**" << endl;
	cout << "************************************" << endl;
	cout << "��ĸ�����" << POINTNUM << endl;
	glutInit(&argc, argv); //�̶���ʽ
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //����ģʽ
	glutInitWindowSize(600, 480);    //��ʾ��Ĵ�С
	glutInitWindowPosition(400, 100); //ȷ����ʾ�����Ͻǵ�λ��
	glutCreateWindow("Bezier Curve");//��������

	init(); // ��ʼ��
	glutMouseFunc(mymouseFunction); // �������¼�
	glutSpecialFunc(MyKeyFunction);//
	glutDisplayFunc(display); // ִ����ʾ   
	glutMainLoop(); //����GLUT�¼�����ѭ��
	return 0;
}
//�����ʽC(n,m)
int fac(int n, int m)
{
	int a1=1, a2=1, a3;
	int i;
	for (i = n-m+1; i <= n; i++)
	{
		a1 *= i;
	}
	for (i = 1; i <= m; i++)
	{
		a2 *= i;
	}
	a3 = a1 / a2;
	return a3;
}