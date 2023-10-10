//
//  main.c
//  10
//
//  Created by Лена on 04.10.2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE_OF_BUFFER 128

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
    fsc_memory_error_detected,
};

int char_to_num(char c)
{
    if (isalpha(c))
    {
        if (isupper(c))
            return (int)(c - 'A' + 10);
        return (int)(c - 'a' + 10);
    }
    return (int)(c - '0');
}

double log_a_b(double a, double b)
{
    return (log(b) / log(a));
}

enum status_codes translation_10_to_x (int n, char* res, int x)
{
    if (x == 0)
        return fsc_invalid_parameter;
    
    if (x < 2 || x > 36)
        return fsc_invalid_parameter;
    
    if (n == 0)
    {
        res[0] = '0';
        res[1] = 0;
        return fsc_ok;
    }
    
    int len_of_n = floor(log_a_b(x, n)) + 1;
    res[len_of_n] = 0;
    
    if (len_of_n > MAX_SIZE_OF_BUFFER )
        return fsc_overflow;
    
    while (n > 0)
    {
        len_of_n--;
        int rm = n % x;
        if (rm >= 10)
            res[len_of_n] = rm - 10 + 'A';
        else
            res[len_of_n] = rm + '0';
        
        n /= x;
        
    }
    
    return fsc_ok;
}

enum status_codes translation_x_to_10 (char* n, int* res, int x)
{
    *res = 0;
    int tmp_n = 0;
    int pow_x = 1;
    for (int i = strlen(n) - 1; i >= 0; --i)
    {
        tmp_n = char_to_num(n[i]);
        
        if (tmp_n >= x)
            return fsc_invalid_parameter;
                
        *res = *res + tmp_n * pow_x;
        pow_x *= x;
    }
    return fsc_ok;
}

int main(int argc, const char * argv[])
{
    enum status_codes function_result = fsc_unknown;
    
    int base;
    printf("Введите основание системы счисления в диапазоне [2..36]: ");
    scanf("%d", &base);
    getchar();//Чтобы ''
    
    char* value;
    if (base < 2)
        function_result = fsc_invalid_parameter;
    else
    {
        value = (char*)malloc(sizeof(char) * MAX_SIZE_OF_BUFFER);
        function_result = (value == NULL) ? fsc_memory_error_detected : fsc_ok;
    }
    
    if (function_result == fsc_ok)
    {
        
        char c;
        int i = 0;
        int max_value = 0;
        int value_10 = 0;
        bool sign = false;
        bool max_value_sign = false;
        bool value_is_empty = true;
        printf("Введите числа:\n");
        char* value_ptr;
        while (function_result != fsc_overflow)
        {
            sign = false;
            i = 0;
            
            while((c = getchar()) != '\n')
            {
                if (i + 1 < MAX_SIZE_OF_BUFFER)
                {
                    value[i] = c;
                    ++i;
                }
                else
                    function_result = fsc_overflow;
            }
            
            value[i] = 0;
            
            if (strcmp(value, "-0") == 0)
            {
                function_result = fsc_invalid_parameter;
                break;
            }
            
            if (strcmp(value, "Stop") == 0)
                break;
            
            if (value[0] == '-')
            {
                sign = true;
                value_ptr = value + 1;
            }
            else
                value_ptr = value;
            
            function_result = translation_x_to_10(value_ptr, &value_10, base);
            if (function_result == fsc_ok)
            {
                value_is_empty = false;
                if (value_10 > max_value)
                {
                    max_value = value_10;
                    max_value_sign = sign;
                }
            }
            else
                break;
            
            if (sign)
                value_ptr = value;
            
            function_result = fsc_ok;
        }
        
        if (function_result == fsc_ok && !value_is_empty)
        {
            printf("Выходные данные: \n");
            printf("Max value: %s%d\n", (max_value_sign ? "-" : ""), max_value);
            
            int list_of_bases[4] = {9, 18, 27, 36};
            for (int i =0; i < 4; ++i)
            {
                if ((translation_10_to_x(max_value, value, list_of_bases[i]) == fsc_ok) && (function_result == fsc_ok))
                    printf("base %d: %c%s\n",list_of_bases[i], (max_value_sign ? '-' : ' '), value);
                else
                    function_result = fsc_overflow;
            }
        }
        free(value);
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
        case fsc_memory_error_detected:
            printf("Memory error detected\n");
            break;
        default:
            printf("function_result is unknown\n");
    }
    
    return 0;
}
