/* CS100 Fall 2026 - HW2 Problem 3: Polynomial evaluation
 *
 * Evaluate P(x) at m given points; print each value rounded to 3 decimals.
 * An array is enough for the coefficients; do not use heap memory and do
 * not use <math.h> (your program is not linked against the math library).
 * Do not rename this file.
 */
#include <stdio.h>

#define MAX_DEGREE 30

int main(void)
{
    int n, m;
    double a[MAX_DEGREE + 1];

    if (scanf("%d", &n) != 1)
        return 0;
    for (int i = 0; i <= n; ++i)
        if (scanf("%lf", &a[i]) != 1)
            return 0;

    if (scanf("%d", &m) != 1)
        return 0;
    for (int k = 0; k < m; ++k) {
        double x;
        if (scanf("%lf", &x) != 1)
            return 0;
        /* Horner's rule: P(x) = (...((a_n x + a_{n-1}) x + a_{n-2}) ...) x + a_0 */
        double result = 0.0;
        for (int i = n; i >= 0; --i)
            result = result * x + a[i];
        printf("%.3f\n", result);
    }
    return 0;
}
