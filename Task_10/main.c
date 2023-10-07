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

#define MAX_SIZE_OF_BUFFER 128

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
};

enum status_codes translation_10_to_x (int n, char* res, int x)
{
    int p = 0;
    if (n == 0)
    {
        res[0] = '0';
        res[1] = 0;
        return fsc_ok;
    }
        
    while (n > 0)
    {
        if (n % x >= 10)
            res[p] = (n % x) - 10 + 'A';
        else
            res[p] = (n % x) + '0';
        
        n /= x;
        if ((p + 1) < (MAX_SIZE_OF_BUFFER - 1))
            ++p;
        else
            return fsc_overflow;
    }
    res[p] = 0;
    for (size_t i = 0, j = strlen(res) - 1; i < j; i++, j--)
    {
        char c = res[i];
        res[i] = res[j];
        res[j] = c;
    }
    return fsc_ok;
}

enum status_codes translation_x_to_10 (char* n, int* res, int x)
{
    *res = 0;
    int tmp_n = 0;
    int pow_x = 1;
    *res = 0;
    for (int i = strlen(n) - 1; i >= 0; --i)
    {
        if (isalpha(n[i]))
        {
            if (isupper(n[i]))
                tmp_n = n[i] - 'A' + 10;
            else
                tmp_n = n[i] - 'a' + 10;
        }
        else
            tmp_n = n[i] - '0';
                
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
    
    char* value = malloc(sizeof(char) * MAX_SIZE_OF_BUFFER);
    char c;
    int i = 0;
    int max_value = 0;
    int value_10 = 0;
    bool sign = false;
    bool max_value_sign = false;
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
        
        if (strcmp(value, "Stop") == 0)
            break;
        
        if (value[0] == '-')
        {
            sign = true;
            value_ptr = value + 1;
        }
        else
            value_ptr = value;
        if (translation_x_to_10(value_ptr, &value_10, base) == fsc_ok)
        {
            if (value_10 > max_value)
            {
                max_value = value_10;
                max_value_sign = sign;
            }
        }
        else
            function_result = fsc_overflow;
        
        if (sign)
            value_ptr = value;
        
        function_result = fsc_ok;
    }
    
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
    
    free(value);
    
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
    
    return 0;
}