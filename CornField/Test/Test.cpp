// Test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class cornfield_dp
{
public:
	cornfield_dp(std::vector<std::vector<bool> >);
	~cornfield_dp();
	int solve();

private:
	std::vector<int> inline_available_states;
	std::vector<int> map;
	std::vector<std::vector<int> > dp;
	bool can_inline(int);
	bool can_near_line(int, int);
	void get_available_states();
	int height;
	int width;
};

cornfield_dp::cornfield_dp(std::vector<std::vector<bool> > map)
{
	this->height = map.size();
	this->width = map[0].size();
	for (int i = 0; i < height; i++)
	{
		this->map.push_back(0);
		for (int j = 0; j < width; j++)
		{
			if (!map[i][j])
				this->map[i] += (1 << (width - 1 - j));
		}
	}
	//初始化所有行内状态
	this->get_available_states();
	this->dp = std::vector<std::vector<int> >(this->height);
	for (int i = 0; i < this->height; i++)
		this->dp[i] = std::vector<int>(this->inline_available_states.size());

}

cornfield_dp::~cornfield_dp()
{
}

int cornfield_dp::solve()
{
	//初始化第一行
	for (int i = 0; i < this->inline_available_states.size(); i++)
	{
		if (can_near_line(0, i))
			dp[0][i] = 1;
	}
	//从第二行开始进行状态选择
	for (int i = 1; i < height; i++)
	{
		for (int j = 0; j < this->inline_available_states.size(); j++)
		{
			if (!can_near_line(i, j)) //判断第i行 假如按状态j放牛的话行不行。
				continue;
			/*
				如果行内匹配通过，则与上一行进行匹配，
				选出上一行状态中与本行当前状态相容的状态，并查找他的当前方案数
			*/
			for (int f = 0; f < this->inline_available_states.size(); f++)
			{
				/*
					其实剪不剪都无所谓，不能行内匹配的状态一开始就是0.
				*/
				if (!can_near_line(i - 1, f)) //剪枝 判断上一行与其状态是否满足
					continue;
				if (!(inline_available_states[j] & inline_available_states[f])) //最后就是要检查这两个会不会发生上下相邻
					dp[i][j] += dp[i - 1][f]; //不会则表示可以在(i-1,f)状态下安排(i,j)状态，就继承它的状态
			}
		}
	}
	//计算最后一行的总状态数
	int ans = 0;
	for (int i = 0; i < this->inline_available_states.size(); i++)
	{
		ans += dp[height - 1][i];
		ans %= 100000000;
	}

	return ans;
}

bool inline cornfield_dp::can_inline(int state)
{
	return !(state & (state << 1));
}

bool inline cornfield_dp::can_near_line(int map_line, int state_line)
{
	return !(map[map_line] & this->inline_available_states[state_line]);
}

void inline cornfield_dp::get_available_states()
{
	for (int i = 0; i < (1 << this->width); i++)
		if (can_inline(i))
			this->inline_available_states.push_back(i);
}


int main()
{
	int height, width;
	cin >> height >> width;
	vector<vector<bool> > map(height);
	for (int i = 0; i < height; i++)
		map[i] = vector<bool>(width);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			int input;
			cin >> input;
			map[i][j] = input ? true : false;
		}
	cornfield_dp cf1(map);

	cout << cf1.solve();
}
