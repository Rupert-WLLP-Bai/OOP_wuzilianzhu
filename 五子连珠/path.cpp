#include"checkerboard.h"
#include<stack>
#include"path.h"
path_search::Node path_search::offset[] = { Node(-1, 0), Node(1, 0), Node(0, -1), Node(0, 1) };

void path_search::maze_spawn(Checkerboard A)
{
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			if (A.get_color(i, j) == 0)
				m_maze[i-1][j-1] = 0;
			else
				m_maze[i-1][j-1] = -1;
		}
	}
}

path_search::~path_search()
{
}

