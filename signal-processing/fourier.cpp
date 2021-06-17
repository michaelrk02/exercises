#include <cmath>
#include <iostream>

typedef double (* func_t)(double x);

double fourier(func_t f, double t0, double t1, int n, double s) {
    double result = 0.0;
    double dt = (t1 - t0) / (double)n;
    for (int i = 0; i < n; i++) {
        double t = t0 + (double)i * dt;
        result = result + f(t) * std::cos(2.0 * M_PI * t * s) * dt;
    }
    return result;
}

void plot_fourier(func_t f, double t0, double t1, int samples, double s0, double s1, int frequencies) {
    double ds = (s1 - s0) / (double)frequencies;
    for (int i = 0; i < frequencies; i++) {
        double s = s0 + (double)i * ds;
        std::cout << "F{f}(" << s << " Hz) = " << fourier(f, t0, t1, samples, s) << std::endl;
    }
}

double our_signal(double t) {
    double frequencies[] = {1.0, 3.0, 5.0, 7.0};
    int n = sizeof(frequencies)/sizeof(double);

    double value = 0.0;
    for (int i = 0; i < n; i++) {
        value = value + std::cos(2.0 * M_PI * frequencies[i] * t);
    }
    return value;
}

int main() {
    plot_fourier(our_signal, 0.0f, 10.0f, 1000, 0.0f, 10.0f, 10);
    return 0;
}

