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
 * "runId": "586"
 * */




#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int read_one_string(char **buffer) {
    int buffer_size = 100, buffer_move = 0, buffer_count = 1;
    size_t buffer_len = 0;
    *buffer = (char *) malloc (buffer_size * sizeof (char));
    if (*buffer == NULL) {
        return -1;
    }
    while (1) {

        if (!fgets (*buffer + buffer_move, buffer_size / buffer_count, stdin)) {
            return -1;
        }
        buffer_len = strlen ((*buffer) + buffer_move);
        if ((*buffer)[buffer_len + buffer_move - 1] != '\n') {
            buffer_size *= 2;
            buffer_count = 2;
            *buffer = (char *) realloc (*buffer, buffer_size);
            if (*buffer == NULL) {
                return -1;
            }
            buffer_move += buffer_len;
        } else {
            (*buffer)[buffer_len + buffer_move - 1] = '\0';
            break;
        }
    }
    return 0;
}

int read_all_strings(char ***strings) {
    char *buffer;
    int strings_col = 100;
    *strings = (char **) malloc (strings_col * sizeof (char *));
    if (*strings == NULL) {
        if (buffer) free (buffer);
        return 0;
    }
    int size = 0, flag = 0;
    int check = read_one_string (&buffer);
    if (check != -1) {
        flag = 1;
        (*strings)[size] = buffer;
        ++size;
    }
    while (check != -1) {
        check = read_one_string (&buffer);
        if (size == strings_col - 1) {
            *strings = (char **) realloc (*strings, strings_col * 2 * sizeof (char *));
            if (*strings == NULL) {
                if (buffer) free (buffer);
                return 0;
            }
        }
        (*strings)[size] = buffer;
        ++size;
    }
    if (flag == 0) {
        return 0;
    }
    return size;
}

int check_one(char *string) {
    int iterator = 0, count = 0;
    size_t length = strlen (string);
    for (iterator = 0; iterator < length; ++iterator) {
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
    int iterator = 0, result_size = 0;
    *result_strings = (char **) malloc (size * sizeof (char *));
    for (iterator = 0; iterator < size; ++iterator) {
        if (check_one (strings_to_check[iterator]) == 0) {
            (*result_strings)[result_size++] = strings_to_check[iterator];
        }
    }
    return result_size;
}


int main() {
    char **strings, **res;
    int size = read_all_strings (&strings), i = 0;
    if (size == 0) {
        free (strings);
        printf ("[error]");
        return 0;
    }

    int res_size = check_brackets (strings, size, &res);
    if (res == NULL) {
        for (i = 0; i < size; i++) {
            free (strings[i]);
        }
        free (strings);
        free (res);
        return 0;
    } else {
        for (i = 0; i < res_size; i++) {
            printf ("%s\n", res[i]);
        }
    }

    for (i = 0; i < size; i++) {
        if (strings[i]) free (strings[i]);
    }
    if (strings) free (strings);

    if (res) free (res);

    return 0;
}
