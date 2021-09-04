/*可视化界面主体*/
#include<iostream>
#include<graphics.h>
#include"eliminate.h"
#include"path.h"
#include"Visual_interface.cpp"
using namespace std;

inline void start()
{
	int val = MessageBox(GetHWnd(), "选择是否显示Console", "Before Start", MB_YESNO);
	if (val == IDYES)
		initgraph(width, height, SHOWCONSOLE);
	else
		initgraph(width, height);
	setlinestyle(PS_SOLID, 2);		// 设置线宽为 2
}

int main_visual()
{
	Visual_interface Window;
	start();
	while (1)
	{
		BeginBatchDraw();//防止回车时出现闪屏
		Window.check_spawn();
		Window.draw_root_window();
		Window.draw_board();
		Window.draw_score();
		FlushBatchDraw();
		Window.game_over();
		Window.mouse_catching();
		bool move = Window.search_path_and_move();
		if (move)
		{
			cout << "移动后数组状态为: " << endl;
			Window.game.show();
			Window.eliminate_and_score();
		}
		cleardevice();
	}
	return 0;
}

