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
	initgraph(width, height,SHOWCONSOLE);
	while (1)
	{
		BeginBatchDraw();//��ֹ�س�ʱ��������
		Window.draw_root_window();
		Window.draw_board();
		Window.draw_score();
		FlushBatchDraw();
		Window.mouse_catching();
		
		
		cleardevice();
	}
	return 0;
}