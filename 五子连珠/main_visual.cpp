/*���ӻ���������*/
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
	setlinestyle(PS_SOLID, 2);		// �����߿�Ϊ 2
	while (1)
	{
		//eliminate(&Window.game, 1, 1, "all");//���ϵͳ���ɵ������Ƿ����Զ���ȥ
		
		BeginBatchDraw();//��ֹ�س�ʱ��������
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