//
//  main.c
//  4
//
//  Created by Лена on 27.09.2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE_OF_BUFFER 128

enum status_codes
{
    fsc_ok,
    fsc_overflow,
    fsc_invalid_parameter,
    fsc_unknown,
};

double log_a_b(double a, double b)
{
    return (log(b) / log(a));
}

enum status_codes translation_10_to_x (char n, char* res, int x)
{
    int p = 0;
    int len_of_n = floor(log_a_b(x, n)) + 1;
    res[len_of_n] = 0;
    
    while (n > 0)
    {
        len_of_n--;
        
        if (n % x >= 10)
            res[len_of_n] = (n % x) - 10 + 'A';
        else
            res[len_of_n] = (n % x) + '0';
        
        n /= x;
        
        if ((p + 1) < (MAX_SIZE_OF_BUFFER - 1))
            ++p;
        else
            return fsc_overflow;
    }
    res[p] = 0;
    for (int i = 0, j = strlen(res) - 1; i < j; i++, j--)
    {
        char c = res[i];
        res[i] = res[j];
        res[j] = c;
    }
    return fsc_ok;
}


int main(int argc, const char * argv[])
{
    enum status_codes function_result = fsc_unknown;
    char flag = 0;
    if (argc < 2)
        function_result = fsc_invalid_parameter;
    else
    {
        flag = argv[1][1];
        function_result = fsc_ok;
    }

    //printf("%c\n", flag);
    
    if (function_result == fsc_ok)
    {
        switch (flag)
        {
            case 'r':
            {
                if (argc < 5)
                    function_result = fsc_invalid_parameter;
                else
                {
                    FILE* files_list[2];
                    files_list[0] = fopen(argv[3], "r");
                    files_list[1] = fopen(argv[2], "r");
                    FILE* file_output = fopen(argv[argc - 1], "w");
                    
                    if (files_list[0] == NULL || files_list[1] == NULL || file_output == NULL)
                    {
                        printf("Файл не найден\n");
                        function_result = fsc_invalid_parameter;
                    }
                    else
                    {
                        bool files_finish [2];
                        files_finish[0] = false;
                        files_finish[1] = false;
                        char c;
                        while (true)
                        {
                            for (int i = 0; i < 2; ++i)
                            {
                                bool token_ready = false;
                                while (!(files_finish[i]))
                                {
                                    c = fgetc(files_list[i]);
                                    if (c != EOF)
                                    {
                                        if (c == ' ' || c == '\n' || c == '\t')
                                        {
                                            if (token_ready)
                                            {
                                                fprintf(file_output, " ");
                                                //printf(" ");
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            fprintf(file_output, "%c", c);
                                            //printf("%c",c);
                                            token_ready = true;
                                        }
                                    }
                                    else
                                        files_finish[i] = true;
                                }
                            }
                            if (files_finish[0] && files_finish[1])
                                break;
                        }
                        
                        fclose(files_list[0]);
                        fclose(files_list[1]);
                        fclose(file_output);
                    }
                }
                break;
            }
            case 'a':
            {
                if (argc < 4)
                    function_result = fsc_invalid_parameter;
                else
                {
                    FILE* file_input = fopen(argv[2], "r");
                    FILE* file_output = fopen(argv[argc - 1], "w");
                    
                    if (file_input == NULL || file_output == NULL)
                    {
                        printf("Файл не найден\n");
                        function_result = fsc_invalid_parameter;
                    }
                    else
                    {
                        int i = 0;
                        char c;
                        bool token_ready = false;
                        char res[MAX_SIZE_OF_BUFFER] = {0};
                        while (((c = fgetc(file_input)) != EOF) && (function_result == fsc_ok))
                        {
                            if (c == ' ' || c == '\n' || c == '\t')
                            {
                                res[0] = c;
                                res[1] = 0;
                                if (token_ready)
                                {
                                    ++i;
                                    fprintf(file_output, " ");
                                    token_ready = false;
                                }
                            }
                            else
                            {
                                if ((i + 1) % 10 == 0)
                                {
                                    //char res[MAX_SIZE_OF_BUFFER];
                                    if (translation_10_to_x(c, res, 4)!= fsc_ok)
                                        function_result = fsc_overflow;
                                        
                                }
                                else
                                {
                                    if ((i + 1) % 2 == 0)
                                    {
                                        if (isupper(c))
                                            c = tolower(c);
                                        res[0] = c;
                                        res[1] = 0;
                                    }
                                    else
                                    {
                                        if ((i + 1) % 5 == 0)
                                        {
                                            //char res[MAX_SIZE_OF_BUFFER];
                                            if (translation_10_to_x(c, res, 8)!= fsc_ok)
                                                function_result = fsc_overflow;
                                        }
                                        else
                                        {
                                            res[0] = c;
                                            res[1] = 0;
                                            //printf("%s\n", res);
                                        }
                                    }
                                }
                                if (function_result == fsc_ok)
                                {
                                    //printf("%s\n", res);
                                    fprintf(file_output, "%s", res);
                                    token_ready = true;
                                }

                            }
                        }
                    }
                    fclose(file_input);
                    fclose(file_output);
                }

                break;
            }
            default:
                function_result = fsc_invalid_parameter;
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
