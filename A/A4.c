#include <stdio.h>
#include <math.h>

double func(double k);
int main() {
    double k;
    double accuracy, sum = 0.0;
    scanf("%lf", &accuracy);
    for (k = 0; ;k++)
    {
        double tempVal;
        tempVal = func(k + 0.0);
        if (tempVal < accuracy)
        {
            break;
        }
        sum += tempVal;
    }
    printf("%.15lf", sum);
    return 0;
}

double func(double k)
{
    double val;
    val = (1 / pow(16.0, k)) * (4 / (8 * k + 1) - 2 / (8 * k + 4) - 1 / (8 * k + 5) - 1 / (8 * k + 6));
    return val;
}

//Question: why long double is WA?