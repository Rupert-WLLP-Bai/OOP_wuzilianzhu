#pragma once
/*
���ӻ�����ʵ��

���ܣ�
1.�������̺�����
2.��ȡ�������
3.ʵ�ֲ˵�ѡ��

*/
#include<graphics.h>
#include"checkerboard.h"

class board //������
{
public:
	board();//��Checkerboard,width,height��ʼ��board�Ĳ���
	~board();

private:
	struct bead  //����
	{
		int x;
		int y;
		int r;
		int color;
	};
	int height;
	int width;
	void draw_board();//��������
	void draw_bead();//������
};

board::board()
{
}

board::~board()
{
}


