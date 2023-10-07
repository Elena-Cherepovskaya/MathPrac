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

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
    fsc_memory_error_detected,
};


int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

void printf_of_array(int* array, int size)
{
    for (int i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n");
}

int nearest_values_from_array(int value, int* array, int size_of_array)
{
    int nearest_value = INT_MAX;
    for (int i = 0; i < size_of_array; ++i)
    {
        if (abs(max(array[i], value) - min(array[i], value)) < nearest_value)
            nearest_value = array[i];
    }
    return nearest_value;
}

int main(int argc, const char * argv[])
{
    enum status_codes function_result = fsc_unknown;
    
    int a = -1000;
    int b = 1000;
    int size_of_array_A = 10 + rand() % (10000 - 10 + 1);
    int size_of_array_B = 10 + rand() % (10000 - 10 + 1);
    
    int* A = malloc(sizeof(int) * size_of_array_A);
    int* B = malloc(sizeof(int) * size_of_array_B);
    int* C = malloc(sizeof(int) * size_of_array_A);
    
    if (A == NULL || B == NULL || C == NULL)
        function_result = fsc_memory_error_detected;
    else
        function_result = fsc_ok;
    
    if (function_result == fsc_ok)
    {
        for (int i = 0; i < size_of_array_A; ++i)
            A[i] = a + rand() % (b - a + 1);
        for(int i = 0; i < size_of_array_B; ++i)
            B[i] = a + rand() % (b - a + 1);
        
        printf("A: ");
        printf_of_array(A, size_of_array_A);
        printf("B: ");
        printf_of_array(B, size_of_array_B);

        for (int i = 0; i < size_of_array_A; ++i)
            C[i] = A[i] + nearest_values_from_array(A[i], B, size_of_array_B);
        
        printf("C: ");
        printf_of_array(C, size_of_array_A);
        
    }
    
    free(A);
    free(B);
    free(C);
    
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
    
    return function_result == fsc_ok ? 0 : 1;
}
