#include "my_db.h"

/* Функция проверки аргумента коммандной строки */
void init_file(int argc, char *const argv[], FILE **fin) {
    if (1 == argc) {
        *fin = fopen(DEFAULT_FILENAME, "a+");
    }
    if (2 == argc) {
        *fin = fopen(argv[1], "a+");
    }
}

/* Функция завершения программы с ошибкой */
void error_exit() {
    fprintf(stderr, "Puck you, Verter!");
    exit(EXIT_FAILURE);
}

/* Функция ввода команды */
void input_command(FILE *fin) {
    char input_string[256] = "";
    int command = -1;
    while (command != DB_EXIT) {
        command = get_command(input_string);
        switch (command) {
            case (DB_ADD):
                db_add(fin);
                break;
            case (DB_SHOW):
                db_show(fin);
                break;
            case (DB_EXIT):
                break;
            case (DB_FIND):
                db_find(fin);
                break;
            default:
                error_exit();
                break;
        }
    }
}

/* Функция получения команды. Возвращает код комманды*/
int get_command(char *input_string) {
    int result = -1;
    scanf("%255s", input_string);
    if (strcmp(input_string, "ADD") == 0) result = DB_ADD;
    if (strcmp(input_string, "SHOW") == 0) result = DB_SHOW;
    if (strcmp(input_string, "EXIT") == 0) result = DB_EXIT;
    if (strcmp(input_string, "FIND") == 0) result = DB_FIND;

    return result;
}

/* Функция вывода записей из файла в stdin */
void db_show(FILE *fin) {
    fseek(fin, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    while (getline(&line, &len, fin) != EOF) {
        printf("%s", line);
    }
}

/* Функция добавления записей в файл */
void db_add(FILE *fin) {
    char product[MAX_LEN] = "";
    int price = 0;
    if (scanf("%255s %d", product, &price) != 2 || price < 0) error_exit();
    fseek(fin, 0, SEEK_END);
    time_t current_time = time(NULL);
    struct tm *now = localtime(&current_time);
    fprintf(fin, "%02d.%02d.%d ", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    fprintf(fin, "%02d:%02d:%02d ", now->tm_hour, now->tm_min, now->tm_sec);
    fprintf(fin, "%s %d\n", product, price);
}

/* Функция поиска записей по дате */
void db_find(FILE *fin) {
    Row input_date;
    check_input_date(&input_date);
    fseek(fin, 0, SEEK_SET);
    size_t len = 0;
    char *line = NULL;
    Row current_row;
    int count = 0;
    while (getline(&line, &len, fin) != EOF) {
        parse_line(&current_row, line);
        if (compare_date(&current_row, &input_date)) {
            printf("%s", line);
            count++;
        }
    }
    if (!count) printf("NO DATA");
}

/* Функция проверки введенной даты */
void check_input_date(Row *date) {
    if (scanf("%d.%d.%d", &date->day, &date->month, &date->year) != 3) error_exit();
    if (date->day <= 0 || date->day > 31) error_exit();
    if (date->month <= 0 || date->month > 12) error_exit();
}

/* Функция парсинга строки из файла */
int parse_line(Row *row, char *str) {
    int error = 0;
    if (sscanf(str, "%d.%d.%d %d:%d:%d %255s %d", &row->day, &row->month, &row->year, &row->hour, &row->min,
               &row->sec, row->name, &row->price) != 8)
        error = -1;
    return error;
}

/* Функция сравления дат возвращает 0 если не равны */
int compare_date(Row *const date1, Row *const date2) {
    return (date1->day == date2->day) || (date1->month == date2->month) || (date1->year == date2->year);
}
