/*可视化界面实现*/
#include<graphics.h>
#include"checkerboard.h"

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
private:

};

const int lattice_side_length = 60;//格子边长 需要9*9的棋盘
const int lattice_num = 9;//9*9的格子
const int height_score = 60;//下方积分栏的高度
const int width_menu = 120;//右侧菜单栏宽度
const int width = lattice_side_length * lattice_num + width_menu;
const int height = lattice_side_length * lattice_num + height_score;
const int r_bead = lattice_side_length / 2;//棋子半径为格子边长的一半
static Checkerboard game;//静态全局game
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

inline void Visual_interface::draw_button()//画按钮
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
		r = 255;//紫色
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
		solidcircle(circle_x, circle_y, r_bead);
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

	initgraph(width, height);
	HWND hwnd = GetHWnd();//获取窗口句柄
	LPCWSTR title = TEXT("五子连珠");
	SetWindowText(hwnd, title);//修改窗口标题
	IMAGE bk;//背景
	loadimage(&bk, TEXT("image/bk.png"), width, height);
	putimage(0, 0, &bk);
	draw_line();//画出分隔线
}

