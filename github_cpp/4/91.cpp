#include "towerOfHanoi.h"

TowerOfHanoi::TowerOfHanoi(int no_of_disks) : m_steps{vector<int>{}, vector<int>{}, vector<int>{}}
{
	for(int i{no_of_disks}; i > 0; --i)
		m_src.push_front(i);

	towerOfHanoi(no_of_disks);
}

void TowerOfHanoi::towerOfHanoi(int no_of_disks)
{
	towerOfHanoi(no_of_disks, m_src, m_aux, m_dest);
}

void TowerOfHanoi::towerOfHanoi(int disc, deque<int>& src, deque<int>& aux, deque<int>& dest)
{
	if(disc == 1)
	 	moveTower();
	else
	{
		towerOfHanoi(disc - 1, src, aux, dest);
		moveTower();
		towerOfHanoi(disc -1, aux, dest, src);
	}
}

void TowerOfHanoi::moveTower()
{
	m_dest.push_front(m_src.front());
	m_src.pop_front();
	recordSteps();
}

void TowerOfHanoi::recordSteps()
{
	for(const auto& step : m_src)
		m_steps[0].push_back(step);

	for(const auto& step : m_aux)
		m_steps[1].push_back(step);

	for(const auto& step : m_dest)
		m_steps[2].push_back(step);
}
