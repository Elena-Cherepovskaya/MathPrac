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

//Для возведения в степень также можно было пользоваться фонкцией pow
long power(int n, int p)
{
    long res = 1;
    for (int i = 1; i <= p; ++i)
        res *= n;
    
    return res;
}

//Для перевода строки в число можно было такде пользоваться функцией atoi
bool str_to_num(const char* str, int* res)
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
            return false;
    }
    
    if (str[0] == '-')
        *res *= (-1);
    
    return true;
}

bool is_num_prime(int n)
{
    n = abs(n);
    for (int i = 2; i < (int)sqrt(n) + 1; ++i)
        if (n % i == 0)
            return false;
    return true;
}

int len_of_value(int value)
{
    abs(value);
    int col = 0;
    while (value > 0)
    {
        value /= 10;
        ++col;
    }
    return col;
}

char* int_to_str(int value)
{
    value = abs(value);
    int i = 0;
    char* res = malloc(sizeof(char) * (len_of_value(value) + 1));
    long del = power(10, len_of_value(value) - 1);
    while (value > 0)
    {
        res[i] = (int)(value / del) + '0';
        value %= del;
        del = (int)(del / 10);
        ++i;
    }
    
    res[i] = 0;
    return res;
}

bool sum (int n, int* res)
{
    for (int i = 1; i <= n; ++i)
    {
        *res += i;
        if (*res < 0)
            return false;
    }
    return true;
}

bool fact(int n, int* res)
{
    if (n < 0)
        return false;
    *res = 1;
    for (int i = 1; i <= n; ++i)
    {
        *res *= i;
        if (*res < 0)
            return false;
    }
    return true;
}

int main(int argc, const char * argv[])
{
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
                    {
                        printf("Найдено два флага\n");
                        return 1;
                    }
                    
                    flag_ready = true;
                    break;
                }
        }
        
        int read_value;
        if (str_to_num(argv[i], &read_value))
        {
            value = read_value;
            if (value_ready)
            {
                printf("Найдено два числа\n");
                return 1;
            }
            value_ready = true;
        }
        
    }
    if (!(flag_ready))
    {
        printf("Флаг не найден\n");
        return 1;
    }
    
    if (!(value_ready))
    {
        printf("Число не найдено\n");
        return 1;
    }
    
    //printf("%d %c\n", value, flag);
    
    switch(flag)
    {
        case 'h':
        {
            bool f = false;
            for (int i = 1; i <= 100; ++i)
                if (i % value == 0)
                {
                    f = true;
                    printf("%d ",i);
                }
            
            if (!f)
                printf("Кратных числ нет");
            
            printf("\n");
            break;
        }
        case 'p':
        {
            if (is_num_prime(value))
                printf("Число %d простое\n", value);
            else
                printf("Число %d составное\n", value);
            break;
        }
        case 's':
        {
            char* p = int_to_str(value);
            char* p_tmp = int_to_str(value);
            for (; *p_tmp != 0; ++p_tmp)
                printf("%c ",*p_tmp);
            
            printf("\n");
            free(p);
            break;
        }
        case 'e':
        {
            if (value > 10)
                printf("Ошибка. Введенное число больше 10. \n");
                if (value < 0)
                    printf("Ошибка. ВВеденное число отрицательное.\n");
                else
                {
                    for (int i = 1; i <= value; ++i)//Подписи столбцов
                        printf("%11d ", i);
                    printf("\n\n");
                    
                    for (int i = 1; i <= 10; ++i)//Числа, возводимые в степень
                    {
                        for (int j = 1; j <= value; ++j)//Степень
                            printf("%11ld ", power(i, j));
                        printf("\n");
                    }
                }
            break;
        }
        case 'a':
        {
            if (value < 0)
                printf("Ошибка. ВВеденное число отрицательное.\n");
            else
            {
                int res = 0;
                if (sum(value, &res))
                    printf("%d\n", res);
                else
                    printf("Переполенение\n");
            }
            break;
        }
        case 'f':
        {
            if (value < 0)
                printf("Ошибка. ВВеденное число отрицательное.\n");
            else
            {
                int res = 1;
                if (fact(value, &res))
                    printf("Факториал %d равен: %d\n",value, res);
                else
                    printf("Переполение\n");
            }
            break;
        }
    }
    
    return 0;
}
