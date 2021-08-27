/*�޿��ӻ����������*/
#include<iostream>
#include"checkerboard.h"
#include"eliminate.h"
#include"path.h"
using namespace std;


int main_base()
{
	int location[4];//����յ�����
	int color_end;//�յ�������ɫ
	int effect;//�ж��Ƿ�����ƶ�
	Checkerboard game;//��Ϸ����
	
	while (1)
	{

		//eliminate(&game, 1,1,"all");//��ȥϵͳ�Զ����ɵ�����
		system("cls");
		game.show();
		if (game.game_over() == true)
		{
			break;
		}
		game.fetch_instruction(location);//��������
		path_search route(location[0]-1,location[1]-1,location[2]-1,location[3]-1,game);//ִ��һ����������·��
		route.searchPath(game);
		if (route.printPath())//�����ƶ�
		{
			game.move(location, &color_end, &effect);
			system("pause");
		}
		else
			effect = 0;
		if (effect == 1)//����ƶ�
		{
			int flag = eliminate(&game, location[2], location[3]);//��ȥ���ӷ�
			game.add(flag);
		}
		else
			continue;
		
	}
	cout << endl << "��Ϸ���������յ÷�Ϊ: " << game.get_score() << endl;

	return 0;
}