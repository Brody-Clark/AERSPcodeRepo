//matrix operations in C


#include <iostream>
#include <cmath>

using namespace std;

void matrixmultiply(double[][col], double[][col], double[][col], int);
void conversion(double[], int, double[][col], double[]);
void transpose(double[][col], double[][col], int);
void crossproduct(double a[], double b[], double result[], int row);
double magnitude1(double a[], int row);
void normalize(double a[], double mag, double result[], int row);
void magnitude2(double a[], int row, double result);
void vectorsub(double a[], double b[], double result[], int row);
void dotproduct(double a[], double b[], double result, int row);
double dotproduct2(double a[], double b[], int row);

int main()
{



	return 0;
}

void matrixmultiply(double c1[][col], double c2[][col], double result[][col], int row)	//multiplies two matrices
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			result[i][j] = 0;
		}
	}
	for (int x = 0; x < row; x++)
	{

		for (int a = 0; a < row; a++)
		{
			for (int b = 0; b < col; b++)
			{
				result[x][a] += c1[x][b] * c2[b][a];
			}
		}
	}

}

void transpose(double c[][col], double cT[][col], int row)	//transposes a matrix
{

	for (int x = 0; x < row; x++)
	{
		for (int y = 0; y < col; y++)
		{
			cT[y][x] = c[x][y];
		}
	}





}
double magnitude1(double a[], int row)	//magnitude of  a vector that doesnt need to be used more than once
{
	double result = 0;
	double argument = 0;
	for (int i = 0; i < row; i++)
		argument += pow(a[i], 2);
	result = pow(argument, 0.5);
	return result;
}
void magnitude2(double a[], int row, double result)	//magnitude of  a vector for quantity that is used repeatedly
{

	double argument = 0;
	for (int i = 0; i < row; i++)
		argument += pow(a[i], 2);
	result = pow(argument, 0.5);

}
void crossproduct(double a[], double b[], double result[], int row)
{
	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = -(a[0] * b[2] - a[2] * b[0]);
	result[2] = a[0] * b[1] - a[1] * b[0];


}
void dotproduct(double a[], double b[], double result, int row)
{
	for (int i = 0; i < row; i++)
		result += a[i] * b[i];



}
double dotproduct2(double a[], double b[], int row)
{
	double result = 0;
	for (int i = 0; i < row; i++)
		result += a[i] * b[i];

	return result;

}

void normalize(double a[], double mag, double result[], int row)
{
	for (int i = 0; i < row; i++)
	{
		result[i] = a[i] / mag;
	}


}
void vectorsub(double a[], double b[], double result[], int row)
{
	for (int i = 0; i < row; i++)
		result[i] = a[i] - b[i];


}