#pragma once
#include <string>
#include <vector>
class Sample
{
private:
	std::vector<long double> properties;
	std::string label;

public:
	Sample(std::vector<long double> properties, std::string label);
	~Sample();
	int getSize();
	long double operator[](const int index);
	std::string getClass();
};

