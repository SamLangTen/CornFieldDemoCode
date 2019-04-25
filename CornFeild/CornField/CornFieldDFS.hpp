#pragma once
#include <vector>

class cornfield_dfs
{
public:
	cornfield_dfs(std::vector<std::vector<bool>>);
	~cornfield_dfs();
	int solve();

private:
	std::vector<std::vector<bool>> visited_map;
	std::vector<std::vector<bool>> original_map;
	std::vector<std::vector<bool>> placed_map;
	std::vector<std::vector<std::vector<bool>>> solved_map;
	bool check_exist(std::vector<std::vector<bool>> map);
	int width;
	int height;
	int dfs(int x, int y);

};

