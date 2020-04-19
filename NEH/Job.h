#pragma once
#include <vector>
class Job
{
public:
	int index;
	std::vector<int> timesOnMachines;
	int sum;
	bool operator< (const Job& other) const {
		if (sum == other.sum)
		{
			return index > other.index;
		}
		return sum < other.sum;
	}
	void setSum();
};

