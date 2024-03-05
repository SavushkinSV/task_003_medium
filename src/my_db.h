#ifndef MY_DB_H
#define MY_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 256
#define SIZE_ARRAY 36
#define DEFAULT_FILENAME "../data/database.txt"
#define DB_EXIT 0
#define DB_ADD 1
#define DB_SHOW 2
#define DB_FIND 3
#define DB_MAX 4

typedef struct {
    int day;
    int month;
    int year;
    int hour;
    int min;
    int sec;
    char name[MAX_LEN];
    int price;
} Row;

void init_file(int argc, char *const argv[], FILE **);
void error_exit();
void input_command(FILE *);
int get_command(char *input_string);
void db_show(FILE *fin);
void db_add(FILE *fin);

void db_find(FILE *fin);
void check_input_date(Row *date);
int parse_line(Row *row, char *str);
int compare_date(Row *const date1, Row *const date2);

void db_max(FILE *fin);
int add_rows(Row row, Row rows_array[SIZE_ARRAY], int size);
void print_max(Row rows_array[SIZE_ARRAY], int size);

#endif  // MY_DB_H