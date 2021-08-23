#pragma once
/*checkerboard.h	�������*/
#include<queue>
using namespace std;
typedef pair<int, int>P;
class Checkerboard
{
public:
	Checkerboard();
	~Checkerboard();
	void score_add(int x);//�ӷ�
	int get_score();//��ʾ����
	void set(int x, int y, int color);//��ֵ
	void show();	//�����������
	void spawn(int a[9][9]);//��ʼ������
	int num_of_blank();//������̿հ���
	bool game_over();//�����Ϸ�Ƿ����	 true:���� false:����
	void fetch_instruction(int* location);//���̻�ȡ����
	int get_color(int x, int y);//��ȡ������ɫ
	void move(int location[4],int *color_end,int *effect);//�ƶ� ��Ҫ���ص�ֵΪ�յ����� �յ�������ɫ �Ƿ�����ƶ�
	void add(int flag);//�������
	bool check_range(int x1, int y1,int x2,int y2);//����ĩλ�úϷ���
private:
	int a[9][9];	//���ڴ�����������
	int score;
};

inline Checkerboard::Checkerboard()
{
	score = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++) 
		{
			a[i][j] = 0;
		}
	}
	spawn(a);
}

inline Checkerboard::~Checkerboard()
{
}

