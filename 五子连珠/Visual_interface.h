#pragma once
/*
可视化界面实现

功能：
1.画出棋盘和棋子
2.获取鼠标输入
3.实现菜单选项

*/
#include<graphics.h>
#include"checkerboard.h"

class board //棋盘类
{
public:
	board();//用Checkerboard,width,height初始化board的参数
	~board();

private:
	struct bead  //珠子
	{
		int x;
		int y;
		int r;
		int color;
	};
	int height;
	int width;
	void draw_board();//画出棋盘
	void draw_bead();//画珠子
};

board::board()
{
}

board::~board()
{
}


