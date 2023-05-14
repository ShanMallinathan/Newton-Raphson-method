#include<iostream>
#include<cmath> //for absolute function
#include<functional>//for function<double(double)>
#include<time.h> //To calculate convergence time

//declaring alpha and epsilon values as preprocessor directive
#define epsilon 0.001
#define alpha 1

class NewtonMethod //class encapsulates the Newton Method
{
private:
	//declaring f and df of type function<double(double)>
	std::function<double(double)>f;
	std::function<double(double)>df;

public:
	//member functions
	NewtonMethod(std::function<double(double)> fun, std::function<double(double)> dfun) : f(fun), df(dfun) 	{}//constructor accepting fun and dfun objects
	double error(double, double); //To compute error for tolerance condition
	double Converge(double); //Method to calculate Newton convergence
	
};


double F(double A, double B, double time, double force3) //To calculate overall external force
{
	
	return (A * time + B * sin(alpha * time) - force3);
}

double dF(double A, double B, double time) //To calculate derivative of F
{

	return (A + B * alpha * cos(alpha * time));
}

double NewtonMethod::error(double time1, double time2)
{
	return abs(time1 - time2);
}

double NewtonMethod::Converge(double time)
{
	int counter = 0;
	double external_force, err, tnext, tprev, exetime;
	clock_t begin, finish; //To calculate the time taken
	begin = clock();//clock begin
	printf("\nIteration\t\tTimetamp\t\tExternal Force\n\n");
	do
	{
		counter++;
		if (counter >= 200)//To terminate the loop after 200 iterations
		{
			printf("Too many iterations reached Exiting!!");
			break;
		}
		external_force = f(time);
		tnext = time - external_force / df(time);
		err = error(time, tnext);
		tprev = time;
		time = tnext;
		printf("%d\t\t\t%lf\t\t%lf\n", counter, tprev, external_force);
	}while (err > epsilon);
	finish = clock();//clock end
	exetime = ((double)(finish - begin)) / CLOCKS_PER_SEC;//converting to seconds
	printf("\nParameters:\n Convergence Time: \t\t\t%lfs\n External Force at convergence: \t%lfN\n Execution time: \t\t\t%lfs\n\n", time, f(time), exetime);
	return time;
}