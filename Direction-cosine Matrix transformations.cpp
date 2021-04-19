//Single Directional Cosine Matrix transformaiton of Vector


#include <iostream>
#include <cmath>
using namespace std;


 const int row = 3, col = 3;	//using arrays with predefined row and column as 3. matrices will always be 3x3, vectors will always be 3x1
 void rotationX(double b, double r[][col], const int num);
 void rotationZ(double, double[][col], const int);
 void rotationY(double, double[][col], const int);
 void matrixmultiply(double[][col], double[][col], double[][col], const int);
 void conversion(double[], const int, double[][col], double[]);


int main()
{
	//const int row = 3, col = 3;
	double vectorA[row] = { 0,0,0 }, vectorB[row] = { 0,0,0 };	//vectors. change vectorA to be desired original vector
	double xRot[row][col], yRot[row][col], zRot[row][col];	//matrices that will become DCMs

	double angle=1;	//measured in raidans. CHNAGE ACCORDING TO DESIRED INITIAL CONDITIONS

	// xRot becomes rotation matrix around x-axis by angle 'angle'
	rotationX(angle, xRot, row);


	// yRot becomes rotation matrix around y-axis by angle 'angle'
	rotationY(angle, yRot, row);


	// zRot becomes rotation matrix around z-axis by angle 'angle'
	rotationZ(angle, zRot, row);



	//transforms vectorA around x-Axis by angle 'angle'. vectorB is the result.
	conversion(vectorA, row, xRot, vectorB);



	/*
	****************************************************************
	****************  For use with Euler Angle Rotaitons  **********
	****************************************************************
	*/

	//Euler angle rotations are a series of 3 single-axis rotations combined to creata unique rotation matrix. 
	//this sequence can be a 3-2-1 roation, 1-2-3, 2-3-1, 2-1-3, ....etc.
	//Euler Angle rotations can be used to describe an object's state in space from any reference coordinate system.
	//to create an Euler angle DCM, you have 3 distinct angles (theta, phi, psi) that each create their own DCM
	//then these DCM's are multiplied in the proper order to creat the final DCm (state transition matrix)

	//NOTE: EULER ANGLE ROTATIONS EXPERIENCE GIMBAL LOCK EFFECTS (I.E. DIVIDE BY ZERO ERROR) UNDER CERTAIN CONDITIONS, CONSIDER USING QUATERNIONS INSTEAD

	double theta, phi, psi;

	//this example does  3-2-1 rotation;
	theta = .8; phi = .01; psi = 0.4;

	rotationX(theta, xRot, row);
	rotationY(phi, yRot, row);
	rotationZ(psi, zRot, row);

	double STM[row][col];	//will be created by multiplying xRot * yRot * zRot from left to right

	matrixmultiply(xRot, yRot, STM, row);
	matrixmultiply(STM, zRot, STM, row);

	conversion(vectorA, row, STM, vectorB);

	//vectorB is the result of the rotation of vectorA. these vectors could be position vectors of a body in space for example.

	return 0;
}
void rotationX(double b, double r[][col], const int num)//creates a DCM using an angle 'b' around axis-1
{

	double rotation1[3][3] = { { 1,0,0 },{ 0, cos(b), sin(b) },{ 0, -sin(b), cos(b) } };	//first axis rotaiton
	for (int x = 0; x < num; x++)
	{
		for (int y = 0; y < col; y++)
		{
			r[x][y] = rotation1[x][y];
		}

	}

}
void rotationZ(double b, double r[][col], const int num)//creates a DCM using an angle 'b' around axis-3
{

	double rotation3[3][3] = { { cos(b), sin(b), 0 },{ -sin(b), cos(b), 0 },{ 0, 0, 1 } };

	for (int x = 0; x < num; x++)
	{
		for (int y = 0; y < col; y++)
		{
			r[x][y] = rotation3[x][y];
		}

	}

}
void rotationY(double b, double r[][col], const int num)	//creates a DCM using an angle 'b' around axis-2
{

	double rotation2[3][3] = { { cos(b),0, -sin(b) },{ 0, 1, 0 },{ sin(b), 0, cos(b) } };

	for (int x = 0; x < num; x++)
	{
		for (int y = 0; y < col; y++)
		{
			r[x][y] = rotation2[x][y];
		}

	}

}

void conversion(double q[], const int  num, double c[][col], double q2[])	//converts a vector 'q' from one coordinate system to another using DCM matrix 'c'
{
	for (int i = 0; i < num; i++)
	{
		q2[i] = 0;
		for (int j = 0; j < col; j++)
		{

			q2[i] += c[i][j] * q[j];
		}




	}
}

void matrixmultiply(double c1[][col], double c2[][col], double result[][col], const int row)	//multiplies two matrices
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


