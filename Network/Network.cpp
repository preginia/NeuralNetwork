#include "stdafx.h"
#include <vector>
#include "Sample.h"
#include "Datas.h"
#include <time.h>   
#include "NeuralNetwork.h"
#include <iostream>


#include <filesystem>
#include <experimental/filesystem>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgproc/imgproc.hpp>

const int classesAmount = 8;

int main()
{
	srand(time(NULL));
	std::vector<Sample> samples;

	std::cout << "start" << std::endl;
	//int i = 2;
	//for (int i = 0; i < 10; i++)
	{
		std::string path = "/training/";
		//path += std::to_string(i);/*"/6.png"*/

		std::string current_path = std::experimental::filesystem::current_path().generic_string();
		//std::cout << current_path;
		path = current_path + path;
		std::cout << path;
		for (auto entry : std::experimental::filesystem::directory_iterator(path))
		{

			for (int i = 0; i < 10; i++)
			{

				std::string path2 = entry.path().u8string() + "\\" + std::to_string(i) + "\\";
				for (auto entry2 : std::experimental::filesystem::directory_iterator(path2))
				{
					cv::Mat image = cv::imread(entry2.path().u8string());
					//std::cout << image.size() << std::endl;
					cv::Mat smallImage;

					cv::resize(image, smallImage, cv::Size(30, 30), 0, 0, cv::INTER_LANCZOS4);


					cv::Mat greyMat;
					cv::cvtColor(smallImage, greyMat, cv::COLOR_BGR2GRAY);


					std::vector<long double> sampleProperties(30 * 30);
					int index = 0;
					for (int j = 0; j < greyMat.rows; j++)
					{

						for (int k = 0; k < greyMat.cols; k++)
						{
							int val = (int)greyMat.at<uchar>(j, k);
							double norm = ((double)val - 0.0) / (255.0 - 0.0);
							sampleProperties[index] = norm;
							index++;
						}
					}

					std::string label = std::to_string(i);
					Sample sample(sampleProperties, label);
					samples.push_back(sample);

				}
			}

			//break;

		}


	}

	// loading samples from ecoli.data.txt
	// more about this code on:
	// https://archive.ics.uci.edu/ml/datasets/Ecoli

	//Datas::loadData(/*"ecoli.data.txt"*/"wifi.txt", samples);
	//int propertiesAmount = samples[0].getSize();

	// netowrk creating, arguments are sizes of
	// input hidden and output layer
	NeuralNetwork network(900,300, 10);

	network.train(samples);

	return 0;
}
