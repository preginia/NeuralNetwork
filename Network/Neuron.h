#pragma once
#include <vector>
class Neuron
{
private:
	std::vector<long double> weights;
	long double bias;

	std::vector<long double> bestWeights;
	long double bestBias;

public:
	Neuron(int size);
	~Neuron();
	Neuron();
	long double classify(std::vector<long double> values);
	long double operator[](const int index);
	int getSize();
	void modify(long double n, long double error, std::vector<long double> inputs);


	

};

