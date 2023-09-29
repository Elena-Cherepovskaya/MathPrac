//
//  main.c
//  5
//
//  Created by Лена on 28.09.2023.
//

// X EPS

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define EPS 0.0001

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
};

enum status_codes fact(int n, double * res)
{
    if (n < 0)
        return fsc_invalid_parameter;

    *res = 1;
    for (int i = 1; i <= n; ++i)
        *res *= i;

    return fsc_ok;
}

enum status_codes double_factorial(int n, double * res)
{
    if (n < 0)
        return fsc_invalid_parameter;
        
    *res = 1;
    for (int i = n % 2 == 0 ? 2 : 1; i <= n; i += 2)
        (*res) *= i;

    return fsc_ok;
}

enum status_codes function_a(int n, double x, double* next_syllable)
{
    double fact_res;
    
    enum status_codes function_result = fact(n, &fact_res);
    
    if (function_result == fsc_ok)
        *next_syllable = pow(x, n) / fact_res;

    return function_result;
}

enum status_codes function_b(int n, double x, double* next_syllable)
{
    double fact_res;
    enum status_codes function_result = fact(2 * n, &fact_res);

    if (function_result == fsc_ok)
        *next_syllable = pow(-1.0, n) * pow(x, 2.0 * n) / fact_res;
    
    return function_result;
}

enum status_codes function_c(int n, double x, double* next_syllable)
{
    double fact_res_1;
    double fact_res_2;
    enum status_codes function_result;
 
    function_result = fact(3 * n, &fact_res_1);
    if (function_result != fsc_ok)
        return function_result;
    
    function_result = fact(n, &fact_res_2);
    if (function_result != fsc_ok)
        return function_result;
    
    *next_syllable = pow(3.0, 3.0 * n) * pow(fact_res_2, 3.0) * pow(x, 2.0 * n) / fact_res_1;

    return function_result;
}

enum status_codes function_d(int n, double x, double* next_syllable)
{
    double fact_res_1;
    double fact_res_2;
    
    enum status_codes function_result = double_factorial(2 * n, &fact_res_1);
    if (function_result != fsc_ok)
        return function_result;
    
    function_result = double_factorial(2 * n - 1, &fact_res_2);
    if (function_result != fsc_ok)
        return function_result;
    
    *next_syllable = pow(-1.0, n) * fact_res_1 * pow(x, 2 * n) / fact_res_2;
    
    return function_result;
}

int main(int argc, const char * argv[])
{
    enum status_codes function_result = argc < 2 ? fsc_invalid_parameter : fsc_ok;
    
    char* end_str;
    double eps = EPS;
    double x = 0;
    if (function_result == fsc_ok)
    {
        x = strtod(argv[1], &end_str);
        
        if (argc == 3)
            eps = strtod(argv[2], &end_str);
    }

    double next_syllable = 0.0;
    if (function_result == fsc_ok)
    {
        for (int i = 0; i < 4; ++i)
        {
            double sum = 0.0;
            for (int n = (i != 3 ? 0 : 1); true; ++n)
            {
                switch (i)
                {
                    case 0:
                        function_result = function_a(n, x, &next_syllable);
                        break;
                        
                    case 1:
                        function_result = function_b(n, x, &next_syllable);
                        break;
                        
                    case 2:
                        function_result = function_c(n, x, &next_syllable);
                        break;

                    case 3:
                        function_result = function_d(n, x, &next_syllable);
                        break;
                }
                
                if (function_result != fsc_ok)
                {
                    printf("%d: Overflow detected\n", i);
                    break;
                }
                else
                {
                    if (fabs(next_syllable) > eps)
                        sum += next_syllable ;
                    else
                    {
                        printf("%c: %lf\n",'a' + i, sum);
                        break;
                    }
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
