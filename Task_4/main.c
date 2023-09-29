//
//  main.c
//  4
//
//  Created by Лена on 27.09.2023.
//

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE_OF_BUFFER 256
enum status_codes
{
    fsc_ok,
    fsc_invalid_parameter,
    fsc_unknown,
};

int main(int argc, const char * argv[])
{
    enum status_codes function_result = fsc_unknown;
    
    const char* tmp_file_input = NULL;
    const char* tmp_file_output = NULL;
    char buffer[MAX_SIZE_OF_BUFFER];
    char flag;
    if (argc >= 3)
    {
        for (int i = 1; i < 3; ++i)
        {
            if ((argv[i][0] == '-' || argv[i][0] == '/') && (strlen(argv[i]) <= 3))
            {
                if (argv[i][1] == 'n')
                {
                    if (argc == 4)
                    {
                        flag = argv[i][2];
                        tmp_file_output = argv[3];
                        function_result = fsc_ok;
                    }
                    else
                    {
                        function_result = fsc_invalid_parameter;
                    }
                }
                else
                {
                    flag = argv[i][1];
                    function_result = fsc_ok;
                }
            }
            else
            {
                tmp_file_input = argv[i];
                function_result = fsc_ok;
            }
        }
    }
    else
    {
        function_result = fsc_invalid_parameter;
    }
    
    if (tmp_file_output == NULL)
    {
        int index_file_name = 0;
        //Ищем начало имени файла в пути
        for (int i = strlen(tmp_file_input) - 1; i >= 0; i--)
        {
            if (tmp_file_input[i] == '/')
            {
                //Формуруем путь к выходному файлу, не доходя до имени
                for (int j = 0; j <= i; ++j)
                {
                    buffer[j] = tmp_file_input[j];
                }
                index_file_name = i;
                break;
            }
            index_file_name = i - 1;
        }
        
        //Добавляем к имени файла префикс "out_"
        strcat(buffer, "out_");
        //Дозаписываем остаток пути к выходному файлу
        for (int j = index_file_name + 1; j < strlen(tmp_file_input); ++j)
        {
            buffer[j+4] = tmp_file_input[j];
        }
        tmp_file_output = buffer;
        function_result = fsc_ok;
    }
    

    //printf("\n");    printf("%c\n", flag);
    //printf("%s\n", tmp_file_input);
    //printf("%s\n", buffer);

    FILE* file_input = NULL;
    FILE* file_output = NULL;
    
    if (function_result != fsc_invalid_parameter)
    {
        file_input = fopen(tmp_file_input, "r");
        file_output = fopen(tmp_file_output, "w");
    }
    
    if (file_input == NULL || file_output == NULL)
    {
        printf("Файл не найден\n");
        function_result = fsc_invalid_parameter;
    }
    
    if (function_result != fsc_invalid_parameter)
    {
        switch (flag)
        {
            case 'd':
            {
                char c;
                while ((c = fgetc(file_input)) != EOF)
                {
                    if (c < '0' || c > '9')
                        fputc(c, file_output);
                }
                break;
            }
            case 'i':
            {
                char str[MAX_SIZE_OF_BUFFER];
                int col = 0;
                while (fgets (str, MAX_SIZE_OF_BUFFER, file_input))
                {
                    for (char* p = str; *p != 0; ++p)
                    {
                        if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z'))
                        {
                            ++col;
                        }
                    }
                    fprintf(file_output, "%d\n", col);
                    col = 0;
                }
                break;
            }
            case 's':
            {
                char str[MAX_SIZE_OF_BUFFER];
                int col = 0;
                while (fgets (str, MAX_SIZE_OF_BUFFER, file_input))
                {
                    for (char* p = str; *p != 0; ++p)
                    {
                        if ((*p < 'A' || *p > 'Z') && (*p < 'a' || *p > 'z') && (*p < '0' || *p > '9') && (*p != ' '))
                        {
                            ++col;
                        }
                    }
                    fprintf(file_output, "%d\n", col);
                    col = 0;
                }
                break;
            }
            case 'a':
            {
                char str[MAX_SIZE_OF_BUFFER];
                while (fgets (str, MAX_SIZE_OF_BUFFER, file_input))
                {
                    for (char* p = str; *p != 0; ++p)
                    {
                        if (*p < '0' || *p > '9')
                            fprintf(file_output, "%x", *p);
                    }
                    fprintf(file_output, "\n");
                }
                break;
            }
            default:
                printf("flag_result is unknown\n");
        }
    }
    
    switch (function_result)
    {
        case fsc_ok:
            break;
        case fsc_invalid_parameter:
            printf("Invalid parameter detected\n");
            break;
        default:
            printf("function_result is unknown\n");
    }

    fclose(file_input);
    fclose(file_output);
    return function_result == fsc_ok ? 0 : 1;
}
