#ifndef MATH_H_
#define MATH_H_
#include <vector>
#include <algorithm>

inline int MiddleNumber(int x, int y, int z)
{
	std::vector<int> temp;
	temp.push_back(x);
	temp.push_back(y);
	temp.push_back(z);
	std::sort(temp.begin(), temp.end());
	return temp[1];
}

#endif
