/*���ӻ�����ʵ��*/
#include<graphics.h>
#include"checkerboard.h"
#include<string>
class Visual_interface
{
public:
	Visual_interface() {};
	~Visual_interface() {};
	void draw_bead(int x, int y);//������������ 
	void draw_board();//��������
	void draw_root_window();
	void draw_line();
	void draw_button();
	void draw_score();//��ʾ����
	void mouse_catching();//��ȡ����¼�
	Checkerboard game;//game
private:

};

const int lattice_side_length = 60;//���ӱ߳� ��Ҫ9*9������
const int lattice_num = 9;//9*9�ĸ���
const int height_score = 60;//�·��������ĸ߶�
const int width_menu = 120;//�Ҳ�˵������
const int width = lattice_side_length * lattice_num + width_menu;
const int height = lattice_side_length * lattice_num + height_score;
const int r_bead = lattice_side_length / 2;//���Ӱ뾶Ϊ���ӱ߳���һ��

/*
��ɫ
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
	setlinecolor(RGB(255, 127, 39));//�ָ�����ɫ����
	for (int i = 0; i < 10; i++)//������
	{
		line(0, i * lattice_side_length, width - width_menu, i * lattice_side_length);//����
		line(i * lattice_side_length, 0, i * lattice_side_length, width - width_menu);//����
	}

}

inline void Visual_interface::draw_button()//���Ҳఴť
{
	//�˳���ť
}

inline void Visual_interface::draw_score()//�÷ֿ�
{
	string text;//�����������
	string text1 = "Score: ";
	string score = to_string(game.get_score());//score
	text = text1 + score;
	settextcolor(GREEN);//������ɫ
	setbkmode(TRANSPARENT);//����͸��
	settextstyle(20, 0, "DejaVu Sans Mono");//��������
	outtextxy(0,height-height_score, text.data());
}

inline void Visual_interface::mouse_catching()
{
}

inline void Visual_interface::draw_bead(int x, int y)//������������ 
{
	//const int pi = 3.14159; //���ڻ�����,��һ���õ���
	int flag = 1;
	HWND hwnd;
	hwnd = GetHWnd();
	int r, g, b;//������ɫ
	const int circle_y = x * lattice_side_length - r_bead;
	const int circle_x = y * lattice_side_length - r_bead;//Բ������
	switch (game.get_color(x, y))//��ȡ������ɫ
	{
	case 1:
		r = 255;//��ɫ
		g = 0;
		b = 0;
		break;
	case 2:
		r = 255;//��ɫ
		g = 128;
		b = 0;
		break;
	case 3:
		r = 255;//��ɫ
		g = 255;
		b = 0;
		break;
	case 4:
		r = 0;//��ɫ
		g = 255;
		b = 0;
		break;
	case 5:
		r = 0;//��ɫ
		g = 255;
		b = 255;
		break;
	case 6:
		r = 0;//��ɫ
		g = 0;
		b = 255;
		break;
	case 7:
		r = 255;//��ɫ
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
		solidcircle(circle_x, circle_y, r_bead-1);
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
	HWND hwnd = GetHWnd();//��ȡ���ھ��
	const char* title = "��������";
	SetWindowText(hwnd, title);//�޸Ĵ��ڱ���
	IMAGE bk;//����
	const char* bk_route = "image/bk.png";
	loadimage(&bk, bk_route, width, height);
	putimage(0, 0, &bk);
	draw_line();//�����ָ���
}

