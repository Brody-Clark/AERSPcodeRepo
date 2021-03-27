/* 	AERSP 312 Project 2: Converging-Diverging Nozzle with a Normal Shock
    April 21, 2019
    Author: Brody Clark
    desc: see README
*/
#include <iostream>

using namespace std;
void bisection(double check, double value, double& A, double& B);
double tempRatio(double Ma);

//global constant: tolerance for bisection method.
float tolerance = 0.0025;  

int main()
{
    double  M2, M1, Me, Ae_A2star, As_A1star, A2_A2star, Ae, Y, P1_P01, P2_P02, P02_P01, Pe_P01, Pe_P02, P2_P1, A2star_A1star, holder, Ae_A1star, A, B;
    double P2_P01 = P2_P02 * P02_P01;
    Ae = 3.14 / 8;
    Ae_A1star = 4.0;
    Y = 1.4;//GAMMA


    /*          	Initialized parameter limits for As/A1*     	*/

    double As = 0;
    double Bs = 8;
    bool over = false;

    /*           	Outer loop for checking if Pe/Po1 is correct , 	it is over when the calculated pe/p01 value is  within tolerance to 0.5      */

    //over when convergence is found
    while (!over)
    {
        /* Initialize parameters for M1   */
        A = 0;
        B = 10;
        As_A1star = (As + Bs) / 2;


        /*  Loop for checking /updating M1 to fit the calculated As/A1* value   */
        over = false;
        while (!over)
        {
            M1 = (A + B) / 2;
            holder = (1 / M1) * pow(1 + 0.2 * M1 * M1, 3) / 1.728;
            if (holder < As_A1star + tolerance && holder > As_A1star - tolerance)
                over = true;
            else
            {

                bisection(holder, As_A1star, A, B);
            }
        }

        P1_P01 = pow((1 + ((Y - 1) / 2) * M1 * M1), (-Y / (Y - 1)));
        P2_P1 = 1 + (2 * Y) / (Y + 1) * (pow(M1, 2) - 1);
        double numerator = 2 + (Y - 1) * M1 * M1;
        double denominator = 2 * Y * M1 * M1 - Y + 1;

        M2 = pow(numerator / denominator, 0.5);

        P2_P02 = pow((1 + ((Y - 1) / 2) * M2 * M2), (-Y / (Y - 1)));

        P02_P01 = pow(P2_P02, -1) * P2_P1 * P1_P01;

        A2_A2star = (1 / M2) * pow(1 + 0.2 * M2 * M2, 3) / 1.728;

        A2star_A1star = pow(A2_A2star, -1) * As_A1star;
        Ae_A2star = Ae_A1star * pow(A2star_A1star, -1);


        /* Initialized parameters for Me,  it is known to be less than 1     */
        A = 0;
        B = 1;

        /*  Loop for /checking/ updating Me based on calculated Ae/A2*   */
        over = false;
        while (!over)
        {
            Me = (A + B) / 2;
            holder = (1 / Me) * pow((1 + 0.2 * Me * Me), 3) / 1.728;
            if (holder <= Ae_A2star + tolerance && holder >= Ae_A2star - tolerance)
                over = true;
            else
            {


                bisection(holder, Ae_A2star, B, A);  	//Here the B and A values are switched to converge for this case
            }
        }


        Pe_P02 = pow((1 + 0.2 * Me * Me), -3.5);

        Pe_P01 = Pe_P02 * P02_P01; //this needs to be 0.5



        /* this controls the outer loop condition. checks Pe/Po1  and updates As/A1* parameters accordingly	*/
        if (Pe_P01 < 0.5 + tolerance && Pe_P01 > 0.5 - tolerance)
            over = true;
        else
        {

            over = false;
            bisection(Pe_P01, 0.5, Bs, As); //continues bisection method if not converged
        }

    }



    /* Temperature calculations */
    double Tstar_T01 = 1.2;
    double T1_T01 = tempRatio(M1);
    double T2_T01 = tempRatio(M2);
    double Te_T01 = tempRatio(Me);


    /* outputs all final values*/
    cout << "Me " << Me << endl;
    cout << "M1: " << M1 << endl;
    cout << "P1/P01: " << P1_P01 << endl;
    cout << " p02_p01: " << P02_P01 << endl;
    cout << " p2_p01: " << P2_P01 << endl;
    cout << " A2/A2star: " << A2_A2star << endl;
    cout << " Ae/A2star: " << Ae_A2star << endl;
    cout << " pe/p02: " << Pe_P02 << endl;
    cout << " M2: " << M2 << endl;
    cout << "As_A1star: " << As_A1star << endl;
    cout << "Pe_P01: " << Pe_P01 << endl;
    cout << "T* / T01" << Tstar_T01 << endl;
    cout << "T1/t01" << T1_T01 << endl;
    cout << "t2/t02: " << T2_T01 << endl;
    cout << "te/t01: " << Te_T01 << endl;

    return 0;
}

double tempRatio(double Ma) //temperature ratio calculation. Accepts mach number as parameter.
{
    return (1 + 0.2 * Ma * Ma);
}

void bisection(double check, double value, double& A, double& B)  //bisection method for narrowing in on proper A and B parameters
{
    if (check > value)
    {
        B = (A + B) / 2.0;
    }
    else if (check < value)
    {
        A = (A + B) / 2.0;
    }
}

