//
//  main.c
//  9
//
//  Created by Лена on 04.10.2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE_OF_ARRAY 128

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
};

void printf_of_array(int* array, int size)
{
    for (int i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n");
}

int main(int argc, const char * argv[])
{
    enum status_codes function_result = fsc_invalid_parameter;
       
   int a = 0;
   int b = 0;
   
    if (argc == 3)
        {
            a = atoi(argv[1]);
            b = atoi(argv[2]);
            
            if (a < b)
                function_result = fsc_ok;
        }
           
   if (function_result == fsc_ok)
   {
       int array_of_random_values[SIZE_OF_ARRAY];
       
       int index_list_of_min[SIZE_OF_ARRAY];
       int index_list_of_max[SIZE_OF_ARRAY];
       int max_value = a;
       int min_value = b;
       int i_min = 0;
       int i_max = 0;
       
       for (int i = 0; i < SIZE_OF_ARRAY; ++i)
           array_of_random_values[i] = a + rand() % (b - a + 1);
        
        printf("Первоначальный массив:\n");
        printf_of_array(array_of_random_values, SIZE_OF_ARRAY);
        
        for (int i = 0; i < SIZE_OF_ARRAY; ++i)
        {
            if (array_of_random_values[i] > max_value)
            {
                i_max = 0;
                max_value = array_of_random_values[i];
                index_list_of_max[i_max] = i;
                ++i_max;
            }
            else
            {
                if (array_of_random_values[i] == max_value)
                {
                    index_list_of_max[i_max] = i;
                    ++i_max;
                }
            }
            
            
            if (array_of_random_values[i] < min_value)
            {
                i_min = 0;
                min_value = array_of_random_values[i];
                index_list_of_min[i_min] = i;
                ++i_min;
            }
            else
            {
                if (array_of_random_values[i] == min_value)
                {
                    index_list_of_min[i_min] = i;
                    ++i_min;
                }
            }
        }
       for (int i = 0; i < i_max; ++i)
           array_of_random_values[index_list_of_max[i]] = min_value;
       
       for (int i = 0; i < i_min; ++i)
           array_of_random_values[index_list_of_min[i]] = max_value;
       
        printf("Обработанный массив:\n");
        printf_of_array(array_of_random_values, SIZE_OF_ARRAY);
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
