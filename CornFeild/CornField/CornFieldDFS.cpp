#include "CornFieldDFS.hpp"
#include <vector>
#include <iostream>
cornfield_dfs::cornfield_dfs(std::vector<std::vector<bool>> map)
{
	this->original_map = map;
	this->width = map.size();
	this->height = map[0].size();
	this->placed_map = std::vector<std::vector<bool>>(width);
	this->visited_map = std::vector<std::vector<bool>>(width);
	for (int i = 0; i < this->width; i++)
	{
		this->placed_map[i] = std::vector<bool>(height);
		this->visited_map[i] = std::vector<bool>(height);
	}

}

cornfield_dfs::~cornfield_dfs()
{

}

int cornfield_dfs::solve()
{
	dfs(0, 0);
	return this->solved_map.size();
}


bool cornfield_dfs::check_exist(std::vector<std::vector<bool>> map)
{

	for (int i = 0; i < this->solved_map.size(); i++)
	{
		bool bit_comparer = false;
		for (int k = 0; k < this->width; k++)
			for (int l = 0; l < this->height; l++)
			{
				bit_comparer |= map[k][l] ^ this->solved_map[i][k][l];
			}
		if (!bit_comparer) return true;
	}
	return false;
}

int cornfield_dfs::dfs(int x, int y)
{
	this->visited_map[x][y] = true;
	bool can_placed = true;
	int num_placed = 0;
	int num_noplaced = 0;
	//如果本格不能放，则不能放
	can_placed &= this->original_map[x][y];
	//检查四个方向是否有已经放的
	if (can_placed && x > 0) can_placed &= !this->placed_map[x - 1][y];
	if (can_placed && y > 0) can_placed &= !this->placed_map[x][y - 1];
	if (can_placed && x < width - 1) can_placed &= !this->placed_map[x + 1][y];
	if (can_placed && y < height - 1) can_placed &= !this->placed_map[x][y + 1];
	if (can_placed) //如果这个可以放
	{
		this->placed_map[x][y] = true;
		if (x > 0 && !this->visited_map[x - 1][y]) num_placed += dfs(x - 1, y);
		if (y > 0 && !this->visited_map[x][y - 1]) num_placed += dfs(x, y - 1);
		if (x < width - 1 && !this->visited_map[x + 1][y]) num_placed += dfs(x + 1, y);
		if (y < height - 1 && !this->visited_map[x][y + 1]) num_placed += dfs(x, y + 1);
		if (!num_placed)
		{
			if (!this->check_exist(this->placed_map))
			{
				this->solved_map.push_back(this->placed_map);
			}
			num_placed++;
		}
	}
	//不能放的情况
	this->placed_map[x][y] = false;
	if (x > 0 && !this->visited_map[x - 1][y]) num_noplaced += dfs(x - 1, y);
	if (y > 0 && !this->visited_map[x][y - 1]) num_noplaced += dfs(x, y - 1);
	if (x < width - 1 && !this->visited_map[x + 1][y]) num_noplaced += dfs(x + 1, y);
	if (y < height - 1 && !this->visited_map[x][y + 1]) num_noplaced += dfs(x, y + 1);
	if (!num_noplaced)
	{
		if (!this->check_exist(this->placed_map))
		{
			this->solved_map.push_back(this->placed_map);
		}
		num_noplaced++;
	}
	this->visited_map[x][y] = false;
	return num_noplaced + num_placed;
}
