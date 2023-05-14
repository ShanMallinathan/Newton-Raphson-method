#include<iostream>
#include<functional>//for function<double(double)>
#include<time.h> //To calculate convergence time
#include "NewtonMethod.h" //Newon method class definition as a header


int main()
{
	int choice;
	double A, B; // coefficients of F1 and F2
	double init_time = 1;
	printf("Time of External Force convergence in an Autonomous Robot\n");
	printf("\nThe equation of calculating the external force is as follows\n\nF = At + B sin(alpha*t) - F3\n\nWhere t is the timestamp");
	printf("\nDefault equation: 0.55t - 0.3 sin (alpha*t) - F3");
	printf("\nPress 0 for default equaion and any number for modified equation: ");
	scanf("%d", &choice); // switching between default and custom equation
	if (choice == 0)
	{
		A = 0.55;//default values as per the assignment sheet
		B = -0.3;
	}
	else
	{
		printf("\nEnter the value for A:");//user deifined values
		scanf("%lf", &A);
		printf("\nEnter the value for B:");
		scanf("%lf", &B);
	}
	printf("\n____________________Considering F3 as 5 N________________________\n");
	//case 1 F3 = 5N
	double f3 = 5;
	//creating an object to NewtinMethod by passing the objects of function F and dF to the constructor
	NewtonMethod soln ([&A, &B, &f3](double t) { return F(A, B, t, f3); }, [&A, &B](double t) { return dF(A, B, t); });
	soln.Converge(init_time);
	printf("\n\n____________________Considering F3 as 10 N________________________\n\n");
	//case 2 F3 = 10N
	f3 = 10;
	NewtonMethod soln1([&A, &B, &f3](double t) { return F(A, B, t, f3); }, [&A, &B](double t) { return dF(A, B, t); });
	//Calling the convergence function to calculate the roots
	soln.Converge(init_time);
	return 0; 
}