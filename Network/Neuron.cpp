#include "stdafx.h"
#include "Neuron.h"



// sigmoidal activation function
long double sig(long double x)
{
	return 1.0 / (1.0 + (long double)exp(-1.0*x));
}



Neuron::Neuron(int size)
{
	this->weights.resize(size);
	for (int i = 0; i < size; i++)
	{
		this->weights[i] = ((long double)(rand() % 10000)) / 10000;
	}

	bias = ((long double)(rand() % 10000)) / 10000;
}

Neuron::~Neuron()
{
}

Neuron::Neuron()
{
}

long double Neuron::classify(std::vector<long double> values)
{
	long double output = 0.0;
	for (int i = 0; i < this->weights.size(); i++)
	{
		long double weight = weights[i];
		output += weights[i] * values[i];
	}
	output += bias;
	double act = sig(output);
	return act;
}

long double Neuron::operator[](const int index)
{
	return this->weights[index];
}

int Neuron::getSize()
{
	return this->weights.size();
}

void Neuron::modify(long double n, long double error, std::vector<long double> inputs)
{
	for (int i = 0; i < weights.size(); i++)
	{
		long double weight = weights[i];
		weight += n * error * inputs[i];
		weights[i] = weight;
	}
	bias = bias + n * error;
}

