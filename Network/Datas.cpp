#include "stdafx.h"
#include "Datas.h"
#include <fstream>


void Datas::loadData(std::string path, std::vector<Sample>& samples)
{
	std::ifstream dataFile;
	dataFile.open(path);

	if (dataFile.fail())
		return;
	std::string name;
	long double feature1;
	long double feature2;
	long double feature3;
	long double feature4;
	long double feature5;
	long double feature6;
	long double feature7;
	std::string label;

	while (dataFile.peek() != EOF) {
		//dataFile >> name;
		dataFile >> feature1;
		dataFile >> feature2;
		dataFile >> feature3;
		dataFile >> feature4;
		dataFile >> feature5;
		dataFile >> feature6;
		dataFile >> feature7;
		dataFile >> label;

		std::vector<long double> properties;

		properties.push_back(feature1);
		properties.push_back(feature2);
		properties.push_back(feature3);
		properties.push_back(feature4);
		properties.push_back(feature5);
		properties.push_back(feature6);
		properties.push_back(feature7);

		Sample patient(properties, label);
		samples.push_back(patient);
	}
}

Datas::Datas()
{
}


Datas::~Datas()
{
}
