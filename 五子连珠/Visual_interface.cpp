/*可视化界面实现*/
#pragma warning(disable : 4996)
#include<graphics.h>
#include<iostream>
#include"checkerboard.h"
#include<string>
#include"path.h"
using namespace std;

class Visual_interface
{
public:
	Visual_interface() {};
	~Visual_interface() {};
	void draw_bead(int x, int y);//传入棋子坐标 
	void draw_board();//传入棋盘
	void draw_root_window();
	void draw_line();
	void draw_button();
	void draw_score();//显示分数
	void mouse_catching();//读取鼠标事件
	void search_path_and_move();//搜索路径 移动
	Checkerboard game;//game
private:

};

const int lattice_side_length = 70;//格子边长 需要9*9的棋盘
const int lattice_num = 9;//9*9的格子
const int height_score = 70;//下方积分栏的高度
const int width_menu = 250;//右侧菜单栏宽度
const int width = lattice_side_length * lattice_num + width_menu;
const int height = lattice_side_length * lattice_num + height_score;
const int r_bead = lattice_side_length / 2;//棋子半径为格子边长的一半
const string blank = "                                                                                 ";

/*
颜色
#define	BLACK			0
#define	BLUE			0xAA0000
#define	GREEN			0x00AA00
#define	CYAN			0xAAAA00
#define	RED				0x0000AA
#define	MAGENTA			0xAA00AA
#define	BROWN			0x0055AA
#define	LIGHTGRAY		0xAAAAAA
#define	DARKGRAY		0x555555
#define	LIGHTBLUE		0xFF5555
#define	LIGHTGREEN		0x55FF55
#define	LIGHTCYAN		0xFFFF55
#define	LIGHTRED		0x5555FF
#define	LIGHTMAGENTA	0xFF55FF
#define	YELLOW			0x55FFFF
#define	WHITE			0xFFFFFF
*/


inline void Visual_interface::draw_line()
{
	HWND hwnd = GetHWnd();
	setlinecolor(RGB(255, 127, 39));//分割线颜色设置
	for (int i = 0; i < 10; i++)//横竖线
	{
		line(0, i * lattice_side_length, width - width_menu, i * lattice_side_length);//横线
		line(i * lattice_side_length, 0, i * lattice_side_length, width - width_menu);//竖线
	}

}

inline void Visual_interface::draw_button()//画右侧按钮
{
	//退出按钮
}

inline void Visual_interface::draw_score()//得分框
{
	string text;//输出文字内容
	string text1 = "Score: ";
	string score = to_string(game.get_score());//score
	text = text1 + score;
	settextcolor(RED);//字体颜色
	setbkmode(TRANSPARENT);//背景透明
	settextstyle(20, 0, "DejaVu Sans Mono");//字体设置
	outtextxy(0, height - height_score, text.data());
}

inline void Visual_interface::mouse_catching()
{
	MOUSEMSG m;//定义鼠标事件
	m = GetMouseMsg();
	int x, y;//坐标
	int x1, y1;//起始 数组
	int x2, y2;
	const char* color[] = { "空白","红","橙" ,"黄","绿","青","蓝","紫" };
	int flag1 = 0;//检测是否选择到有效的起始位置
	int	flag2 = 0; // 检测是否选择到有效的终止位置

	while (1)
	{
	start:
		if (MouseHit())//检测到鼠标事件
		{
			m = GetMouseMsg();
			x = m.x / lattice_side_length + 1;
			y = m.y / lattice_side_length + 1;
			x1 = y; y1 = x;
			switch (m.uMsg)
			{
			case WM_LBUTTONDOWN: //按下左键
				cout << "选择起始位置" << endl;
				cout << "已选择起始棋子" << endl;
				cout << "鼠标坐标为: (" << m.x << "," << m.y << ")" << endl;
				cout << "选择的棋子坐标为: (" << x << "," << y << ")" << endl;
				cout << "选择的棋子颜色为: (" << color[game.get_color(x1, y1)] << ")" << endl;
				if (x1 <= 9 && y1 <= 9 && color[game.get_color(x1, y1)] != "空白")
				{
					game.loc[0] = x1; game.loc[1] = y1;
					flag1 = 1;
					break;
				}
				else
				{
					cout << "起始位置无效,重新选择" << endl;
					break;
				}
			case WM_MOUSEMOVE://移动鼠标
				/*cout << "move1" << endl;
				cout << "flag1 = " << flag1 << endl;
				cout << "flag2 = " << flag2 << endl;*/
				break;
			default:
				/*cout << "other1" << endl;
				cout << "flag1 = " << flag1 << endl;
				cout << "flag2 = " << flag2 << endl;*/
				break;
			}
		}
		if (flag1)
			break;
	}


	while (1)
	{
		MOUSEMSG m2;
		if (MouseHit())//检测到鼠标事件
		{
			m2 = GetMouseMsg();
			x = m2.x / lattice_side_length + 1;
			y = m2.y / lattice_side_length + 1;
			x2 = y; y2 = x;
			switch (m2.uMsg)
			{
			case WM_LBUTTONDOWN: //按下左键
				cout << "选择终止位置: " << endl;
				cout << "已选择终止位置" << endl;
				cout << "鼠标坐标为: (" << m2.x << "," << m2.y << ")" << endl;
				cout << "终止位置坐标为: (" << x << "," << y << ")" << endl;
				cout << "终止位置颜色为: (" << color[game.get_color(x2, y2)] << ")" << endl;
				if (x2 <= 9 && y2 <= 9 && color[game.get_color(x2, y2)] == "空白")
				{
					game.loc[2] = x2; game.loc[3] = y2;
					flag2 = 1;
					break;
				}
				else
				{
					cout << "终止位置无效,回到选择起始棋子" << endl;
					flag1 = 0;
					flag2 = 0;
					/*cout << "flag1 = " << flag1 << endl;
					cout << "flag2 = " << flag2 << endl;*/
					break;
				}
			case WM_MOUSEMOVE://移动鼠标
				/*cout << "move2" << endl;*/
				flag2 = -1;
				break;
			case WM_RBUTTONDOWN:
				cout << "Selection canceled." << endl;
				flag1 = 0;
				flag2 = 0;
				goto start;
			default:
				/*cout << "other2" << endl;*/
				flag2 = -1;
				break;
			}
		}
		if (flag1 == 1 && flag2 == 1)
		{
			cout << "执行移动函数" << endl;
			game.move(game.loc);
			return;
		}
		if (flag2 == 0)
		{
			goto start;
		}
	}
}




inline void Visual_interface::search_path_and_move()
{






}

inline void Visual_interface::draw_bead(int x, int y)//传入棋子坐标 
{
	//const int pi = 3.14159; //用于画渐变,不一定用得上
	int flag = 1;
	HWND hwnd;
	hwnd = GetHWnd();
	int r, g, b;//棋子颜色
	const int circle_y = x * lattice_side_length - r_bead;
	const int circle_x = y * lattice_side_length - r_bead;//圆心坐标
	switch (game.get_color(x, y))//获取棋子颜色
	{
	case 1:
		r = 255;//红色
		g = 0;
		b = 0;
		break;
	case 2:
		r = 255;//橙色
		g = 128;
		b = 0;
		break;
	case 3:
		r = 255;//黄色
		g = 255;
		b = 0;
		break;
	case 4:
		r = 0;//绿色
		g = 255;
		b = 0;
		break;
	case 5:
		r = 0;//青色
		g = 255;
		b = 255;
		break;
	case 6:
		r = 0;//蓝色
		g = 0;
		b = 255;
		break;
	case 7:
		r = 128;//紫色
		g = 0;
		b = 255;
		break;
	default:
		flag = 0;
		break;
	}
	if (flag)
	{
		setfillcolor(RGB(r, g, b));
		solidcircle(circle_x, circle_y, r_bead - 1);
	}
}

inline void Visual_interface::draw_board()
{
	for (int i = 1; i < 10; i++)
		for (int j = 1; j < 10; j++)
		{
			draw_bead(i, j);
		}
}

inline void Visual_interface::draw_root_window()
{
	HWND hwnd = GetHWnd();//获取窗口句柄
	const char* title = "五子连珠";
	SetWindowText(hwnd, title);//修改窗口标题
	IMAGE bk;//背景
	const char* bk_route = "image/bk.png";
	loadimage(&bk, bk_route, width, height);
	putimage(0, 0, &bk);
	draw_line();//画出分隔线
}

