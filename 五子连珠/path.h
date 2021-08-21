#pragma once
#include"checkerboard.h"
#include<stack>
#include<iostream>
#include<iomanip>

class path_search
{
public:
	//��Ա������ʼ��
	path_search(int start_x, int start_y, int end_x, int end_y,Checkerboard A)
		:m_start(Node(start_x, start_y)), m_end(Node(end_x, end_y))
	{
		maze_spawn(A);
		m_maze[start_x][start_y] = 1;  //�Թ���ڳ�ʼ��Ϊ1�������ظ���
	}
	~path_search();
	//�������·��
	void searchPath(Checkerboard A)
	{
		searchPath(m_tempPath, m_start, m_end,A);//����˽�к���
	}
	//��ӡ���·���߹��ĵ�
	bool printPath()
	{
		if (m_path.empty())
		{
			cout << "�޿���·��" << endl;
			return false;
		}

		cout << "���·������: " << endl;
		while (!m_path.empty())
		{
			cout << '(' << m_path.top().m_x+1 << ','
				<< m_path.top().m_y+1 << ')' << "����>"
				<< m_maze[m_path.top().m_x][m_path.top().m_y]-1
				<< endl;
			m_path.pop();
		}
		return true;
	}
	//��ӡ�����������ڵ�ֵ
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
private:
	//����ڵ�
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

	void searchPath(stack<Node>& path,
		const Node& start, const Node& end, Checkerboard A)
	{
		if (start.m_x == end.m_x && start.m_y == end.m_y)  //�ߵ��յ�
		{
			if (path.size() < m_path.size()  //��ǰ·������ �� Ϊ��һ���ҵ���·��
				|| m_path.empty())
				m_path = path;
			return;
		}
		for (size_t i = 0; i < 4; ++i)  //�����ĸ�����
		{
			Node nextNode = start + offset[i];  //����ƫ����
			if (isCanGo(start, nextNode))  //�������ͨ��
			{
				m_maze[nextNode.m_x][nextNode.m_y] = m_maze[start.m_x][start.m_y] + 1;
				path.push(nextNode);  //�ڵ���ջ
				searchPath(path, nextNode, end, A);  //�ݹ����
				path.pop();    //����ջ��
			}
		}
	}
	bool isCanGo(const Node& start, const Node& next)const
	{
		int x = next.m_x, y = next.m_y;
		int preValue = m_maze[start.m_x][start.m_y]; //�ڵ�ֵ
		if (x < 0 || x > 8 || y < 0 || y > 8  //Խ�� 
			|| -1 == m_maze[x][y])			//ǽ
			return false;
		if (0 == m_maze[x][y])  //������
			return true;
		else
			return preValue + 1 < m_maze[x][y];  //�߹��ĵ�
	}


	stack<Node> m_path; //�洢���·��
	stack<Node> m_tempPath; //�洢��ʱ·��
	Node m_start;//���
	Node m_end;//�յ�
	static Node offset[4];//�ĸ�����ƫ����
	int m_maze[9][9]; //�Թ�
	void maze_spawn(Checkerboard A);//���ɳ�ʼ�Թ�
};


