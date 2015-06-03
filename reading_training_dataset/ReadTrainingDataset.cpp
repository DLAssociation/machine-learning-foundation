/*************************************************
Copyright: 2015 DL Association. All rights reserved.
Author: Yizhen Lao 
Date:03/06/2015
Description: This is tha relazation of class(ReadTrainingDataset) for trainning data reading for testing of all algrithms in this project 
**************************************************/


#include "ReadTrainingDataset.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

ReadTrainingDataset:: ReadTrainingDataset(string path)
{
	filePath = path;
	readCSV();
}


vector<vector<double >> ReadTrainingDataset::getTrainingDataset()
{
	return trainingData; 
}

void ReadTrainingDataset::readCSV()
{
	


	ifstream fin(filePath);

    string line; 

    while (getline(fin, line)) 
    {
       istringstream sin(line); 
       vector<string> fields; 
	   string field;
	   while (getline(sin, field, ',')) 
	   {
	   fields.push_back(field); 
       }

	    vector<double> singelData;

	   dim = fields.size() - 1;

	   for (int i = 0; i < fields.size(); i++)
	   {
		   cout<<fields[i]<<"  ";
		   string str = fields[i];
		   
		   singelData.push_back(atof(str.c_str()));
	   }
	   cout<<" "<<endl; 
	   trainingData.push_back(singelData);
 }
}
					 

					 