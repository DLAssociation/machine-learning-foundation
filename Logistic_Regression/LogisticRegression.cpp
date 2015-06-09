/*************************************************
Copyright: 2015 DL Association. All rights reserved.
Author: Yizhen Lao 
Date:09/06/2015
Description: This is tha relazation of Logistic Regression by using gradient descent  
             relizatoin of LogisrcRegression class (cpp fine)
**************************************************/


#include <iostream>
#include <stdio.h>  
#include <math.h>  
#include <string.h>  
#include <vector>
#include "LogisticRegression.h"
#include "ReadTrainingDataset.h"

using namespace std;

#define MAX 20  
#define ITERATION_NUM 50
#define ALPHA 0.01


LogistcRegression::LogistcRegression(vector<vector<double>> data, vector<double> Y)
{
	regress(data,Y);
}


//main algorithms 
void LogistcRegression::regress(vector<vector<double>> data, vector<double> Y)
{
	int N = data.size(); //the number of trained points 
	int M = data[0].size(); // the number of features 

	vector<double> w;
	for (int i = 0; i < M; i++)  //init weight vector 
	{
		w.push_back(0);
	}
	

	//interate enough rounds, or the erro is less than a threshold
	for(int i=0; i < ITERATION_NUM; i++)
	{
		w = update_weights(data,Y,w);
	}
}

// caculate the result of cost function 
double LogistcRegression::caculate_error_in()
{
	return 0;
}

//update the weights vector by using gradient descent 
vector<double> LogistcRegression::update_weights(vector<vector<double>> data, vector<double> Y, vector<double> w)
{
	int N = data.size(); //the number of trained points 
	int M = data[0].size(); // the number of features 

	vector<double> new_W; //new weight vector which needed to be return 
	

	for (int i=0; i < M; i++) 
	{
		double tem1 = 0;

		for (int j =0; j < N; j++)
		{
			double tem2 = 0;
			for (int k=0; k < M; k++)
			{
				tem2 +=w[k]*data[j][k];
			}

			tem2 = tem2*(-Y[j]);
			tem2 = exp(tem2)/(1+exp(tem2));
			tem2 = tem2 * (-Y[j] * data[j][i]);

			tem1 += tem2;
		}

		new_W.push_back((tem1/N)*ALPHA + w[i]);
		
	}

	
	return new_W;
}

int main()  
{  
	//modify the path to your testing CSV file 
	ReadTrainingDataset rtd("C:\\WorkSpace\\GitHub Projects\\NTU_ML_Course\\machine-learning-foundation\\trainingDataset.csv");
	double y[7] = {0,0,0,0,1,1,1};
	vector<double> f(&y[0],&y[7]);

	LogistcRegression lr(rtd.trainingData,f);

}  