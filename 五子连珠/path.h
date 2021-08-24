#pragma once
#include"checkerboard.h"
#include<deque>
#include<iostream>
#include<iomanip>
//定义节点

class path_search
{
public:
	class Node
	{
	public:
		int m_x;
		int m_y;
		Node(int x = 0, int y = 0) : m_x(x), m_y(y) {}
		const Node operator+ (const Node& that)const
		{
			Node node;
			node.m_x = m_x + that.m_x;
			node.m_y = m_y + that.m_y;
			return node;
		}
	};
	//成员变量初始化
	path_search(int start_x, int start_y, int end_x, int end_y, Checkerboard A)
		:m_start(Node(start_x, start_y)), m_end(Node(end_x, end_y))
	{
		maze_spawn(A);
		m_maze[start_x][start_y] = 1;  //迷宫入口初始化为1，避免重复走
	}
	~path_search();
	//查找最短路径
	void searchPath(Checkerboard A)
	{
		searchPath(m_tempPath, m_start, m_end, A);//调用私有函数
	}
	//打印最短路径走过的点(用另一端弹出)
	bool printPath()
	{
		if (m_path.empty())
		{
			cout << "无可行路径" << endl;
			return false;

		}

		cout << "最短路径如下: " << endl;
		cout << "(" << m_start.m_x + 1 << "," << m_start.m_y + 1 << ")" << "——>" << 0 << endl;//起点
		while (!m_path.empty())
		{
			cout << '(' << m_path.front().m_x + 1 << ','
				<< m_path.front().m_y + 1 << ')' << "——>"
				<< m_maze[m_path.front().m_x][m_path.front().m_y] - 1
				<< endl;
			m_path.pop_front();
		}

		return true;
	}
	//打印遍历后的数组节点值
	void printMaze()const
	{
		for (size_t i = 0; i < 9; ++i)
		{
			for (size_t j = 0; j < 9; ++j)
			{
				cout << setw(2) << m_maze[i][j] << ',';
			}
			cout << '\b' << endl;
		}
	}
	bool m_path_empty()
	{
		if (m_path.empty())
			return true;
		else
			return false;
	}

	deque<Node> m_path; //存储最短路径

private:


	void searchPath(deque<Node>& path,
		const Node& start, const Node& end, Checkerboard A)
	{
		if (start.m_x == end.m_x && start.m_y == end.m_y)  //走到终点
		{
			if (path.size() < m_path.size()  //当前路径更短 或 为第一个找到的路径
				|| m_path.empty())
				m_path = path;
			return;
		}
		for (size_t i = 0; i < 4; ++i)  //遍历四个方向
		{
			Node nextNode = start + offset[i];  //加上偏移量
			if (isCanGo(start, nextNode))  //如果可以通过
			{
				m_maze[nextNode.m_x][nextNode.m_y] = m_maze[start.m_x][start.m_y] + 1;
				path.push_back(nextNode);  //节点入栈
				searchPath(path, nextNode, end, A);  //递归查找
				path.pop_back();    //弹出栈顶
			}
		}
	}
	bool isCanGo(const Node& start, const Node& next)const
	{
		int x = next.m_x, y = next.m_y;
		int preValue = m_maze[start.m_x][start.m_y]; //节点值
		if (x < 0 || x > 8 || y < 0 || y > 8  //越界 
			|| -1 == m_maze[x][y])			//墙
			return false;
		if (0 == m_maze[x][y])  //可以走
			return true;
		else
			return preValue + 1 < m_maze[x][y];  //走过的点
	}


	deque<Node> m_tempPath; //存储临时路径
	deque<Node> copy_path;//最短路径备份
	Node m_start;//起点
	Node m_end;//终点
	static Node offset[4];//四个方向偏移量
	int m_maze[9][9]; //迷宫
	void maze_spawn(Checkerboard A);//生成初始迷宫
};


