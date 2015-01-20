#include <math.h>
#include <gmpxx.h>
#include <iostream>
#include <iomanip>

mpz_class factorial(int n) {
	mpz_class sum(1);
	for(int i = 2; i <= n; i++) {
		sum *= i;
	}

	return sum;
}

double f(double x, int level) {
	mpf_class result(10);
	result = 0;

	int sign = 1;

	for(int i = 1; i <= level; i+=2) {
		//result += sign * pow(x, i) / factorial(i);
		mpf_class num;
		num = sign * pow(x, i);
		num /= factorial(i);

		result += num;
		sign *= -1;
	}

	//std::cout << std::setprecision(10) << std::fixed << result << std::endl;
	return result.get_d();
}
