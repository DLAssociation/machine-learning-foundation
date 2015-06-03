//
//  main.cpp
//  c2
//
//  Created by Ifly Hsueh on 28/05/15.
//  Modified by Yizhen Lao on 03/06/2015
/****************************************************
1. support for dynamic mutil tuples trainning data
2. change coding style to C++ 
3. support for standard self-denined data reading method throgh CSV 
***************************************************/
//  Copyright (c) 2015 DL Association. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>
#include "ReadTrainingDataset.h"

using namespace std;

struct Item 
{
    int x0 ;
    double x1, x2, x3, x4;
    int label;
};

struct Weight
{
    double w0, w1, w2, w3, w4;
} W0 = { 0, 0, 0, 0, 0 };

//Sign function
int sign(int s) 
{
    if(s < 1)
        return -1;
    else if (s >1)
        return 1;
    else
        return 0;
}

//Dot Product
double dotProduct(Item item, Weight weight)
{
    return item.x0 * weight.w0 + item.x1 * weight.w1 + item.x2 * weight.w2 + item.x3 * weight.w3 + item.x4 * weight.w4;
}

//Weight update
Weight updateWeight(Item item, Weight weight)
{
    Weight newWeight;
    newWeight.w0 = weight.w0 + item.x0 * item.label;
    newWeight.w1 = weight.w1 + item.x1 * item.label;
    newWeight.w2 = weight.w2 + item.x2 * item.label;
    newWeight.w3 = weight.w3 + item.x3 * item.label;
    newWeight.w4 = weight.w4 + item.x4 * item.label;
    return newWeight;
}

//PLA
Weight goPLA(vector<Item> item)
{
    Weight wit = W0;
    vector<Item> vItem;

	vItem = item;

	/*for (int i = 0; i < sizeof(item); i ++) 
	{
        vItem.push_back(item[i]);
    }*/
    for (vector<Item>::iterator iter = vItem.begin(); iter != vItem.end(); ++ iter)
	{
		//mistake occur 
        if ((*iter).label != sign(dotProduct(*iter, wit)))
		{
            wit = updateWeight(*iter, wit);
            iter = vItem.begin();  //after updating, iterate from begin again until no uncorrected prediction 
        }
    }
    return wit;
}

int main(int argc, const char * argv[]) 
{ 
	//please set the path of your trainning dataset here 
	ReadTrainingDataset rtd("C:\\WorkSpace\\GitHub Projects\\NTU_ML_Course\\machine-learning-foundation\\trainingDataset.csv");
	vector<Item> data;


	for (int i =0; i < rtd.trainingData.size(); i++)
	{
		Item data_ ;
		data_.x0 = rtd.trainingData[i][0];
		data_.x1 = rtd.trainingData[i][1];
		data_.x2 = rtd.trainingData[i][2];
		data_.x3 = rtd.trainingData[i][3];
		data_.x4 = rtd.trainingData[i][4];
		data_.label = rtd.trainingData[i][5];

		data.push_back(data_);
	}

    Weight wit = goPLA(data);

    cout<<"The final w vector:"<<endl;
    cout<<"w0 = "<<wit.w0<<"; w1 = "<<wit.w1<<"; w2 = "<<wit.w2<<"; w3 = "<<wit.w3<<"; w4 = "<<wit.w4<<endl;
    return 0;
}