/* 	AERSP 312 Project 1: NUMERICAL SOLUTIONS TO THE FALKNER-SKAN EQUATIONS 

    March 14, 2019
    Author: Brody Clark
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

void IEM(double h, double& y1, double& y2, double& y3, double beta);  //prototype for Improved Euler Method function

void bisection(double y2max, double& A, double& B); //function for narrowing in on the proper value of F''(0)

int main()
{
    char ans = 'Y';        //character for while loop continuation
    double y1, y2, y3, A, B;   //variable for storing initial conditions. These will be changed during iterations
    double h;  //variable for step size
    double beta;
    string name = "output at beta = ";
    string base = ".txt"
        double y2max; //this will be set to the value of F' at eta max, and will be compared to 1.

    ofstream output2;	//creates files for outputting estimated F' values (y2)






//outer do/while-loop is for continuously entering beta values and writing data
    do {


        cout << "Enter the value for beta: " << endl;
        cin >> beta;  //sets new value of beta
        A = 0; //A and B contribute to the initial condition for y3
        B = 2;

        for (int j = 0; j <= 10; j++) 	//loops through the Improved euler method & y3 update 20 times
        {


            //opens files for outputting F' values
            output2.open(name + to_string(beta) + base);


            //initializes Y'' based on A and B, y1=0, y2=0 and makes step size .1

            y3 = (A + B) / 2;
            y1 = 0;
            y2 = 0;
            h = .1;


            for (double eta = 0; eta <= 10; eta += h)   	//loop for reiterating IEM function to produce new values each step. 100 total iterations
            {

                IEM(h, y1, y2, y3, beta);     	//Improved Euler Method function call, updates y1, y2, and y3 based on step size h and Beta


                output2 << y1 << endl; //outputs estimated answers for Y1(F) to a file


                y2max = y2;   //sets y2max value based on final F' at max eta value. In this case, the max eta value is 10
            }

            bisection(y2max, A, B);//bisection method function call, updates A and B

                //closes file
            output2.close();



        }
        cout << "do you wish to perform another integration with a different Beta value? Y/N" << endl;  	//allows user to enter different beta values without restarting entire code
        cin >> ans;
    } while (ans == 'Y' || ans == 'y');

    return 0;
}


void bisection(double check, double& A, double& B)  //bisection method for narrowing in on proper y3 value, changes values of A and B based on y2 value (check)
{
    if (check > 1)   	//compares F' at eta max to 1. if greater, lowers value of B
    {
        B = (A + B) / 2.0;
    }
    else if (check < 1)  //if greater, increases A
    {
        A = (A + B) / 2.0;
    }

}

void IEM(double h, double& y1, double& y2, double& y3, double beta)    	//improved Euler method function. accepts step size and three reference variables as parameters.
{

    double y11, y22, y33;         	//new values of Y1 and Y2 and Y3
    double dy = y2;                      	// equation for y1'
    double dy2 = y3;                     	 //y2'
    double dy3 = -y1 * y3 - beta * (1 - pow(y2, 2));   	//equation for F'''

    double k1[3] = { dy, dy2 , dy3 }; //K1 array, has element K11 and K12 and K13

    double y1star = y1 + h * k1[0];   //increased value of y1 based on step size
    double y2star = y2 + h * k1[1];   //increased value of  Y2 based on step size
    double y3star = y3 + h * k1[2];   //increased value of Y3 based on step size
    double k2[3] = { y2star, y3star, -y1star * y3star + beta * (1 - pow(y2star,2)) };  //this becomes the increased values of of the evaluation point based on step size


    y11 = y1 + (h / 2) * (k1[0] + k2[0]);         	//solves for new values of Y1 Y2 and Y3
    y22 = y2 + (h / 2) * (k1[1] + k2[1]);
    y33 = y3 + (h / 2) * (k1[2] + k2[2]);

    y1 = y11; 	//changes value of y1, y2, and y3 for next iteration to use.
    y2 = y22;
    y3 = y33;


}
