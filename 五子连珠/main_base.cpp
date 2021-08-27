/*无可视化界面的主体*/
#include<iostream>
#include"checkerboard.h"
#include"eliminate.h"
#include"path.h"
using namespace std;


int main_base()
{
	int location[4];//起点终点坐标
	int color_end;//终点棋子颜色
	int effect;//判断是否完成移动
	Checkerboard game;//游戏主体
	
	while (1)
	{

		//eliminate(&game, 1,1,"all");//消去系统自动生成的棋子
		system("cls");
		game.show();
		if (game.game_over() == true)
		{
			break;
		}
		game.fetch_instruction(location);//键盘输入
		path_search route(location[0]-1,location[1]-1,location[2]-1,location[3]-1,game);//执行一次重新搜索路径
		route.searchPath(game);
		if (route.printPath())//可以移动
		{
			game.move(location, &color_end, &effect);
			system("pause");
		}
		else
			effect = 0;
		if (effect == 1)//完成移动
		{
			int flag = eliminate(&game, location[2], location[3]);//消去并加分
			game.add(flag);
		}
		else
			continue;
		
	}
	cout << endl << "游戏结束，最终得分为: " << game.get_score() << endl;

	return 0;
}