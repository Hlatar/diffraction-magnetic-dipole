#include "math.h"
#include <stdio.h>

int N;
double eps;
double a;
double b;

double f(double x)
{
    return x * x;
}
double my_func(double x, double y) {
    return sin(x)*sin(y);
}


double trap_uniform(double (*f)(double),double a, double b, int N)
{
    double step = (b - a) / N;
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        double x0 = a + i * step;
        double x1 = a + (i + 1) * step;
        sum += 0.5 * (f(x0) + f(x1)) * step;
    }
    return sum;
}

double trap_adaptive(double (*f)(double), double a, double b,  //"а" нижняя граница, "b" нижняя граница 
                     int N, double eps, int max_iter)
{
    double I_old = trap_uniform(f, a, b, N);
    for (int it = 0; it < max_iter; it++) {
        N *= 2;
        double I_new = trap_uniform(f, a, b, N);
        if (std::fabs(I_new - I_old) < eps)
            return I_new;
        I_old = I_new;
    }
    return I_old; // не сошлось за max_iter
}



double trap_double_fast(double (*f)(double, double),
                        double a, double b, int Nx,
                        double c, double d, int Ny)
{
    double hx = (b - a) / Nx;
    double hy = (d - c) / Ny;
    double sum = 0.0;

    for (int i = 0; i <= Nx; i++) {
        double x = a + i * hx;
        double wx = (i == 0 || i == Nx) ? 0.5 : 1.0;

        for (int j = 0; j <= Ny; j++) {
            double y = c + j * hy;
            double wy = (j == 0 || j == Ny) ? 0.5 : 1.0;

            sum += wx * wy * f(x, y);
        }
    }
    return sum * hx * hy;
}



double trap_double_adaptive(double (*f)(double, double),
                            double a, double b,     // "а" нижняя граница, "b" нижняя граница 
                            double c, double d,     // "c" нижняя граница, "d" нижняя граница 
                            int Nx, int Ny,
                            double eps, int max_iter)
{
    double I_old = trap_double_fast(f, a, b, Nx, c, d, Ny);

    for (int it = 0; it < max_iter; it++) {
        Nx *= 2;
        Ny *= 2;
        double I_new = trap_double_fast(f, a, b, Nx, c, d, Ny);

        if (fabs(I_new - I_old) < eps)
            return I_new;

        I_old = I_new;
    }
    return I_old; // не сошлось за max_iter
}

int main()
{
    printf("%f ", trap_double_adaptive(my_func, 0, 3.14 ,0, 3.14, 10, 10 , 0.00001, 1000));
}
