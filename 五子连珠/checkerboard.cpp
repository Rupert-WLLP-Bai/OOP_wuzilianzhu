#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<Windows.h>
#include"checkerboard.h"
#define START_NUM 7
#define COLOR_NUM 7
const int INF = 0x3f3f3f3f;
using namespace std;
typedef pair<int, int>P;

/*�����������*/
void Checkerboard::show()
{
	cout << "    1 2 3 4 5 6 7 8 9" << endl<<endl;
	for (int i = 0; i < 9; i++)
	{
		cout << i + 1 << "   ";
		for (int j = 0; j < 9; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout<<"�÷�Ϊ: "<<score << endl;
	cout << "���������Ϊ" << num_of_blank() << endl;
	cout << endl;
}

/*������̵ĳ�ʼ��*/
void Checkerboard::spawn(int a[9][9])
{
	srand((unsigned int)time(NULL));

	int block[9][9];
	int k = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			block[i][j] = k;
		}
	}

	int num = 0;
	int color = 0;
	while (num < START_NUM)
	{
		int row = rand() % 9;
		int column = rand() % 9;
		if (a[row][column] == 0)
		{
			color = rand() % COLOR_NUM + 1;
			a[row][column] = color;
			num++;
		}
		else
			continue;
	}

}

/*������̿հ���*/
int Checkerboard::num_of_blank()
{
	int num = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (a[i][j] == 0)
				num++;
		}
	}
	return num;
}

bool Checkerboard::game_over()
{
	int num = num_of_blank();
	if (num <= 3)
		return true;
	else
		return false;
}

void Checkerboard::fetch_instruction(int* location)
{
	while (1)//������ʼ��ֹ����
	{
		re:
		system("cls");
		show();
		cout << "������ʼ���� " << endl;
		cin >> location[0];
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536,'\n');
			cout << "��������,��������" << endl;
			Sleep(1000);
			continue;
		}
		cin >> location[1];
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536,'\n');
			cout << "��������,��������" << endl;
			Sleep(1000);
			continue;
		}
		cout << "������ֹ���� " << endl;
		cin >> location[2];
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536,'\n');
			cout << "��������,��������" << endl;
			Sleep(1000);
			continue;
		}
		cin >> location[3];
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(65536,'\n');
			cout << "��������,��������" << endl;
			Sleep(1000);
			continue;
		}
		break;
	}
	int flag = check_range(location[0]-1, location[1]-1, location[2]-1, location[3]-1);
	if (flag == false)
	{
		cout << "�ƶ���Ч,��������" << endl;
		Sleep(1000);
		goto re;
	}
}

int Checkerboard::get_color(int x, int y)
{
	return a[x-1][y-1];
}

/*�ƶ�*/
void Checkerboard::move(int location[4],int* color_end, int* effect)
{
		a[location[2]-1][location[3]-1] = a[location[0]-1][location[1]-1];
		a[location[0]-1][location[1]-1] = 0;
		*effect = 1;
}

void Checkerboard::move(int location[4])
{
	a[location[2] - 1][location[3] - 1] = a[location[0] - 1][location[1] - 1];
	a[location[0] - 1][location[1] - 1] = 0;
}

void Checkerboard::add(int flag)
{
	if (flag == 1)
		return;
	srand((unsigned int)time(0));
	int x, y;//����
	int newpoint[3][3];//����������������Ϣ	
	int i = 0;
	while (i < 3)
	{
		x = rand() % 9;
		y = rand() % 9;
		if (a[x][y] == 0)
		{
			newpoint[0][i] = x;
			newpoint[1][i] = y;
			newpoint[2][i] = rand() % COLOR_NUM + 1;
			i++;
		}
		else
			continue;
	}

	for (int i = 0; i < 3; i++)	//��ֵ
	{
		a[newpoint[0][i]][newpoint[1][i]] = newpoint[2][i];
	}
}

bool Checkerboard::check_range(int x1, int y1, int x2, int y2)
{
	bool flag = 1;
	if (x1 < 0 || x1 > 8 || x2 < 0 || x2 > 8 || y2 < 0 || y2 > 8 || y1 < 0 || y1 > 8)//ѡ��λ�ó�����Χ
	{
		flag=0;
	}
	else
	{
		if (this->a[x1][y1] == 0)//��ʼλ��������
		{
			flag=0;
		}
		if (this->a[x2][y2] != 0)//��ֹλ��������
		{
			flag=0;
		}
	}
	return flag;
}





void Checkerboard::set(int x, int y, int color)
{
	a[x-1][y-1] = color;
}

void Checkerboard::score_add(int x)
{
	score += x;
}

int Checkerboard::get_score()
{
	return score;
}

