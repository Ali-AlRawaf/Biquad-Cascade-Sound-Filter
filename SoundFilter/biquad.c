#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	double x[3] = {0.0}, y[3] = {0.0};
	double g = atof(argv[1]), a = atof(argv[2]), b = atof(argv[3]), c = atof(argv[4]), d = atof(argv[5]); //get coefficients

	if(argc != 6)
	{
		perror("Must have 6 arguments!\n");
		return 1;
	}
	
	while(scanf("%lg", &x[2]) == 1)
	{
		y[2] = g * (x[2] + a * x[1] + b * x[0]) - c * y[1] - d * y[0];  //recursive sequence formula
		printf("%g\n", y[2]); //print output sequence
		x[0] = x[1]; //push values through the array for next iteration
		x[1] = x[2];
		y[0] = y[1];
		y[1] = y[2];
	}
	return 0;
}