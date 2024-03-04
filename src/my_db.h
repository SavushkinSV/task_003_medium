#ifndef MY_DB_H
#define MY_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DB_EXIT 0
#define DB_ADD 1
#define DB_SHOW 2

void error_exit();
void input_command();
int get_command(char *input_string);
void db_show();
void db_add();

#endif  // MY_DB_H