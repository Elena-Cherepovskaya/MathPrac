//
//  main.c
//  1
//  М8О-213Б-22
//  Череповская Елена
//

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
};

//Для возведения в степень также можно было пользоваться фонкцией pow
long power(int n, int p)
{
    long res = 1;
    for (int i = 1; i <= p; ++i)
        res *= n;
    
    return res;
}

//Для перевода строки в число можно было такде пользоваться функцией atoi
enum status_codes str_to_num(const char* str, int* res)
{
    char const* p_flags = str;
    if (*p_flags == '-')
        ++p_flags;
    
    *res = 0;
    for (;*p_flags != 0; ++p_flags)
    {
        if (*p_flags >= '0' && *p_flags <= '9')
            *res = *res * 10 + *p_flags - '0';
        else
            return fsc_invalid_parameter;
    }
    
    if (str[0] == '-')
        *res *= (-1);
    
    return fsc_ok;
}

bool is_num_prime(int n)
{
    if (n < 0)
        return false;

    for (int i = 2; i < (int)sqrt(n) + 1; ++i)
        if (n % i == 0)
            return false;
    return true;
}

int len_of_value(int value)
{
    if (value == 0)
        return 1;
    
    value = abs(value);
    int col = 0;
    while (value > 0)
    {
        value /= 10;
        ++col;
    }
    return col;
}

enum status_codes int_to_str(int value, char* buffer, int buffer_size)
{
    int len = len_of_value(value);
    if (len >= buffer_size - 1)
        return fsc_overflow;
    
    value = abs(value);
    int i = 0;
    long del = power(10, len_of_value(value) - 1);
    while (len > i)
    {
        buffer[i] = value / del + '0';
        value %= del;
        del = (int)(del / 10);
        ++i;
    }
    buffer[i] = 0;
    return fsc_ok;
}

enum status_codes sum (int n, int* res)
{
    if (n < 0)
        return fsc_invalid_parameter;
    
    *res = (int)((1 + n) / 2) * n;
    
    if (*res < 0)
        return fsc_overflow;
    
    return fsc_ok;
}

enum status_codes fact(int n, int* res)
{
    if (n < 0)
        return fsc_invalid_parameter;
    *res = 1;
    for (int i = 1; i <= n; ++i)
    {
        *res *= i;
        if (*res < 0)
            return fsc_overflow;
    }
    return fsc_ok;
}

int main(int argc, const char * argv[])
{
    enum status_codes function_result = fsc_unknown;
    
    bool flag_ready = false;
    bool value_ready = false;
    char const* flags_list = "hpseaf";
    char flag;
    int value;
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
        
        int read_value;
        if (str_to_num(argv[i], &read_value) == fsc_ok)
        {
            value = read_value;
            if (value_ready)
                function_result = fsc_invalid_parameter;//найдено два числа
            
            value_ready = true;
        }
        
    }
    function_result = (flag_ready && value_ready) ? fsc_ok : fsc_invalid_parameter;
    
    //printf("%c %d\n", flag, value);
    if (function_result == fsc_ok)
    {
        switch(flag)
        {
            case 'h':
            {
                value = abs(value);
                if (value == 0)
                    function_result = fsc_invalid_parameter;
                else
                {
                    for (int i = value; i <= 100; i+=value)
                        printf("%d ",i);
                    
                    if (value > 100 || value < 1)
                        printf("No multiples found");
                    
                    printf("\n");
                    function_result = fsc_ok;
                }
                break;
            }
            case 'p':
            {
                if (is_num_prime(value))
                    printf("value is simple\n");
                else
                    printf("value is composit\n");
                
                function_result = fsc_ok;
                break;
            }
            case 's':
            {
                char buffer[256];
                if (int_to_str(value, buffer, sizeof(buffer)) == fsc_ok)
                {
                    for (char* p_flags = buffer; *p_flags != 0; ++p_flags)
                        printf("%c ",*p_flags);
                }
                
                printf("\n");
                break;
            }
            case 'e':
            {
                if (value > 10 || value < 0)
                    function_result = fsc_invalid_parameter;

                else
                {
                    for (int i = 1; i <= value; ++i)//Подписи столбцов
                        printf("%11d ", i);
                    printf("\n\n");
                
                    for (int i = 1; i <= 10; ++i)//Числа, возводимые в степень
                    {
                        long pow_value = 1;
                        for (int j = 1; j <= value; ++j)//Степень
                        {
                            pow_value *= i;
                            printf("%11ld ",pow_value);
                        }
                        printf("\n");
                    }
                    function_result = fsc_ok;
                }
                break;
            }
            case 'a':
            {
                if (value < 0)
                    function_result = fsc_invalid_parameter;
                else
                {
                    int res = 0;
                    if (sum(value, &res) == fsc_ok)
                    {
                        printf("%d\n", res);
                        function_result = fsc_ok;
                    }
                    else
                        function_result = fsc_overflow;
                }
                break;
            }
            case 'f':
            {
                if (value < 0)
                    function_result = fsc_invalid_parameter;
                else
                {
                    int res = 1;
                    if (fact(value, &res) == fsc_ok)
                    {
                        printf("Факториал %d равен: %d\n",value, res);
                        function_result = fsc_ok;
                    }
                    else
                        function_result = fsc_overflow;
                }
                break;
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

