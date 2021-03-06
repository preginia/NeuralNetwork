#include "stdafx.h"
#include "NeuralNetwork.h"
#include <iostream>
#include<algorithm>

const int classesAmount = 8;
const std::string CLASSES[classesAmount] = { "cp","im","pp","imU","om","omL","imL","imS" };


NeuralNetwork::NeuralNetwork(int inputLayerSize, int hiddenLayerSize, int outputLayerSize)
{
	this->inputLayer.resize(inputLayerSize);
	this->hiddenLayer.resize(hiddenLayerSize);
	this->outputLayer.resize(outputLayerSize);
	
	for (int i = 0; i < inputLayerSize; i++)
	{
		Neuron neuron(1);
		inputLayer[i] = neuron;
	}

	for (int i = 0; i < hiddenLayerSize; i++)
	{
		Neuron neuron(inputLayerSize);
		hiddenLayer[i] = neuron;
	}

	for (int i = 0; i < outputLayerSize; i++)
	{
		Neuron neuron(hiddenLayerSize);
		outputLayer[i] = neuron;
	}


}

NeuralNetwork::~NeuralNetwork()
{
}

std::string NeuralNetwork::classify(Sample sample)
{
	std::vector<long double> inputLayerOutputs;
	std::vector<long double> hiddenLayerOutputs;
	std::vector<long double> outputLayerOutputs;

	inputLayerOutputs.resize(inputLayer.size());
	for (int i = 0; i < inputLayer.size(); i++)
	{
		std::vector<long double> values;
		values.push_back(sample[i]);
		inputLayerOutputs[i] = inputLayer[i].classify(values);
	}


	hiddenLayerOutputs.resize(hiddenLayer.size());
	for (int i = 0; i < hiddenLayer.size(); i++)
	{
		hiddenLayerOutputs[i] = hiddenLayer[i].classify(inputLayerOutputs);
	}

	outputLayerOutputs.resize(outputLayer.size());
	for (int i = 0; i < outputLayer.size(); i++)
	{
		outputLayerOutputs[i] = outputLayer[i].classify(hiddenLayerOutputs);
	}

	int index = -1;
	long double maxVal = -1;
	
	// looking for neuron in last layer which return highest
	// value from activate function
	for (int i = 0; i < outputLayerOutputs.size() ; i++)
	{
		if (outputLayerOutputs[i] > maxVal)
		{
			maxVal = outputLayerOutputs[i];
			index = i;
		}
	}

	return CLASSES[index];
}

void NeuralNetwork::train(std::vector<Sample> samples)
{

	std::random_shuffle(samples.begin(), samples.end());

	int best = -1;
	long double bestErr = 10000;
	long double n = 0.01;
	int it = 0;

	while(true)
	for (int i = 0; i < samples.size(); i++)
	{ 
		
			// randomize sample to train on it
			int rd = rand() % samples.size();
			Sample sample = samples[i];
			std::vector<long double> inputLayerOutputs;
			std::vector<long double> hiddenLayerOutputs;
			std::vector<long double> outputLayerOutputs;


			// compute outputs of each layer


			inputLayerOutputs.resize(inputLayer.size());
			for (int i = 0; i < inputLayer.size(); i++)
			{
				std::vector<long double> values;
				values.push_back(sample[i]);
				inputLayerOutputs[i] = inputLayer[i].classify(values);
			}


			hiddenLayerOutputs.resize(hiddenLayer.size());
			for (int i = 0; i < hiddenLayer.size(); i++)
			{
				hiddenLayerOutputs[i] = hiddenLayer[i].classify(inputLayerOutputs);
			}

			outputLayerOutputs.resize(outputLayer.size());
			for (int i = 0; i < outputLayer.size(); i++)
			{
				outputLayerOutputs[i] = outputLayer[i].classify(hiddenLayerOutputs);
			}
			

			// compute error for each layer with back propagation algorith

			std::vector<long double> outputLayerError;
			outputLayerError.resize(outputLayerOutputs.size());

			for (int i = 0; i < outputLayerError.size(); i++)
			{
				long double expectedValue;

				// checking which is expecting output for this sample for neuron
				// on i index in last layer and computing error

				expectedValue = ((sample.getClass() == CLASSES[i]) ? 1.0 : 0.0);
				outputLayerError[i] =(expectedValue - outputLayerOutputs[i]);
			}

			std::vector<long double> hiddenLayerError;
			hiddenLayerError.resize(hiddenLayerOutputs.size());
			for (int i = 0; i < hiddenLayerError.size(); i++)
			{
				long double error = 0.0;
				for (int j = 0; j < outputLayerError.size(); j++)
				{
					error += (outputLayerError[j] * outputLayer[j][i]);
				}
				hiddenLayerError[i] = error;

			}

			std::vector<long double> inputLayerError;
			inputLayerError.resize(inputLayerOutputs.size());
			for (int i = 0; i < inputLayerError.size(); i++)
			{
				long double error = 0.0;
				for (int j = 0; j < hiddenLayerError.size(); j++)
				{
					error += (hiddenLayerError[j] * hiddenLayer[j][i]);
				}
				inputLayerError[i] = error;

			}

			///////////////////////////////////////


			for (int i = 0; i < inputLayer.size(); i++)
			{
				Neuron neuron = inputLayer[i];
				
					std::vector<long double> inputs;
					inputs.push_back(sample[i]);
					neuron.modify(n, inputLayerError[i], inputs);
					inputLayer[i] = neuron;
				
			}

			for (int i = 0; i < hiddenLayer.size(); i++)
			{
				Neuron neuron = hiddenLayer[i];
				neuron.modify(n, hiddenLayerError[i], inputLayerOutputs);
				hiddenLayer[i] = neuron;
				
			}

			for (int i = 0; i < outputLayer.size(); i++)
			{
				Neuron neuron = outputLayer[i];
				neuron.modify(n, outputLayerError[i], hiddenLayerOutputs);
				outputLayer[i] = neuron;	
			}
		

		// counting how many samples are corectly classify with current weights
		int correcrtly_classified = 0;
		for (auto sample : samples)
		{
			std::string out = this->classify(sample);
			if (out == sample.getClass())
				correcrtly_classified++;

		}

		// remebering best result
		if(correcrtly_classified > best)
			best = correcrtly_classified;
		
		// compute loss error function
		long double err = this->error_fun(samples);

		// remembering lowest error
		if (err < bestErr)
			bestErr = err;
	
		std::cout << err << " || " << bestErr << " || " << correcrtly_classified << " || " << best<< std::endl;

	}


}

long double NeuralNetwork::error_fun(std::vector<Sample> samples)
{
	long double error = 0.0;
	for (auto sample : samples)
	{
		std::vector<long double> inputLayerOutputs;
		std::vector<long double> hiddenLayerOutputs;
		std::vector<long double> outputLayerOutputs;

		inputLayerOutputs.resize(inputLayer.size());
		for (int i = 0; i < inputLayer.size(); i++)
		{
			std::vector<long double> values;
			values.push_back(sample[i]);
			inputLayerOutputs[i] = inputLayer[i].classify(values);
		}


		hiddenLayerOutputs.resize(hiddenLayer.size());
		for (int i = 0; i < hiddenLayer.size(); i++)
		{
			hiddenLayerOutputs[i] = hiddenLayer[i].classify(inputLayerOutputs);
		}

		outputLayerOutputs.resize(outputLayer.size());
		for (int i = 0; i < outputLayer.size(); i++)
		{
			outputLayerOutputs[i] = outputLayer[i].classify(hiddenLayerOutputs);
		}

		long double err = 0.0;
		for (int i = 0; i < outputLayerOutputs.size(); i++)
		{
			long double expectedValue;
			expectedValue = ((sample.getClass() == CLASSES[i]) ? 1.0 : 0.0);
			err += pow(expectedValue - outputLayerOutputs[i],2);
		}

		error += err;


	}

	return error;
}
