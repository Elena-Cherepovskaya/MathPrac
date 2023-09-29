//
//  main.c
//  3
//
// Created by Лена on 22.09.2023.
// М8О-213Б-22
// Череповская Елена

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define MAX_VALUES 10
#define MAX_SIZE_OF_BUFFER 32

float const EPS = 0.0001;

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
    fsc_valid_roots_is_not_detected,
};

enum status_codes solve_the_equation(double a, double b, double c, double* x_1, double* x_2)
{
    double D = b*b - 4.0*a*c;
    if (D >= 0)
    {
        *x_1 = ((-1.0) * b + sqrt(D)) / (2.0 * a);
        *x_1 = ((-1.0) * b - sqrt(D)) / (2.0 * a);
        return fsc_ok;
    }
    else
        return fsc_valid_roots_is_not_detected;
}

void sides_of_the_triangle(double a, double b, double c, double* cathet_1, double* cathet_2, double* hypotenuse)
{
    if (a >= b && a >= c)
    {
        *hypotenuse = a;
        *cathet_1 = b;
        *cathet_2 = c;
    }
        else
            if (b >= a && b >= c)
            {
                *hypotenuse = b;
                *cathet_1 = a;
                *cathet_2 = c;
            }
            else
                {
                    *hypotenuse = c;
                    *cathet_1 = a;
                    *cathet_2 = b;
                }
    return;
}

int main(int argc, const char * argv[])
{
    enum status_codes function_result = fsc_unknown;
    
    int i_int = 0;
    int i_double = 0;
    
    bool flag_ready = false;
    char const* flags_list = "qmt";
    char flag = 0;
    
    int int_values_list[MAX_VALUES];
    double double_values_list[MAX_VALUES];
    
    double double_value = 0.0;
    int int_value = 0;
    char* end_str;
    for (int i = 1; i < argc; ++i)
    {
        if ((argv[i][0] == '/' || argv[i][0] == '-') && argv[i][1] >= 'a' && argv[i][1] <= 'z')
        {
            flag = argv[i][1];
            for (char const* p_flags = flags_list; *p_flags != 0; ++p_flags)
                if (flag == *p_flags)
                {
                    if (flag_ready)
                        function_result = fsc_invalid_parameter;//найдено два флага
                    
                    flag_ready = true;
                    break;
                }
        }
        
        else
        {
            int_value = atoi(argv[i]);
            double_value = strtod(argv[i], &end_str);
            
            if (fabs(double_value - int_value) < EPS)
            {
                if (i_int < MAX_VALUES)
                {
                    int_values_list[i_int] = int_value;
                    ++i_int;
                }
                else
                {
                    function_result = fsc_overflow;
                    break;
                }
            }
            
            if (i_double < MAX_VALUES)
            {
                double_values_list[i_double] = double_value;
                ++i_double;
            }
            else
            {
                function_result = fsc_overflow;
                break;
            }
        }
        
    }
    
    /*printf("%c\n", flag);
    for (int i = 0; i < i_int; ++i)
        printf("%d ",int_values_list[i]);
    printf("\n");
    for (int i = 0; i < i_double; ++i)
        printf("%lf ",double_values_list[i]);
    printf("\n");*/

    double x_1;
    double x_2;
    switch (flag)
    {
        case 'q':
            if (i_double == 4)
            {
                double epsilon = double_values_list[0];
                double params[6][3] = {
                    double_values_list[1], double_values_list[2], double_values_list[3],
                    double_values_list[2], double_values_list[1], double_values_list[3],
                    double_values_list[3], double_values_list[1], double_values_list[2],
                    double_values_list[1], double_values_list[3], double_values_list[2],
                    double_values_list[2], double_values_list[3], double_values_list[1],
                    double_values_list[3], double_values_list[2], double_values_list[1],
                };
                for(int i = 0; i < 6; ++i)
                {
                    bool skip_variant = false;
                    // Проверка может этот вариант стоит пропустить
                    for(int t = 0; t < i; ++t)
                    {
                        if ((fabs(params[t][0] - params[i][0]) <= epsilon) &&
                            (fabs(params[t][1] - params[i][1]) <= epsilon) &&
                            (fabs(params[t][2] - params[i][2]) <= epsilon))
                        {
                            skip_variant = true;
                        }
                    }
    
                    printf("a = %lf b = %lf c = %lf => ", params[i][0], params[i][1], params[i][2]);
                    if (!skip_variant)
                    {
                        if (solve_the_equation(params[i][0], params[i][1], params[i][2], &x_1, &x_2) == fsc_ok)
                        {
                            printf("x_1 = %lf, x_2 = %lf\n", x_1, x_2);
                            function_result = fsc_ok;
                        }
                        else
                            printf("Для этого уравнения действиельных корней нет\n");
                    }
                    else
                        printf("Уже решали\n");
                }
            }
            function_result = fsc_ok;
            break;
        case 'm':
        {
            bool res = (i_int == 2 && (abs(int_values_list[0]) % abs(int_values_list[0]) == 0));
            printf("%d %sкратно %d\n", int_values_list[0], (res ? "" : "не "),int_values_list[1]);
            function_result = fsc_ok;
            break;
        }
        case 't':
        {
            if (i_double == 4)
            {
                if (double_values_list[0] <= 0 || double_values_list[1] <= 0 || double_values_list[2] <= 0 || double_values_list[3] <= 0)
                    function_result = fsc_invalid_parameter;
                else
                {
                    double cathet_1;
                    double cathet_2;
                    double hypotenuse;
                    double eps = double_values_list[0];
                    sides_of_the_triangle(double_values_list[1], double_values_list[2], double_values_list[3], &cathet_1, &cathet_2, &hypotenuse);
                    
                    bool res = fabs(hypotenuse * hypotenuse - (cathet_1 * cathet_1 + cathet_2 * cathet_2)) <= (eps * eps);
                    printf("Данная тройка чисел %sможет является сторонами треугольника\n", (res ? "" : "не "));
                    function_result = fsc_ok;
                }
            }
            else
                function_result = fsc_invalid_parameter;
            break;
        }
        default:
            function_result = fsc_invalid_parameter;
            break;
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

