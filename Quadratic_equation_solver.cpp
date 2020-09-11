#include <stdio.h>
#include <iostream>
#include <math.h>

enum roots {
	inf, linear_1, linear_0, quadratic_2, quadratic_1, quadratic_0
};

int input(double* coeff) {
	printf("Let's solve an quadratic equation like  ax^2 + bx + c = 0.\nPlease enter a, b and c.\n");

	for (int i = 0; i < 3; i++) {
		if (scanf_s("%lg", coeff + i) == 0) {
			printf("Wrong number\n");
			return 1;
		}
	}
	return 0;
}

int linear_equation_solver(double** x1, double** x2, double b, double c) {
	if ((b == 0) && (c == 0))
		return inf;
	if (b != 0) {
		**x1 = (-c / b);
		return linear_1;
	}
	else
		return linear_0;
}

int quadratic_equation_solver(double a, double b, double c, double* x1, double* x2) {
	if (a == 0)
		return linear_equation_solver(&x1, &x2, b, c);

	if (c == 0) {
		*x1 = 0;
		if (b == 0) {
			*x2 = 0;
			return quadratic_1;
		}
		*x2 = -b / a;
		return quadratic_2;
	}

	double Disc = b * b - 4 * a * c;

	if (Disc > 0) {
		*x1 = (-b + sqrt(Disc)) / (2 * a);
		*x2 = (-b - sqrt(Disc)) / (2 * a);

		return(quadratic_2);
	}
	if (Disc == 0) {
		*x1 = (-b + sqrt(Disc)) / (2 * a);

		return(quadratic_1);
	}

	return quadratic_0;
}

void print_roots(double* coeff) {
	double x1 = 0, x2 = 0;

	switch (quadratic_equation_solver(coeff[0], coeff[1], coeff[2], &x1, &x2)) {
	case inf:
		printf("Equation has an infinite number of solutions");
		break;
	case linear_1:
		printf("Equation is linear. It has an only one solution.\n%g", x1);
		break;
	case linear_0:
		printf("Equation is linear. It has no solutions.");
		break;
	case quadratic_2:
		printf("Equation has two solutions\n%g and %g", x1, x2);
		break;
	case quadratic_1:
		printf("Equation has two similar solutions\n%g", x1);
		break;
	case quadratic_0:
		printf("Equation has no solutions");
		break;
	default:
		printf("Unknown error");
		break;
	}
}

int main() {
	double* coeff = (double*)calloc(3, sizeof(double));

	if (input(coeff) == 1)
		return 0;

	print_roots(coeff);

	free(coeff);
	return 0;
}