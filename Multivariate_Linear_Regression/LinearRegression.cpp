/*************************************************
Copyright: 2015 DL Association. All rights reserved.
Author: Yizhen Lao 
Date:08/06/2015
Description: This is tha relazation of multivariate linear regression 
**************************************************/


#include <stdio.h>  
#include <math.h>  
#include <string.h>  
#include <vector>
#include "ReadTrainingDataset.h"
  
#define MAX 20  
#define E 0.000000001  

using namespace std;
  
/** 
 * caculate the norm of the matrix 
 */  
double calculate_A( double src[][MAX], int n )  
{  
    int i,j,k,x,y;  
    double tmp[MAX][MAX], t;  
    double result = 0.0;  
      
    if( n == 1 )  
    {  
        return src[0][0];  
    }  
      
    for( i = 0; i < n; ++i )  
    {  
        for( j = 0; j < n - 1; ++j )  
        {  
            for( k = 0; k < n - 1; ++k )  
            {  
                x = j + 1;  
                y = k >= i ? k + 1 : k;  
                  
                tmp[j][k] = src[x][y];  
            }  
        }  
          
        t = calculate_A( tmp, n - 1 );  
          
        if( i % 2 == 0 )  
        {  
            result += src[0][i] * t;  
        }  
        else  
        {  
            result -= src[0][i] * t;  
        }  
    }  
  
    return result;  
}  
  
/** 
 * caculate the adjoint matrix  
 */  
void calculate_A_adjoint( double src[MAX][MAX], double dst[MAX][MAX], int n )  
{  
    int i, j, k, t, x, y;  
    double tmp[MAX][MAX];  
  
    if( n == 1 )  
    {  
        dst[0][0] = 1;  
        return;  
    }  
      
    for( i = 0; i < n; ++i )  
    {  
        for( j = 0; j < n; ++j )  
        {  
            for( k = 0; k < n - 1; ++k )  
            {  
                for( t = 0; t < n - 1; ++t )  
                {  
                    x = k >= i ? k + 1 : k ;  
                    y = t >= j ? t + 1 : t;  
                      
                    tmp[k][t] = src[x][y];  
                }  
            }  
              
            dst[j][i]  =  calculate_A( tmp, n - 1 );  
              
            if( ( i + j ) % 2 == 1 )  
            {  
                dst[j][i] = -1*dst[j][i];  
            }  
        }  
    }  
}  
  
/** 
 * Caculate teh inverse matrix. 
 */  
int calculate_A_inverse( double src[MAX][MAX], double dst[MAX][MAX], int n )  
{  
    double A = calculate_A( src, n );  
    double tmp[MAX][MAX];  
    int i, j;  
  
    if ( fabs( A - 0 ) <= E )  
    {  
        printf("inverse matrix do not exit£¡\n");  
        return 0;  
    }  
  
    calculate_A_adjoint( src, tmp, n );    
  
    for( i = 0; i < n; ++i )    
    {    
        for( j = 0; j < n; ++j )    
        {    
            dst[i][j] = (double)( tmp[i][j] / A );  
        }    
    }  
  
    return 1;  
}  
  
/** 
 * print the matrix  
 */  
void print_M( double M[][MAX], int n )  
{  
    int i, j;  
      
    for ( i = 0; i < n; ++i )  
    {  
        for ( j = 0; j < n; ++j )  
        {  
            printf("%lf ", M[i][j]);  
        }  
          
        printf("\n");  
    }  
}  

//Algorithms of multivariate linear regression 
void regress(vector<vector<double>> data, vector<double> y)
{ 
	int M = data.size();
	int N = data[0].size();

	double result[MAX][MAX];
    memset( result, 0, sizeof( result ) );
	for (int i = 0; i< N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double tem = 0;
			for (int k = 0; k < M; k++)
			{
				tem += data[k][i]*data[k][j];
			}
			result[i][j] = tem;
		}
	}

	double B[MAX];
	 memset( B, 0, sizeof( B ) );
	for (int i = 0; i < N; i++)
	{
		double tem = 0;
		for (int j = 0; j < M; j++)
		{
			tem += data[j][i]*y[j];
		}
		B[i] = tem;
	}

	double dst[MAX][MAX];
	int  is_exist = calculate_A_inverse( result, dst, N);

	double C[MAX];
	memset( C, 0, sizeof( C ) );
	for (int i = 0; i < N; i++)
	{
		double tem = 0;
		for (int j = 0; j < N; j++)
		{
			tem += dst[i][j]*B[j];
		}
		C[i] = tem;
	}

	cout<<"The resuult: "<<endl;
	for (int i=0; i < N; i++)
	{
		cout<<"Coefficients"<< i +1 << ": "<< C[i]<<endl;
	}
}
  
/** 
 * main 
 */  
int main()  
{  
	//modify the path to your testing CSV file 
	ReadTrainingDataset rtd("C:\\WorkSpace\\GitHub Projects\\NTU_ML_Course\\machine-learning-foundation\\trainingDataset.csv");
	double y[7] = {4,6,8,5,7,12,16};
	vector<double> f(&y[0],&y[7]);
	regress(rtd.trainingData,f);

}  
 