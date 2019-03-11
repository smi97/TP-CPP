/*
 * "name": "Максим",
 * "surname": "Сударев",
 * "group": "АПО-13"
 * "task":
 * Задача A-7. Задача о скобочной последовательности
Time limit:	14 s
Memory limit:	64 M
Составить программу построчной обработки текста. Суть обработки - отбор строк, содержащих одинаковое количество открывающих и закрывающих круглых скобок.

Программа считывает входные данные со стандартного ввода, и печатает результат в стандартный вывод.

Процедура отбора нужных строк должна быть оформлена в виде отдельной функции, которой на вход подается массив строк (который необходимо обработать), количество переданных строк, а также указатель на переменную, в которой необходимо разместить результат - массив отобранных строк.
В качестве возвращаемого значения функция должна возвращать количество строк, содержащихся в результирующем массиве.

Программа должна уметь обрабатывать ошибки - такие как неверные входные данные(отсутствие входных строк) или ошибки выделения памяти и т.п.
В случае возникновения ошибки нужно выводить об этом сообщение "[error]" и завершать выполнение программы.

ВАЖНО! Программа в любом случае должна возвращать 0. Не пишите return -1, exit(1) и т.п. Даже если обнаружилась какая-то ошибка, все равно необходимо вернуть 0! (и напечатать [error] в stdout)."
 *
 * runId = 1017
 * */


#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int read_all_strings(char ***strings) {
    size_t strings_max_col = 100;
    size_t string_size = 100;
    ssize_t getline_result = 0;
    int strings_amount = 0;

    *strings = (char **) malloc (strings_max_col * sizeof (char *));
    if (*strings == NULL) {
        return 0;
    }

    (*strings)[strings_amount] = (char *) malloc (string_size * sizeof (char));
    if((*strings)[strings_amount] == NULL) {
        return 0;
    }
    getline_result = getline(&(*strings)[strings_amount], &string_size, stdin);
    while (getline_result != -1) {
        if (strings_amount == strings_max_col - 1) {
            char ** temp = (char **) realloc (*strings, strings_max_col * 2 * sizeof (char *));
            if (*temp == NULL) {
                return 0;
            }
            for(int i = 0; i < strings_amount; ++i) {
                free ((*strings)[i]);
            }
            free(strings);
            *strings = temp;
        }
        ++strings_amount;
        (*strings)[strings_amount] = (char *) malloc (string_size * sizeof (char));
        if((*strings)[strings_amount] == NULL) {
            for(int i = 0; i < strings_amount; ++i) {
                free ((*strings)[i]);
                return 0;
            }
        }
        getline_result = getline(&(*strings)[strings_amount], &string_size, stdin);
        if(getline_result == -1)
        {
            free((*strings)[strings_amount]);
        }
    }
    return strings_amount;
}

int check_one(char *string) {
    int count = 0;
    size_t length = strlen (string);
    for (int iterator = 0; iterator < length; ++iterator) {
        if (string[iterator] == '(') {
            ++count;
        }
        if (string[iterator] == ')' && count == 0) {
            return -1;
        }
        if (string[iterator] == ')' && count != 0) {
            --count;
        }
    }
    if (count != 0) {
        return -1;
    }
    return 0;
}

int check_brackets(char **strings_to_check, int size, char ***result_strings) {
    int result_size = 0;
    *result_strings = (char **) malloc (size * sizeof (char *));
    if(*result_strings == NULL) {
        printf ("[error]");
        return 0;
    }
    for (int iterator = 0; iterator < size; ++iterator) {
        if (check_one (strings_to_check[iterator]) == 0) {
            (*result_strings)[result_size++] = strings_to_check[iterator];
        }
    }
    return result_size;
}


int main() {
    char **strings = NULL, **res  = NULL;
    int size = 0;
    size = read_all_strings (&strings);
    if (size == 0) {
        free (strings);
        printf ("[error]");
        return 0;
    }

    int res_size = check_brackets (strings, size, &res);
    if (res == NULL) {
        for (int i = 0; i < size; i++) {
            free (strings[i]);
        }
        free (strings);
        free (res);
        return 0;
    }
    for (int i = 0; i < res_size; i++) {
        printf ("%s", res[i]);
    }


    for (int i = 0; i < size; i++) {
        if (strings[i]) free (strings[i]);
    }
    if (strings) free (strings);

    if (res) free (res);

    return 0;
}
