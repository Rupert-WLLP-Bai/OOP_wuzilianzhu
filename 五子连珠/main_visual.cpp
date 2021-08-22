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
	Window.draw_root_window();
	Window.draw_board();
	system("pause");
	return 0;
}