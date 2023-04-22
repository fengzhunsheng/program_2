#include <gl/glut.h>
#include <math.h>
#include <Windows.h>
#include<iostream>
using namespace std;

int fac(int n, int m);
//这是一个点的类，用于存储其中点的坐标
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
//当前点的下标
static int PointNum = 0;
//点的最大数量
const int POINTMAX = 20;
//接收用户定义的控制点数
int POINTNUM = 2;
//用于存储点的集合,因为绘制的都是4个点的贝塞尔曲线，所以数组大小为4
static Point points[POINTMAX];
int a[POINTMAX], b[POINTMAX], c[POINTMAX];

//初始化函数
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0); //设定背景为黑色
	glColor3f(0.0, 0.0, 0.0); //绘图颜色为白色
	glPointSize(4.0); //设定点的大小为2*2像素的
	glMatrixMode(GL_PROJECTION); // 设定合适的矩阵
	glLoadIdentity(); // 是一个无参的无值函数，其功能是用一个4×4的单位矩阵来替换当前矩阵，
					  //实际上就是对当前矩阵进行初始化。也就是说，
					  //无论以前进行了多少次矩阵变换，在该命令执行后，当前矩阵均恢复成一个单位矩阵，
					  //即相当于没有进行任何矩阵变换状态
	gluOrtho2D(0.0, 600.0, 0.0, 480.0); //平行投影，四个参数分别是x,y范围
}

//绘制点
void setPoint(Point p) {
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
	glFlush();
}

// 绘制直线
void setline(Point p1, Point p2) {
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
	glFlush();
}

// 求解贝塞尔曲线上的点坐标
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

//display函数
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

// 鼠标事件
void mymouseFunction(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) // 如果鼠标按下，不区分左右键的
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		if (CLEAR_NUM == 1)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			CLEAR_NUM =0;
		}
		points[PointNum].setxy(x, 480 - y); // 这里求鼠标点的坐标的时候
											 // 设置点的颜色，绘制点
		glColor3f(1.0, 0.0, 0.0);
		setPoint(points[PointNum]);
		// 设置线的颜色，绘制线
		glColor3f(1.0, 0.0, 0.0);
		if (PointNum > 0) setline(points[PointNum - 1], points[PointNum]);

		//如果达到了POINTNUM个则绘制贝塞尔曲线，并在之后给计数器清零
		if (PointNum >= POINTNUM-1) //“>”的意义为用户在输入几个点后，突然减小控制点的数目
		{	                        //此时能够画出当前POINTNUM个点所控制的贝塞尔曲线
			//绘制贝塞尔曲线   
			glColor3f(0.0, 0.0, 1.0); // 设定贝塞尔曲线的颜色

			Point p_current = points[0]; //设为起点
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
	cout << "**  KEY_UP    增加控制点个数      **" << endl;
	cout << "**  KEY_DOWN  增加控制点个数      **" << endl;
	cout << "**  KEY_F1    下一次画点时清空界面**" << endl;
	cout << "************************************" << endl;
	cout << "点的个数：" << POINTNUM << endl;
}

int main(int argc, char *argv[])
{
	cout << "************************************" << endl;
	cout << "**  KEY_UP    增加控制点个数      **" << endl;
	cout << "**  KEY_DOWN  增加控制点个数      **" << endl;
	cout << "**  KEY_F1    下一次画点时清空界面**" << endl;
	cout << "************************************" << endl;
	cout << "点的个数：" << POINTNUM << endl;
	glutInit(&argc, argv); //固定格式
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //缓存模式
	glutInitWindowSize(600, 480);    //显示框的大小
	glutInitWindowPosition(400, 100); //确定显示框左上角的位置
	glutCreateWindow("Bezier Curve");//窗口名称

	init(); // 初始化
	glutMouseFunc(mymouseFunction); // 添加鼠标事件
	glutSpecialFunc(MyKeyFunction);//
	glutDisplayFunc(display); // 执行显示   
	glutMainLoop(); //进人GLUT事件处理循环
	return 0;
}
//求二项式C(n,m)
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