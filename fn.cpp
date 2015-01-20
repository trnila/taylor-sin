#include <math.h>

long long factorial(int n) {
	long long sum = 1;
	for(int i = 2; i <= n; i++) {
		sum *= i;
	}

	return sum;
}

double f(double x, int level) {
	double result = 0;
	int sign = 1;

	for(int i = 1; i <= level; i+=2) {
		result += sign * pow(x, i) / factorial(i);

		sign *= -1;
	}

	return result;
}
