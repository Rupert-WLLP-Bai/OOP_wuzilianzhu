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
	while (1)
	{
		Window.draw_root_window();
		Window.draw_board();
		Window.draw_score();
		
		
		system("pause");
		cleardevice();
	}
	return 0;
}