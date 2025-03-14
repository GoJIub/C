#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// 2 * x * sinx - cosx = 0 [0.4, 1] 0.6533
// e^x + sqrt(1 + e^(2 * x)) - 2 = 0 [-1, 0] -0.2877

typedef struct {
    double root;
    int iters;
    bool success;
} answer;

typedef double(*func)(double);

double df(func f, double x) {

    double dx = 1e-6;
    return (f(x + dx) - f(x)) / dx;

}

double ddf(func f, double x) {

    double dx = 1e-4;
    return (f(x + dx) - 2 * f(x) + f(x - dx)) / (dx * dx);
    
}

double f10(double x) {
    return 2 * x * sin(x) - cos(x);
}

double g10(double x) {
    return x - 0.3 * f10(x);
}

double f11(double x) {
    return exp(x) + sqrt(1 + exp(2 * x)) - 2;
}

double g11(double x) {
    return log(2 - sqrt(1 + exp(2 * x)));
}

answer diho(func f, double a, double b) {

    answer res = {.root = 0, .iters = 0, .success = false};

    if (f(a) * f(b) > 0)
        return res;

    int iters = 0;
    double apr = 1e-6;

    while (a + apr <= b) {
        
        double c = (a + b) / 2;

        if (f(c) * f(a) <= 0)
            b = c;
        else
            a = c;

        iters++;
    }

    res.root = (a + b) / 2;
    res.iters = iters;
    res.success = true;
    return res;

}

answer iterations(func g, double x) {
    
    answer res = {.root = 0, .iters = 0, .success = false};

    int iters = 0;
    int max_iters = 1000;
    double apr = 1e-5;
    double new_x = g(x);

    while (fabs(new_x - x) >= apr) {

        if (abs(df(g, x)) >= 1) {
            res.success = false;
            return res;
        }

        x = new_x;
        new_x = g(x);
        iters++;

        if (iters > max_iters) {
            res.iters = iters;
            return res;
        }

    }

    res.root = new_x;
    res.iters = iters;
    res.success = true;
    return res;

}

answer newton(func g, double x) {
    
    answer res = {.root = 0, .iters = 0, .success = false};

    int iters = 0;
    int max_iters = 1000;
    double apr = 1e-6;
    double new_x = x - g(x) / df(g, x);

    while (fabs(new_x - x) >= apr) {

        x = new_x;

        if (fabs(df(g, x) < apr * apr))
            return res;

        if (fabs(g(x) * ddf(g, x)) >= (df(g, x) * df(g, x))) {
            res.success = false;
            return res;
        }

        new_x = x - g(x) / df(g, x);
        iters++;

        if (iters > max_iters) {
            res.success = false;
            return res;
        }

    }

    res.root = new_x;
    res.iters = iters;
    res.success = true;
    return res;

}

int main() {

    printf("\nFirst equation:\n");

    answer res_diho = diho(f10, 0.4, 1.0);
    printf("Bisection method: x = %.4f, iterations: %d\n", res_diho.root, res_diho.iters);


    answer res_iters = iterations(g10, 1.0);
    printf("Iteration method: x = %.4f, iterations: %d\n", res_iters.root, res_iters.iters);

    answer res_newton = newton(f10, 0.5);
    printf("Newton's method: x = %.4f, iterations: %d\n", res_newton.root, res_newton.iters);


    printf("\nSecond equation:\n");

    res_diho = diho(f11, -1.0, 0.0);
    printf("Bisection method: x = %.4f, iterations: %d\n", res_diho.root, res_diho.iters);


    res_iters = iterations(g11, -0.2);
    printf("Iteration method: x = %.4f, iterations: %d\n", res_iters.root, res_iters.iters);


    res_newton = newton(f11, -0.2);
    printf("Newton's method: x = %.4f, iterations: %d\n", res_newton.root, res_newton.iters);

}