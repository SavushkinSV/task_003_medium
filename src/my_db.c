#include "my_db.h"

/* Функция проверки аргумента коммандной строки */
void init_file(int argc, char *const argv[], FILE **fin) {
    if (1 == argc) {
        *fin = fopen(DEFAULT_FILENAME, "a+");
        // if (!fin) error_exit();
    }
    if (2 == argc) {
        *fin = fopen(argv[1], "a+");
        // if (!fin) error_exit();
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

    return result;
}

/* Функция вывода записей из файла в stdin */
void db_show(FILE *fin) {
    fseek(fin, 0, SEEK_SET);
    // printf("db_show fin=%p\n", fin);
    size_t len = 0;
    char *line = NULL;
    while (getline(&line, &len, fin) != EOF) {
        printf("%s", line);
    }
    // fclose(fin);
}

/* Функция добавления записей в файл */
void db_add(FILE *fin) {
    char product[256] = "";
    int price = 0;
    if (scanf("%255s %d", product, &price) != 2 || price < 0) error_exit();
    fseek(fin, 0, SEEK_END);
    time_t current_time = time(NULL);
    struct tm *now = localtime(&current_time);
    fprintf(fin, "%02d.%02d.%d ", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    fprintf(fin, "%02d:%02d:%02d ", now->tm_hour, now->tm_hour, now->tm_sec);
    fprintf(fin, "%s %d\n", product, price);
}
