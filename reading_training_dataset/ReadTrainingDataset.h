/*************************************************
Copyright: 2015 DL Association. All rights reserved.
Author: Yizhen Lao 
Date:03/06/2015
Description: This is tha class for trainning data reading for testing of all algrithms in this project 
**************************************************/


#ifndef READ_TRAINING_DATASET_
#define READ_TRAINING_DATASET_
#include <iostream>
#include <vector>

using namespace std;

class ReadTrainingDataset
{


public:
	int dim;
	string filePath;

	vector<vector<double>> trainingData;
	ReadTrainingDataset(string path);
	vector<vector<double>> getTrainingDataset();
	void readCSV();
};

#endif READ_TRAINING_DATASET_