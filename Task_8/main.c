//
//  main.c
//  8
//
//  Created by Лена on 03.10.2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE_OF_BUFFER 256

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int char_to_num (char c)
{
    return (isupper(c)) ? (c - 'A' + 10) : (c - 'a' + 10);
}

int main(int argc, const char * argv[])
{
    enum status_codes function_result = fsc_unknown;
    
    char flag = 0;
    FILE* file_input = NULL;
    FILE* file_output = NULL;
    if (argc < 3)
        function_result = fsc_invalid_parameter;
    else
    {
        file_input = fopen(argv[1], "r");
        file_output = fopen(argv[2], "w");
        flag = argv[1][1];
        function_result = fsc_ok;
    }
    
    if (file_input == NULL || file_output == NULL)
    {
        printf("Файл не найден\n");
        function_result = fsc_invalid_parameter;
    }
    
    if (function_result == fsc_ok)
    {
        int i = 0;
        char c;
        bool token_ready = false;
        char str[MAX_SIZE_OF_BUFFER] = {0};
        int base_of_number_system = 0;
        while (true)
        {
            
            int value_EOF = fgetc(file_input);
            c = value_EOF;
            if (c == ' ' || c == '\n' || c == '\t' || value_EOF == EOF)
            {
                if (token_ready)
                {
                    str[i] = 0;
                    fprintf(file_output, "%s %d\n", str, base_of_number_system);
                    token_ready = false;
                    i = 0;
                }
            }
            else
            {
                int value = isalpha(c) ? char_to_num(c) : c - '0';
                
                base_of_number_system = max(base_of_number_system, value + 1);
                token_ready = true;
                
                if (i + 1 < MAX_SIZE_OF_BUFFER)
                {
                    str[i] = c;
                    ++i;
                }
                else
                {
                    function_result = fsc_overflow;
                    break;
                }
            }
            if (value_EOF == EOF)
                break;
        }
    }
    fclose(file_input);
    fclose(file_output);
    
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
