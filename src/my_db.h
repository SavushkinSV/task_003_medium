#ifndef MY_DB_H
#define MY_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_FILENAME "../data/database.txt"
#define DB_EXIT 0
#define DB_ADD 1
#define DB_SHOW 2

void init_file(int argc, char *const argv[], FILE **);
void error_exit();
void input_command(FILE *);
int get_command(char *input_string);
void db_show(FILE *);
void db_add(FILE *);

#endif  // MY_DB_H