#pragma once
/*checkerboard.h	棋盘相关*/
#include<queue>
using namespace std;
typedef pair<int, int>P;
class Checkerboard
{
public:
	Checkerboard();
	~Checkerboard();
	void score_add(int x);//加分
	int get_score();//显示分数
	void set(int x, int y, int color);//赋值
	void show();	//输出棋盘内容
	void spawn(int a[9][9]);//初始化棋盘
	int num_of_blank();//检查棋盘空白数
	bool game_over();//检查游戏是否结束	 true:结束 false:继续
	void fetch_instruction(int* location);//键盘获取输入
	int get_color(int x, int y);//获取棋子颜色
	void move(int location[4],int *color_end,int *effect);//移动 需要返回的值为终点坐标 终点棋子颜色 是否完成移动
	void add(int flag);//添加棋子
	bool check_range(int x1, int y1,int x2,int y2);//检查初末位置合法性
private:
	int a[9][9];	//用于储存棋盘内容
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

