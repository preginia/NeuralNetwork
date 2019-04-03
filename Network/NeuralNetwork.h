#pragma once
#include<vector>
#include "Neuron.h"
#include "Sample.h"
#include "Neuron.h"

class NeuralNetwork
{
private:
	std::vector<Neuron> inputLayer;
	std::vector<Neuron> hiddenLayer;
	std::vector<Neuron> hiddenLayer2;
	std::vector<Neuron> outputLayer;
public:
	NeuralNetwork(int inputLayerSize, int hiddenLayerSize, int hiddenLayerSize2, int outputLayerSize);
	~NeuralNetwork();
	std::string classify(Sample sample);
	void train(std::vector<Sample> samples);
	long double error_fun(std::vector<Sample> samples);
};

