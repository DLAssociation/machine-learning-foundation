/*************************************************
Copyright: 2015 DL Association. All rights reserved.
Author: Yizhen Lao 
Date:09/06/2015
Description: This is tha relazation of Logistic Regression by using gradient descent  
             Definition of LogisrcRegression class(head fine)
**************************************************/


#include <iostream>
#include <vector>
using namespace std;



class  LogistcRegression
{
public:
	 LogistcRegression(vector<vector<double>> data, vector<double> Y);
	

private: 
	double caculate_error_in();
	void regress(vector<vector<double>> data, vector<double> Y);
	vector<double> update_weights(vector<vector<double>> data, vector<double> Y, vector<double> w);

};


