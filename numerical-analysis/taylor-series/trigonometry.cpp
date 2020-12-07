#include <cmath>
#include <iostream>

using namespace std;

// assume f(x) = sin(x)
// then:
// f'(x) = cos(x)
// f''(x) = -sin(x)
// f'''(x) = -cos(x)
// f''''(x) = sin(x)
// f'''''(x) = cos(x)
// f'''''''(x) = -sin(x)
// f''''''''(x) = -cos(x)
// if c = pi/4, then sin(c) = cos(c) = 0.707106781186 (value of sqrt(2)/2)
// this function calculates sin(x) between [0, pi/2]
// though there's a better approximation method (by using Maclaurin series, which is c = 0), at least this function proves that the Taylor series is correctly approximating for all c
// this function exposes round-off errors (notice when we use c = 0, the sine and cosine of c would be the EXACT value a.k.a. 0 or 1)
double __sine_0_1(double x) {
    double c = 0.785398163397;
    double sin_c = 0.707106781186;
    double cos_c = 0.707106781186;
    double h = x - c;

    return sin_c
        + pow(h, 1) / 1 * cos_c
        + pow(h, 2) / 2 * -sin_c
        + pow(h, 3) / 6 * -cos_c
        + pow(h, 4) / 24 * sin_c;
        + pow(h, 5) / 120 * cos_c
        + pow(h, 6) / 720 * -sin_c
        + pow(h, 7) / 5040 * -cos_c;
}

double __radians(double x) {
    return x * 0.017453292520;
}

double __degrees(double x) {
    return x * 57.295779513082;
}

double sine(double x) {
    int deg = (int)((long long)__degrees(x) % 360);
    int s = deg / 90;
    if (s == 1) {
        return __sine_0_1(__radians(180 - deg));
    }
    if (s == 2) {
        return -__sine_0_1(__radians(deg - 180));
    }
    if (s == 3) {
        return -__sine_0_1(__radians(360 - deg));
    }
    return __sine_0_1(__radians(deg));
}

double cosine(double x) {
    return sine(__radians(__degrees(x) + 90));
}

double tangent(double x) {
    return sine(x) / cosine(x);
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(12);
    while (true) {
        double x;
        cout << "Enter x: ";
        cin >> x;

        cout << endl;

        cout << " [approx] sin(x) = " << sine(x) << endl;
        cout << " [cmath] sin(x) = " << sin(x) << endl;
        cout << endl;

        cout << " [approx] cos(x) = " << cosine(x) << endl;
        cout << " [cmath] cos(x) = " << cos(x) << endl;
        cout << endl;

        cout << " [approx] tan(x) = " << tangent(x) << endl;
        cout << " [cmath] tan(x) = " << tan(x) << endl;
        cout << endl;
    }

    return 0;
}

