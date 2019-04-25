#include "CornFieldDP.hpp"

cornfield_dp::cornfield_dp(std::vector<std::vector<bool>> map)
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
	//��ʼ����������״̬
	this->get_available_states();
	this->dp = std::vector<std::vector<int>>(this->height);
	for (int i = 0; i < this->height; i++)
		this->dp[i] = std::vector<int>(this->inline_available_states.size());

}

cornfield_dp::~cornfield_dp()
{
}

int cornfield_dp::solve()
{
	//��ʼ����һ��
	for (int i = 0; i < this->inline_available_states.size(); i++)
	{
		if (can_near_line(0, i))
			dp[0][i] = 1;
	}
	//�ӵڶ��п�ʼ����״̬ѡ��
	for (int i = 1; i < height; i++)
	{
		for (int j = 0; j < this->inline_available_states.size(); j++)
		{
			if (!can_near_line(i, j)) //�жϵ�i�� ���簴״̬j��ţ�Ļ��в��С�
				continue;
			/*
				�������ƥ��ͨ����������һ�н���ƥ�䣬
				ѡ����һ��״̬���뱾�е�ǰ״̬���ݵ�״̬�����������ĵ�ǰ������
			*/
			for (int f = 0; f < this->inline_available_states.size(); f++)
			{
				/*
					��ʵ������������ν����������ƥ���״̬һ��ʼ����0.
				*/
				if (!can_near_line(i - 1, f)) //��֦ �ж���һ������״̬�Ƿ�����
					continue;
				if (!(inline_available_states[j] & inline_available_states[f])) //������Ҫ����������᲻�ᷢ����������
					dp[i][j] += dp[i - 1][f]; //�������ʾ������(i-1,f)״̬�°���(i,j)״̬���ͼ̳�����״̬
			}
		}
	}
	//�������һ�е���״̬��
	int ans = 0;
	for (int i = 0; i < this->inline_available_states.size(); i++)
		ans += dp[height - 1][i];
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
