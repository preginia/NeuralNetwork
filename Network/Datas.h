#pragma once

#include <string>
#include <vector>
#include "Sample.h"
class Datas
{
public:
	static void loadData(std::string path, std::vector<Sample> &samples);
	Datas();
	~Datas();
};

