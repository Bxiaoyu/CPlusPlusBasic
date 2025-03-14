#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

/*
* 深度遍历搜索迷宫路径，软件运行如下：
* 请输入迷宫行列数（例如：10 10）：5 5
* 请输入迷宫的路径信息（0表示可以走，1表示不能走）：
* 0 0 0 1 1
* 1 0 0 0 1
* 1 1 0 1 1
* 1 1 0 0 1
* 1 1 1 0 0
* 
* 迷宫搜索中
* >>>如果没有路径，直接输出<<<
* 不存在一条迷宫路径
* >>>如果有路径，直接输出<<<
* * * * 1 1
* 1 0 * 0 1
* 1 1 * 1 1
* 1 1 * * 1
* 1 1 1 * *
*/


// 定义每一个节点的四个方向
const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;

// 迷宫每一个节点方向的数量
const int WAY_NUM = 4;

// 定义节点行走状态
const int YES = 4;
const int NO = 5;

// 迷宫
class Maze
{
public:
	Maze(int row, int col)
		: _row(row)
		, _col(col)
	{
		_pMaze = new Node * [_row];
		for (int i = 0; i < _row; ++i)
		{
			_pMaze[i] = new Node[_col];
		}
	}

	// 初始化迷宫路径节点
	void initNode(int x, int y, int val)
	{
		_pMaze[x][y]._x = x;
		_pMaze[x][y]._y = y;
		_pMaze[x][y]._val = val;
		for (int i = 0; i < WAY_NUM; ++i)
		{
			_pMaze[x][y]._state[i] = NO;
		}
	}

	// 初始化迷宫0节点四个方向的行走状态信息
	void setNodeState()
	{
		for (int i = 0; i < _row; ++i)
		{
			for (int j = 0; j < _col; ++j)
			{
				if (_pMaze[i][j]._val == 1)
				{
					continue;
				}

				if (j < _col - 1 && _pMaze[i][j+1]._val == 0)
				{
					_pMaze[i][j]._state[RIGHT] = YES;
				}

				if (i < _row - 1 && _pMaze[i+1][j]._val == 0)
				{
					_pMaze[i][j]._state[DOWN] = YES;
				}

				if (j > 0 && _pMaze[i][j-1]._val == 0)
				{
					_pMaze[i][j]._state[LEFT] = YES;
				}

				if (i > 0 && _pMaze[i - 1][j]._val == 0)
				{
					_pMaze[i][j]._state[UP] = YES;
				}
			}
		}
	}

	// 深度搜索迷宫路径
	void searchMazePath()
	{
		if (_pMaze[0][0]._val == 1)
		{
			return;
		}

		_stack.push(_pMaze[0][0]);

		while (!_stack.empty())
		{
			Node top = _stack.top();
			int x = top._x;
			int y = top._y;

			// 已经找到右下角出口的迷宫路径
			if (x == _row - 1 && y == _col - 1)
			{
				return;
			}

			// 往右方搜寻
			if (_pMaze[x][y]._state[RIGHT] == YES)
			{
				_pMaze[x][y]._state[RIGHT] = NO;
				_pMaze[x][y + 1]._state[LEFT] = NO;
				_stack.push(_pMaze[x][y + 1]);
				continue;
			}

			// 往下方搜寻
			if (_pMaze[x][y]._state[DOWN] == YES)
			{
				_pMaze[x][y]._state[DOWN] = NO;
				_pMaze[x+1][y]._state[UP] = NO;
				_stack.push(_pMaze[x + 1][y]);
				continue;
			}

			// 往左方搜寻
			if (_pMaze[x][y]._state[LEFT] == YES)
			{
				_pMaze[x][y]._state[LEFT] = NO;
				_pMaze[x][y - 1]._state[RIGHT] = NO;
				_stack.push(_pMaze[x][y - 1]);
				continue;
			}

			// 往上方搜寻
			if (_pMaze[x][y]._state[UP] == YES)
			{
				_pMaze[x][y]._state[UP] = NO;
				_pMaze[x - 1][y]._state[DOWN] = NO;
				_stack.push(_pMaze[x - 1][y]);
				continue;
			}

			_stack.pop();
		}
	}

	// 显示迷宫路径
	void showMazePath()
	{
		if (_stack.empty())
		{
			cout << "不存在一条迷宫路径" << endl;
			return;
		}
		else
		{
			while (!_stack.empty())
			{
				Node top = _stack.top();
				_pMaze[top._x][top._y]._val = '*';
				_stack.pop();
			}

			for (int i = 0; i < _row; ++i)
			{
				for (int j = 0; j < _col; ++j)
				{
					if (_pMaze[i][j]._val == '*')
					{
						cout << "* ";
					}
					else
					{
						cout << _pMaze[i][j]._val << " ";
					}
				}
				cout << endl;
			}
		}
	}
private:
	struct Node
	{
		int _x;  // x 坐标
		int _y;  // y 坐标
		int _val;  // 值
		int _state[WAY_NUM];  // 节点四个方向状态
	};

	Node** _pMaze;  // 动态生成迷宫路径
	int _row;
	int _col;
	stack<Node> _stack;  // 栈结构，辅助深度搜索迷宫路径
};

#if 0
int main()
{
	cout << "请输入迷宫的行列数（例如：10 10）：";
	int row, col, data;
	cin >> row >> col;

	Maze maze(row, col);  // 创建迷宫对象

	cout << "请输入迷宫的路径信息（0表示可以走，1表示不可以走）：" << endl;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			cin >> data;
			maze.initNode(i, j, data);  // 初始化迷宫基本信息
		}
	}

	// 设置所有节点四个方向的状态
	maze.setNodeState();

	// 开始从迷宫左上角搜索迷宫路径信息
	maze.searchMazePath();

	// 打印迷宫路径
	maze.showMazePath();

	return 0;
}
#endif