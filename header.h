#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

char items[100][100];
int count_of_dir;

int open_dir(char array[]);
int count_of_slash(char *path);
int path_back(char *path, int slash);
//int open_file(char *file, char *file2);
int piddd(void);
