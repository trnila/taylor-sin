#include <math.h>
#include <gmpxx.h>
#include <iostream>
#include <iomanip>

void factorial(int n, mpf_t &result) {
	mpf_set_ui(result, 1);

	for(int i = 2; i <= n; i++) {
		mpf_mul_ui(result, result, i);
	}
}

double f(double x, int level) {
	mpf_t fact;
	mpf_init(fact);

	mpf_t result;
	mpf_init(result);
	mpf_set_ui(result, 0);

	bool positive = true;

	mpf_t temp;
	mpf_init(temp);

	for(int i = 1; i <= level; i+= 2) {
		//result += sign * pow(x, i) / factorial(i);

		factorial(i, fact);

		mpf_set_d(temp, x); // temp = x
		mpf_pow_ui(temp, temp, i); // x^i

		//mpf_mul_ui(temp, temp, sign); // sign * x^i
		if(!positive) {
			mpf_neg(temp, temp);
		}
		positive = !positive;

		mpf_div(temp, temp, fact); // sign * x^i / factorial(i)

		mpf_add(result, result, temp); // result += temp
	}

	double resultDouble = mpf_get_d(result);
	mpf_clears(fact, result, temp, NULL);
	return resultDouble;
}
