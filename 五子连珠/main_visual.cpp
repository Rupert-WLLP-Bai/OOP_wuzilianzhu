/*可视化界面主体*/
#include<iostream>
#include<graphics.h>
#include"eliminate.h"
#include"path.h"
#include"Visual_interface.cpp"
using namespace std;

int main_visual()
{
	Visual_interface Window;
	initgraph(width, height, SHOWCONSOLE);
	setlinestyle(PS_SOLID, 2);		// 设置线宽为 2
	while (1)
	{
		//eliminate(&Window.game, 1, 1, "all");//检查系统生成的棋子是否能自动消去
		
		BeginBatchDraw();//防止回车时出现闪屏
		Window.draw_root_window();
		Window.draw_board();
		Window.draw_score();
		FlushBatchDraw();
		cout << "Blank = " << Window.game.num_of_blank() << endl;
		Window.game_over();
		Window.mouse_catching();
		bool move = Window.search_path_and_move();
		if(move)
			Window.elinimate_and_score();
		cleardevice();
	}
	return 0;
}