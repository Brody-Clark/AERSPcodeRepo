/*
AERSP 313: Displacement of Simple Harmonic Oscillator
Date: FAll 2018
Author: Brody Clark
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
using namespace std;

void exact(double i, double& ex1, double& ex2);		//prototype for exact equation function
void IEM(double h, double& y1, double& y2);   //prototype for improved euler method function

int main()
{
	double y1, y2, ex1, ex2;	//variable for storing initial conditions. will be changed during process
	double h;			//variable for step size
	double e1, e2;		//variable for error

		//asks user to enter initial conditions
	cout << "please enter the initial conditions:" << endl;
	cout << "Y(0) = ";
	cin >> y1;
	cout << endl;
	cout << "Y'(0) = ";
	cin >> y2;
	cout << endl;
	cout << "please enter the step size: ";
	cin >> h;


	//creates files for outputting estimated and exact values
	ofstream output1;
	output1.open("output1.txt");
	ofstream output2;
	output2.open("output2.txt");
	ofstream exactans1;
	exactans1.open("exact solutions1.txt");
	ofstream exactans2;
	exactans2.open("exact solutions2.txt");
	ofstream errors1;
	errors1.open("percent errors.txt");
	ofstream errors2;
	errors2.open("percent errors2.txt");


	for (double t = 0; t <= 10; t += h)  //loop for reiterating functions to produce values each step
	{


		IEM(h, y1, y2);		//improved euler method function

		output1 << y1 << endl;		//outputs estimated answers for Y1 and Y2 to a file
		output2 << y2 << endl;
		exact(t, ex1, ex2);	 //exact equation function



		exactans1 << ex1 << endl;		//outputs exact answers for Y1 and Y2 to a file
		exactans2 << ex2 << endl;



	}

	output1.close();		//closes files
	exactans1.close();
	exactans2.close();
	output2.close();



	ifstream errorvalues;	//creates file for error percentages 
	errorvalues.open("output1.txt");


	double estimated1[100], estimated2[100];	//creates two arrays whose elements will be compared for calculation

	estimated1[0] = 1;	//initializes the estimated values for Y1 and Y2 to 1 and 0 for comparing to exact values.
	estimated2[0] = 0;

	for (int i = 1; i < (10 / h); i++)
	{

		errorvalues >> estimated1[i];	//reads the estimated values file and puts values in array


	}
	errorvalues.close();
	errorvalues.open("output2.txt");
	for (int i = 1; i < (10 / h); i++)
	{

		//reads the estimated values file and puts values in array
		errorvalues >> estimated2[i];

	}
	errorvalues.close();
	errorvalues.open("exact solutions1.txt");	//opens exact solutions file
	double exacts1[100], exacts2[100];			//creates exact solution array

	for (int i = 0; i < (10 / h); i++)
	{

		errorvalues >> exacts1[i];	//reads file and puts values from exact solution file to array


	}
	errorvalues.close();
	errorvalues.open("exact solutions2.txt");
	for (int i = 0; i < (10 / h); i++)
	{

		//reads file and puts values from exact solution file to array
		errorvalues >> exacts2[i];

	}

	errorvalues.close();







	for (int i = 0; i < (10 / h); i++)
	{

		e1 = 100 * (abs(exacts1[i] - estimated1[i]) / abs(exacts1[i]));	//creates percent error value for Y1 values

		errors1 << setw(4) << fixed << setprecision(3) << e1 << endl;	//outputs to file

		e2 = 100 * (abs(exacts2[i] - estimated2[i]) / abs(exacts2[i]));	//creates percent error value for Y2 values
		errors2 << setw(4) << fixed << setprecision(3) << e2 << endl;


	}

	errors1.close();	//closes files
	errors2.close();

	return 0;
}




void exact(double i, double& ex1, double& ex2)    //exact equation file, accepts the step value, and two reference variables as parameters
{



	double eq1 = exp(-i / 2) * (cos(pow(15, .5) * i / 2) + (1 / pow(15, .5)) * sin(pow(15, .5) * i / 2));	//calculates actual Y1 based on actual equation
	ex1 = eq1;//changes value of ex1
	double eq2 = (((-1) / pow(15, .5)) * (8 * exp(-i / 2) * sin(pow(15, .5) * i / 2)));		//calculates actual value of Y2 based on derivative of actual equation
	ex2 = eq2;	//changes value of ex2



}

void IEM(double h, double& y1, double& y2)		//improved euler method function. accepts step size and two reference variables as parameters.
{

	double y11, y22;		//new values of Y1 and Y2
	double a = y2;	//first function created by differential equation
	double b = -a - 4 * y1;		//second function created by differential equation


	double k1[2] = { a, b };	//K1 array, has element K11 and K12. K11 = a function and K12 = b function

	double astar = a + h * b;	//placeholder for new function called astar. increases b by step size
	double bstar = -astar - 4 * (y1 + h * a);  	//placeholder for new function called bstar. replaces a with astar and increases Y1

	double k2[2] = { astar, bstar };	//new K values based on astar and bstar

	y11 = y1 + (h / 2) * (k1[0] + k2[0]);		//solves for new values of Y1 and Y2
	y22 = y2 + (h / 2) * (k1[1] + k2[1]);

	y1 = y11;	//changes vale of y1 and y2 for next iteration to use. 
	y2 = y22;

}
