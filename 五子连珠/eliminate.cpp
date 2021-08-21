#include"eliminate.h"
#include"checkerboard.h"

void eliminate_1(Checkerboard A, int x, int y, int* left, int* right) //形参为棋盘,终点坐标,搜索横向长度
{
	if (A.get_color(x, y) == 0)
		return;
	int start = y;
	int color = A.get_color(x, y);
	int l = 0;//棋子左边的长度
	int r = 0;//棋子右边的长度
	while (1)
	{
		if (y == 1)
			break;
		if (A.get_color(x, y - 1) == color)
		{
			l++;
			y--;
		}
		else
			break;
	}

	y = start;

	while (1)
	{
		if (y == 9)
			break;
		if (A.get_color(x, y + 1) == color)
		{
			r++;
			y++;
		}
		else
			break;

	}

	*left = l;
	*right = r;
}

void eliminate_2(Checkerboard A, int x, int y, int* up, int* down)//形参为棋盘,终点坐标,搜索竖向长度
{
	if (A.get_color(x, y) == 0)
		return;
	int start = x;
	int color = A.get_color(x, y);
	int u = 0;//上侧棋子的长度
	int d = 0;//下侧棋子的长度

	while (1)
	{
		if (x == 9)
			break;
		if (A.get_color(x + 1, y) == color)
		{
			d++;
			x++;
		}
		else
			break;
	}

	x = start;

	while (1)
	{
		if (x == 1)
			break;
		if (A.get_color(x - 1, y) == color)
		{
			u++;
			x++;
		}
		else
			break;

	}

	*up = u;
	*down = d;

}

void eliminate_3(Checkerboard A, int x, int y, int* EN, int* WS)//形参为棋盘,终点坐标,搜索撇向长度
{
	if (A.get_color(x, y) == 0)
		return;
	int start_x = x;
	int start_y = y;
	int color = A.get_color(x, y);
	int en = 0;//EN侧棋子的长度
	int ws = 0;//WS侧棋子的长度
	while (1)
	{
		if (x == 1 || y == 9)
			break;
		if (A.get_color(x - 1, y + 1) == color)
		{
			en++;
			x--; y++;
		}
		else
			break;
	}

	x = start_x;
	y = start_y;

	while (1)
	{
		if (x == 9 || y == 1)
			break;
		if (A.get_color(x + 1, y - 1) == color)
		{
			ws++;
			x++; y--;
		}
		else
			break;
	}

	*WS = ws;
	*EN = en;
}

void eliminate_4(Checkerboard A, int x, int y, int* WN, int* ES)//形参为棋盘,终点坐标,搜索捺向长度
{
	if (A.get_color(x, y) == 0)
		return;
	int start_x = x;
	int start_y = y;
	int color = A.get_color(x, y);
	int wn = 0;//WN侧棋子的长度
	int es = 0;//ES侧棋子的长度
	while (1)
	{
		if (x == 1 || y == 1)
			break;
		if (A.get_color(x - 1, y - 1) == color)
		{
			wn++;
			x--; y--;
		}
		else
			break;
	}

	x = start_x;
	y = start_y;

	while (1)
	{
		if (x == 9 || y == 9)
			break;
		if (A.get_color(x + 1, y + 1) == color)
		{
			es++;
			x++; y++;
		}
		else
			break;
	}

	*WN = wn;
	*ES = es;
}

int eliminate(Checkerboard *A, int x, int y,const char *prompt)//综合四个函数进行消去
{
	int flag = 0;//默认未消去
	if (prompt == "all")//用于检查系统自动生成的棋子是否可消去
	{
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				x = i;
				y = j;
				int start_x = x;
				int start_y = y;
				int E = 0;//消去数量,用于计分
				int left, right, up, down;
				int EN, WS;//东北,西南方向
				int WN, ES;//西北,东南方向
				int num[4];//四个方向消去数量
				eliminate_1(*A, x, y, &left, &right);
				eliminate_2(*A, x, y, &up, &down);
				eliminate_3(*A, x, y, &EN, &WS);
				eliminate_4(*A, x, y, &WN, &ES);
				num[0] = left + right; num[1] = up + down; num[2] = EN + WS; num[3] = WN + ES;
				if (num[0] >= 4)
				{
					for (int i = y - left; i <= y + right; i++)
						(*A).set(x, i, 0);//blank
					E += num[0];
					x = start_x;
					y = start_y;
					flag = 1;
				}
				if (num[1] >= 4)
				{
					for (int i = x - up; i <= x + down; i++)
						(*A).set(i, y, 0);//blank
					E += num[1];
					x = start_x;
					y = start_y;
					flag = 1;
				}
				if (num[2] >= 4)
				{
					int i = 0;
					while (i != num[2] + 1)
					{
						(*A).set(x - EN, y + EN, 0);//blank
						i++;
						x++;
						y--;
					}
					E += num[2];
					x = start_x;
					y = start_y;
					flag = 1;
				}
				if (num[3] >= 4)
				{
					int i = 0;
					while (i != num[3] + 1)
					{
						(*A).set(x - WN, y - WN, 0);//blank
						i++;
						x++;
						y++;
					}
					E += num[3];
					x = start_x;
					y = start_y;
					flag = 1;
				}
			}
		}
		return flag;
	}
	else
	{
		int start_x = x;
		int start_y = y;
		int E = 0;//消去数量,用于计分
		int left, right, up, down;
		int EN, WS;//东北,西南方向
		int WN, ES;//西北,东南方向
		int num[4];//四个方向消去数量
		eliminate_1(*A, x, y, &left, &right);
		eliminate_2(*A, x, y, &up, &down);
		eliminate_3(*A, x, y, &EN, &WS);
		eliminate_4(*A, x, y, &WN, &ES);
		num[0] = left + right; num[1] = up + down; num[2] = EN + WS; num[3] = WN + ES;
		if (num[0] >= 4)
		{
			for (int i = y - left; i <= y + right; i++)
				(*A).set(x, i, 0);//blank
			E += num[0];
			x = start_x;
			y = start_y;
			flag = 1;
		}
		if (num[1] >= 4)
		{
			for (int i = x - up; i <= x + down; i++)
				(*A).set(i, y, 0);//blank
			E += num[1];
			x = start_x;
			y = start_y;
			flag = 1;
		}
		if (num[2] >= 4)
		{
			int i = 0;
			while (i != num[2] + 1)
			{
				(*A).set(x - EN, y + EN, 0);//blank
				i++;
				x++;
				y--;
			}
			E += num[2];
			x = start_x;
			y = start_y;
			flag = 1;
		}
		if (num[3] >= 4)
		{
			int i = 0;
			while (i != num[3] + 1)
			{
				(*A).set(x - WN, y - WN, 0);//blank
				i++;
				x++;
				y++;
			}
			E += num[3];
			x = start_x;
			y = start_y;
			flag = 1;
		}
		if (flag == 1)
			E += 1;
		(*A).score_add(2 * E);
	}
	return flag;
}