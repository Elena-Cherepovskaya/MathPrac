//
//  main.c
//  6
//
//  Created by Лена on 09.10.2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE_OF_BUFFER 16384

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
};

double f_0(double x)
{
    return log(1 + x)/x;
}

double f_1(double x)
{
    return exp(-((x * x) / 2.0));
}

double f_2(double x)
{
    return log(1.0 / (1.0 - x));
}

double f_3(double x)
{
    return pow(x, x);
}

int main(int argc, const char * argv[])
{
    enum status_codes function_result = argc < 2 ? fsc_invalid_parameter : fsc_ok;

    if (function_result == fsc_ok)
    {
        char* end_str;
        double eps = strtod(argv[1], &end_str);
        
        double (*functions[4]) (double) = {f_0, f_1, f_2, f_3};
        for(int nm = 0; nm < 4; ++nm)
        {
            double dx = 0.01;
            double prev_y = 0.0;
            while(true)
            {
                double y = 0.0;
                for(double x = dx; x < 1.0 - dx; x += dx)
                {
                    double x1 = x - dx / 2.0;
                    double x2 = x + dx / 2.0;

                    double y1 = functions[nm](x1);
                    double y2 = functions[nm](x2);
                    
                    double s = y1 + (y2 - y1) / 2.0;
                    y += s * dx;
                }
                if (fabs(y - prev_y) < eps)
                {
                    printf("integral %c: %0.10lf\n", nm + 'a', y);
                    break;
                }
                else
                {
                    prev_y = y;
                    dx /= 10.0;
                }
            }
        }
    }
    
    switch (function_result)
    {
        case fsc_ok:
            break;
        case fsc_overflow:
            printf("Overflow detected\n");
            break;
        case fsc_invalid_parameter:
            printf("Invalid parameter detected\n");
            break;
        default:
            printf("function_result is unknown\n");
    }
    
    return function_result == fsc_ok ? 0 : 1;
}
