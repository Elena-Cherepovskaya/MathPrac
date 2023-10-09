//
//  main.c
//  2
//
//  Created by Лена on 05.10.2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE_OF_BUFFER 16000

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
};

bool num_is_prime(int n)
{
    if (n == 1)
        return false;
    
    if (n % 2 == 0)
        return false;
    {
        int max_del = (int)sqrt(n + 1);
        for (int i = 3; i <= max_del; i += 2)
        {
            if (n % i == 0)
                return false;
        }
    }
    return true;
}

double fact(int n)
{
    double res = 1.0;

    for (int i = 1; i <= n; ++i)
        res *= i;
    
    return res;
}

double pow_2 (double n)
{
    return n * n;
}

double pow_4 (double n)
{
    return  n * n * n * n;
}

double amount_a(int n)
{
    return 1.0 / fact(n);
}

double amount_b(int n)
{
    return pow(-1.0, n - 1) / (2.0 * n - 1.0);
}

double amount_c(int n)
{
    return pow(-1.0, n - 1) / n;
}

double amount_d(int n)
{
    return pow(2.0, pow(2.0, -n));
}

double amount_e(int n)
{
    return 1.0 / pow_2(floor(sqrt(n))) - 1.0 / n;
}

double lim_a(int n)
{
    return pow((1.0 + 1.0 / n), n);
}

double lim_b(int n)
{
    return pow_4(pow(2.0, n) * fact(n)) / (n * pow_2(fact(2 * n)));
}

double lim_c(int n)
{
    return n * (pow(2.0, 1.0 / n) - 1.0);
}

double lim_d (double x_prev)
{
    return x_prev - pow_2(x_prev) /  2.0 + 1.0 ;
}

double lim_e (int m)
{
    double res = 0.0;
    for (int k = 1; k <= m; ++k)
    {
        res +=(fact(m) / (fact(k) * fact(m  -k))) * (pow(-1.0, k) / k) * log(fact(k));
    }
    return res;
}

double solution_of_equation (double a, double b)
{
    return (a + b) / 2.0;
}

enum status_codes push_list_of_prime_values(int* list_of_prime_values, int* col_of_prime_values, int t)
{
    while (true)
    {
        if (t > list_of_prime_values[*col_of_prime_values - 1])
        {
            for (int i = list_of_prime_values[*col_of_prime_values - 1] + 1; true; ++i)
            {
                if (num_is_prime(i))
                {
                    if (*col_of_prime_values + 1 > MAX_SIZE_OF_BUFFER)
                        return fsc_overflow;
                    else
                    {
                        list_of_prime_values[*col_of_prime_values] = i;
                        ++*col_of_prime_values;
                    }
                    break;
                }
            }
        }
        else
            return fsc_ok;
    }
}

double equation_e(int t, int* list_of_prime_values, int* col_of_prime_values)
{
    double res = 1.0;
    push_list_of_prime_values(list_of_prime_values, col_of_prime_values, t);
    for (int i = 0; list_of_prime_values[i] < t; ++i)
        res *= ((list_of_prime_values[i] - 1.0) / list_of_prime_values[i]);

    return log(t) * res;
}

int main(int argc, const char * argv[])
{
    
    enum status_codes function_result = argc < 2 ? fsc_invalid_parameter : fsc_ok;
    
    if (function_result == fsc_ok)
    {
        char* end_str;
        double eps = strtod(argv[1], &end_str);
        
        for(int n_func = 0; n_func < 5; ++n_func)
        {
            int n_begin[] = {0, 1, 1, 2, 2};
            double sum_begin[] = {0, 0, 0, 1, 0};
            
            double next_syllable = 0.0;
            double sum = sum_begin[n_func];
            
            for (int n = n_begin[n_func]; true; ++n)
            {
                switch (n_func)
                {
                    case 0:
                        next_syllable = amount_a(n);
                        sum += next_syllable;
                        break;
                    case 1:
                        next_syllable = amount_b(n);
                        sum += next_syllable;
                        break;
                    case 2:
                        next_syllable = amount_c(n);
                        sum += next_syllable;
                        break;
                    case 3:
                        next_syllable = amount_d(n);
                        sum *= next_syllable;
                        next_syllable -= 1.0;
                        break;
                    case 4:
                        next_syllable = amount_e(n);
                        sum += next_syllable;
                        break;
                }
                
                if (fabs(next_syllable) < eps && next_syllable > 0)
                {
                    switch (n_func)
                    {
                        case 1:
                            sum = 4.0 * sum;
                            break;
                        case 4:
                            sum = -pow_2(M_PI) / 6 + sum;
                            break;
                        default:
                            break;
                    }
                    printf("Amount_%c: %lf\n", n_func + 'a',sum);
                    break;
                }
            }
        }
        
        for(int n_func = 0; n_func < 5; ++n_func)
        {
            double lim_prev = 0.0;
            
            double lim;
            double prev_lim_d = -0.5;
            for (int n = 1; true; ++n)
            {
                switch (n_func)
                {
                    case 0:
                        lim = lim_a(n);
                        break;
                    case 1:
                        lim = lim_b(n);
                        break;
                    case 2:
                        lim = lim_c(n);
                        break;
                    case 3:
                    {
                        lim = lim_d(prev_lim_d);
                        prev_lim_d = lim;
                        break;
                    }
                    case 4:
                    {
                        lim = lim_e(n + 1);
                        break;
                    }
                }
                if (isnan(lim))
                    lim = lim_prev;

                if (fabs(lim - lim_prev) <= eps)
                {
                    printf("lim f_%c: %lf\n", n_func + 'a', lim);
                    break;
                }
                else
                    lim_prev = lim;
            }
        }
        
        int list_of_prime_values[MAX_SIZE_OF_BUFFER] = {0};
        list_of_prime_values[0] = 2;
        int col_of_prime_values = 1;
        
        double lim;
        double lim_prev = 1.0;
        int col_prime_lim = col_of_prime_values;
        int col_prime_lim_prev = col_of_prime_values;
        
        for (int t = 3; true; ++t)
        {
            lim = equation_e(t, list_of_prime_values, &col_of_prime_values);
            col_prime_lim = col_of_prime_values;
            
            if (col_prime_lim == col_prime_lim_prev)
                continue;
            
            if (fabs(lim - lim_prev) <= eps)
                break;
            
            col_prime_lim_prev = col_prime_lim ;
            lim_prev = lim;
        }

        for(int n_func = 0; n_func < 5; ++n_func)
        {
            double f_a, f_b, f_c;

            double begin[] = {1, 1, 0, 1, 0};
            double end[] = {3, 4, 1, 2, 1};
            
            double delta = eps / 100.0;
            double a = begin[n_func];
            double b = end[n_func];
            
            while (true)
            {
                double c = (a+b) / 2.0;
                double x1 = (a+b-delta)/2.0;
                double x2 = (a+b+delta)/2.0;
                switch (n_func)
                {
                    case 0:
                    {
                        f_a = log(x1) - 1.0;
                        f_b = log(x2) - 1.0;
                        f_c = log(c) - 1.0;
                        break;
                    }
                    case 1:
                    {
                        f_a = cos(x1) + 1.0;
                        f_b = cos(x2) + 1.0;
                        f_c = cos(c) + 1.0;
                        break;
                    }
                    case 2:
                    {
                        f_a = exp(x1) - 2.0;
                        f_b = exp(x2) - 2.0;
                        f_c = exp(c) - 2.0;
                        break;
                    }
                    case 3:
                    {
                        f_a = pow_2(x1) - 2.0;
                        f_b = pow_2(x2) - 2.0;
                        f_c = pow_2(c) - 2.0;
                        break;
                    }
                    case 4:
                    {
                        f_a = 1.0 / exp(x1) - lim;
                        f_b = 1.0 / exp(x2) - lim;
                        f_c = 1.0 / exp(c) - lim;
                        break;
                    }
                }
                
                if ((fabs(f_c) < eps) || ((b - a) < delta))
                {
                    printf("equation f_%c: %lf\n", n_func + 'a', c);
                    break;
                }
                else
                {
                    if (fabs(f_a) > fabs(f_b))
                        a = c + delta;
                    else
                        b = c - delta;
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
