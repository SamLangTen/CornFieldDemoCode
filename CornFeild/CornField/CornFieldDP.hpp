#pragma once
#include <vector>

class cornfield_dp
{
public:
	cornfield_dp(std::vector<std::vector<bool>>);
	~cornfield_dp();
	int solve();

private:
	std::vector<int> inline_available_states;
	std::vector<int> map;
	std::vector<std::vector<int>> dp;
	bool can_inline(int);
	bool can_near_line(int, int);
	void get_available_states();
	int height;
	int width;
};
