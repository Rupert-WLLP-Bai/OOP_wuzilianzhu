/*���ӻ�����ʵ��*/
#pragma warning(disable : 4996)
#include<graphics.h>
#include<iostream>
#include<deque>
#include"checkerboard.h"
#include<string>
#include"path.h"
#include"eliminate.h"
#include<iomanip>

#define SLEEPTIME 0
using namespace std;

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
	bool search_path_and_move();//����·�� �ƶ�
	void elinimate_and_score();
	void game_over();
	Checkerboard game;//game
private:

};

const int lattice_side_length = 70;//���ӱ߳� ��Ҫ9*9������
const int lattice_num = 9;//9*9�ĸ���
const int height_score = 70;//�·��������ĸ߶�
const int width_menu = 250;//�Ҳ�˵������
const int width = lattice_side_length * lattice_num + width_menu;
const int height = lattice_side_length * lattice_num + height_score;
const int r_bead = lattice_side_length / 2;//���Ӱ뾶Ϊ���ӱ߳���һ��
const string blank = "                                                                                 ";

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
	settextcolor(RED);//������ɫ
	setbkmode(TRANSPARENT);//����͸��
	settextstyle(20, 0, "DejaVu Sans Mono");//��������
	outtextxy(0, height - height_score, text.data());
}

inline void Visual_interface::mouse_catching()
{
	MOUSEMSG m;//��������¼�
	m = GetMouseMsg();
	int x, y;//����
	int x1, y1;//��ʼ ����
	int x2, y2;
	const char* color[] = { "�հ�","��","��" ,"��","��","��","��","��" };
	int flag1 = 0;//����Ƿ�ѡ����Ч����ʼλ��
	int	flag2 = 0; // ����Ƿ�ѡ����Ч����ֹλ��

	while (1)
	{
	start:
		if (MouseHit())//��⵽����¼�
		{
			m = GetMouseMsg();
			x = m.x / lattice_side_length + 1;
			y = m.y / lattice_side_length + 1;
			x1 = y; y1 = x;
			switch (m.uMsg)
			{
			case WM_LBUTTONDOWN: //�������
				cout << "ѡ����ʼλ��" << endl;
				cout << "��ѡ����ʼ����" << endl;
				cout << "�������Ϊ: (" << m.x << "," << m.y << ")" << endl;
				cout << "ѡ�����������Ϊ: (" << x << "," << y << ")" << endl;
				cout << "ѡ���������ɫΪ: (" << color[game.get_color(x1, y1)] << ")" << endl;
				if (x1 <= 9 && y1 <= 9 && color[game.get_color(x1, y1)] != "�հ�")
				{
					game.loc[0] = x1; game.loc[1] = y1;
					flag1 = 1;
					break;
				}
				else
				{
					cout << "��ʼλ����Ч,����ѡ��" << endl;
					break;
				}
			case WM_MOUSEMOVE://�ƶ����
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
		if (MouseHit())//��⵽����¼�
		{
			m2 = GetMouseMsg();
			x = m2.x / lattice_side_length + 1;
			y = m2.y / lattice_side_length + 1;
			x2 = y; y2 = x;
			switch (m2.uMsg)
			{
			case WM_LBUTTONDOWN: //�������
				cout << "ѡ����ֹλ��: " << endl;
				cout << "��ѡ����ֹλ��" << endl;
				cout << "�������Ϊ: (" << m2.x << "," << m2.y << ")" << endl;
				cout << "��ֹλ������Ϊ: (" << x << "," << y << ")" << endl;
				cout << "��ֹλ����ɫΪ: (" << color[game.get_color(x2, y2)] << ")" << endl;
				if (x2 <= 9 && y2 <= 9 && color[game.get_color(x2, y2)] == "�հ�")
				{
					game.loc[2] = x2; game.loc[3] = y2;
					flag2 = 1;
					break;
				}
				else
				{
					cout << "��ֹλ����Ч,�ص�ѡ����ʼ����" << endl;
					flag1 = 0;
					flag2 = 0;
					/*cout << "flag1 = " << flag1 << endl;
					cout << "flag2 = " << flag2 << endl;*/
					break;
				}
			case WM_MOUSEMOVE://�ƶ����
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
			cout << "ִ���ƶ�����" << endl;
			return;
		}
		if (flag2 == 0)
		{
			goto start;
		}
	}
}




inline bool Visual_interface::search_path_and_move()
{
	path_search route(game.loc[0] - 1, game.loc[1] - 1, game.loc[2] - 1, game.loc[3] - 1, game);
	route.searchPath(game);
	if (route.m_path_empty())//·��������
	{
		cout << "�޿���·��" << endl;
		return false;
	}
	else
	{
		int num = 0;
		path_search::Node start, end;//��ʼ�ڵ�
		start.m_x = game.loc[0]; start.m_y = game.loc[1];
		end = route.m_path.front()+path_search::Node(1,1);
		int location[4] = { start.m_x,start.m_y,end.m_x,end.m_y };
		route.m_path.pop_front();
		game.move(location);
		BeginBatchDraw();//��ֹ�س�ʱ��������
		draw_root_window();
		draw_board();
		draw_score();
		FlushBatchDraw();
		Sleep(SLEEPTIME);
		cleardevice();
		cout << "Moves: " << setw(2)<<++num <<" " << '(' << start.m_y << ','
			<< start.m_x << ')' << "����>" << '(' << end.m_y << ','
			<< end.m_x << ')' << endl;
		// pathÿpopһ�Σ�����һ������յ㣬ִ��move����ʱ�����»����̣�ֱ��pathΪ��
		while (!route.m_path.empty())//deque
		{
			start = end;
			end = route.m_path.front() + path_search::Node(1, 1);
			route.m_path.pop_front();
			int location[4] = { start.m_x,start.m_y,end.m_x,end.m_y };
			game.move(location);
			BeginBatchDraw();//��ֹ�س�ʱ��������
			draw_root_window();
			draw_board();
			draw_score();
			FlushBatchDraw();
			Sleep(SLEEPTIME);
			cleardevice();

			cout << "Moves: " << setw(2) << ++num << " " << '(' << start.m_y << ','
				<< start.m_x << ')' << "����>" << '(' << end.m_y << ','
				<< end.m_x << ')' << endl;
		}
		////һ���ƶ�
		//route.printPath();
		//game.move(game.loc);
		return true;
	}
}

inline void Visual_interface::elinimate_and_score()
{
	int flag = eliminate(&game, game.loc[2], game.loc[3]);//��ȥ���ӷ�
	game.add(flag);
}

inline void Visual_interface::game_over()
{
	if (game.num_of_blank()==0)//flag==1 ��ʾδ���� ��Ҫ������� ���֮ǰ�����ж�
	{
		int ok = MessageBox(GetHWnd(), "��Ϸ����,�����ť�˳���Ϸ", "Oops", MB_OK);
		if (ok == IDOK)
		{
			cleardevice();
			exit(-2);
		}
	}
}

inline void Visual_interface::draw_bead(int x, int y)//������������ 
{
	//const int pi = 3.14159; //���ڻ�����,��һ���õ���
	int flag = 1;
	HWND hwnd;
	hwnd = GetHWnd();
	float H, S=1, V=1;//������ɫ
	const int circle_y = x * lattice_side_length - r_bead;
	const int circle_x = y * lattice_side_length - r_bead;//Բ������
	switch (game.get_color(x, y))//��ȡ������ɫ
	{
	case 1:
		H=0;//��ɫ
		break;
	case 2:
		H=30;//��ɫ
		break;
	case 3:
		H=60;//��ɫ
		break;
	case 4:
		H=120;//��ɫ
		break;
	case 5:
		H=180;//��ɫ
		break;
	case 6:
		H=240;//��ɫ
		break;
	case 7:
		H=270;//��ɫ
		break;
	default:
		flag = 0;
		break;
	}
	if (flag)
	{
		//������(��ɫ)
		setfillcolor(HSVtoRGB(H, S, V));
		solidcircle(circle_x, circle_y, r_bead-1);
		
		//// ������(�м�ƫ��ɫ) (����) (�����ܿ�)
		//for (int i = 0; i < r_bead - 1; i++)
		//{
		//	for (int r = r_bead-1; r > 0; r--)
		//	{
		//		S-=0.45f/r_bead;	//�ı�S��ֵ
		//		setlinecolor(HSVtoRGB(H,S,V));
		//		circle(circle_x, circle_y, r);
		//	}
		//}
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
	HWND hwnd = GetHWnd();//��ȡ���ھ��
	const char* title = "��������";
	SetWindowText(hwnd, title);//�޸Ĵ��ڱ���
	IMAGE bk;//����
	const char* bk_route = "bk.png";
	loadimage(&bk, bk_route, width, height);
	putimage(0, 0, &bk);
	draw_line();//�����ָ���
}

