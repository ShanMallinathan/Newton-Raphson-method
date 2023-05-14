#include<stdio.h>
#include<math.h>//for fabs function
#include<time.h>//for clock function

//defining alpha and epsilon as preprocessor directive
#define alpha 1
#define epsilon 0.001

//Function declaration
double F(double, double); //function to calculate overall external force
double dF(double); // function to return the derivatie of the above function
double Converge(double, double); //Function to calculate time using Newtons method

void main()
{
	double t = 1;  //initialising timestamp as 1
	double  f3; //Force F3
	f3 = 5;
	printf("\nConsidering F3 as 5 N\n");
	Converge(t, f3);
	f3 = 10;
	printf("\nConsidering F3 as 10 N\n");
	Converge(t, f3);

}

double F(double time, double F3) //To calculate overall external force
{
	return (0.55 * time - 0.3 * sin(alpha * time) - F3);
}


double dF(double time) // To calculate the derivative of overall external force
{
	return (0.55 - 0.3 * alpha * cos(alpha * time));
}

double Converge(double t, double f3) //Function to calculate time using Newtons method
{
	int counter = 0;
	//declaration of next time stamp, difference between t and tnext, time of execution and previous time
	double tnext, error, external_force, exetime, tprev;  
	clock_t begin, finish; //To calculate the time taken
	begin = clock(); //noting timestamp start
	printf("\nIteration\t\tTimetamp\t\tExternal Force\n\n");
	//loop to calculate tnext using newton method and terminate once convergence reached epsilon
	do {
		counter++;
		if (counter >= 200)//To terminate the loop after 200 iterations
		{
			printf("Too many iterations reached Exiting!!");
			break;
		}
		external_force = F(t, f3);
		tnext = t - external_force / dF(t); //Newton's equation for predicting the next timestamp
		error = tnext - t;
		tprev = t;
		t = tnext;
		printf("%d\t\t\t%lf\t\t%lf\n", counter, tprev, external_force);
	} while (fabs(error) > epsilon);
	finish = clock();//noting timestamp end
	exetime = ((double)(finish - begin)) / CLOCKS_PER_SEC;//Converting the cycle time to seconds
	printf("\nParameters:\n Convergence Time: \t\t\t%lfs\n External Force at convergence: \t%lfN\n Execution time: \t\t\t%lfs\n\n", t, F(t, f3), exetime);
	return t;

}