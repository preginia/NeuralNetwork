#include "stdafx.h"
#include <vector>
#include "Sample.h"
#include "Datas.h"
#include <time.h>   
#include "NeuralNetwork.h"

const int classesAmount = 8;

int main()
{
	srand(time(NULL));
	std::vector<Sample> samples;

	// loading samples from ecoli.data.txt
	// more about this code on:
	// https://archive.ics.uci.edu/ml/datasets/Ecoli

	Datas::loadData("ecoli.data.txt", samples);
	int propertiesAmount = samples[0].getSize();

	// netowrk creating, arguments are sizes of
	// input hidden and output layer
	NeuralNetwork network(propertiesAmount,16, 8);

	network.train(samples);

	return 0;
}
