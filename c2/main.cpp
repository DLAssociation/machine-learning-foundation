//
//  main.cpp
//  c2
//
//  Created by Ifly Hsueh on 28/05/15.
//  Copyright (c) 2015 DL Association. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

struct Item {
    int x0 = 1;
    double x1, x2, x3, x4;
    int label;
};

struct Weight{
    double w0, w1, w2, w3, w4;
}W0 = { 0, 0, 0, 0, 0 };

//Sign function
int sign(int s) {
    if(s < 1)
        return -1;
    else if (s >1)
        return 1;
    else
        return 0;
}

//Dot Product
double dotProduct(Item item, Weight weight){
    return item.x0 * weight.w0 + item.x1 * weight.w1 + item.x2 * weight.w2 + item.x3 * weight.w3 + item.x4 * weight.w4;
}

//Weight update
Weight updateWeight(Item item, Weight weight){
    Weight newWeight;
    newWeight.w0 = weight.w0 + item.x0 * item.label;
    newWeight.w1 = weight.w1 + item.x1 * item.label;
    newWeight.w2 = weight.w2 + item.x2 * item.label;
    newWeight.w3 = weight.w3 + item.x3 * item.label;
    newWeight.w4 = weight.w4 + item.x4 * item.label;
    return newWeight;
}

//PLA
Weight goPLA(Item *item){
    Weight wit = W0;
    vector<Item> vItem;
    for (int i = 0; i < 4; i ++) {
        vItem.push_back(item[i]);
    }
    for (vector<Item>::iterator iter = vItem.begin(); iter != vItem.end(); ++ iter) {
        if ((*iter).label != sign(dotProduct(*iter, wit))) {
            wit = updateWeight(*iter, wit);
            iter = vItem.begin();
        }
    }
    return wit;
}

int main(int argc, const char * argv[]) {
    Item *data = new Item[4];
    data[0].x0 = 1; data[0].x1 = 1; data[0].x2 = 2; data[0].x3 = 1; data[0].x4 = 1; data[0].label = 1;
    data[1].x0 = 1; data[1].x1 = 2; data[1].x2 = 3; data[1].x3 = 1; data[1].x4 = 4; data[1].label = 1;
    data[2].x0 = 1; data[2].x1 = 3; data[2].x2 = 2; data[2].x3 = 1; data[2].x4 = 2; data[2].label = -1;
    data[3].x0 = 1; data[3].x1 = 2; data[3].x2 = 4; data[3].x3 = 4; data[3].x4 = 2; data[3].label = -1;
    Weight wit = goPLA(data);
    cout<<"The final w vector:"<<endl;
    cout<<"w0 = "<<wit.w0<<"; w1 = "<<wit.w1<<"; w2 = "<<wit.w2<<"; w3 = "<<wit.w3<<"; w4 = "<<wit.w4<<endl;
    return 0;
}