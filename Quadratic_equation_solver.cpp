#include <stdio.h>
#include <math.h>
#include <assert.h>

enum roots {
	INF, LINEAR_1, LINEAR_0, QUADRATIC_2, QUADRATIC_1, QUADRATIC_0
};

int input(double* coeff) {
	printf("Let's solve an quadratic equation like  ax^2 + bx + c = 0.\nPlease enter a, b and c.\n");

	for (int i = 0; i < 3; i++) {
		if (scanf_s("%lg", coeff + i) == 0) {
			printf("Wrong number\n");
			return 1;
		}
	}
}

int linear_equation_solver(double** x1, double** x2, double b, double c) {
	if ((b == 0) && (c == 0))
		return INF;
	if (b != 0) {
		assert(b != 0);

		**x1 = (-c / b);
		return LINEAR_1;
	}
	else
		return LINEAR_0;
}

int quadratic_equation_solver(double a, double b, double c, double* x1, double* x2) {
	if (a == 0) return linear_equation_solver(&x1, &x2, b, c);

	if (c == 0) {
		*x1 = 0;
		if (b == 0) {
			*x2 = 0;
			return QUADRATIC_1;
		}

		assert(a != 0);

		*x2 = -b / a;
		return QUADRATIC_2;
	}

	double Disc = b * b - 4 * a * c;

	if (Disc > 0) {
		assert(a != 0);

		double sqrtD = sqrt(Disc);

		*x1 = (-b + sqrtD) / (2 * a);
		*x2 = (-b - sqrtD) / (2 * a);

		return(QUADRATIC_2);
	}
	if (Disc == 0) {
		assert(a != 0);

		double sqrtD = sqrt(Disc);

		*x1 = (-b + sqrtD) / (2 * a);

		return(QUADRATIC_1);
	}

	return QUADRATIC_0;
}

void print_roots(double* coeff) {
	double x1 = 0, x2 = 0;

	switch (quadratic_equation_solver(coeff[0], coeff[1], coeff[2], &x1, &x2)) {
	case INF:
		printf("Equation has an infinite number of solutions");
		break;
	case LINEAR_1:
		printf("Equation is linear. It has an only one solution.\n%g", x1);
		break;
	case LINEAR_0:
		printf("Equation is linear. It has no solutions.");
		break;
	case QUADRATIC_2:
		printf("Equation has two solutions\n%g and %g", x1, x2);
		break;
	case QUADRATIC_1:
		printf("Equation has two similar solutions\n%g", x1);
		break;
	case QUADRATIC_0:
		printf("Equation has no solutions");
		break;
	default:
		printf("Unknown error");
		break;
	}
}

int main() {
	double* coeff = new double[3];

	if (input(coeff) == 1)
		return 0;

	print_roots(coeff);

	delete[] coeff;
	return 0;
}
