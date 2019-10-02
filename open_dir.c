#include "header.h"

int open_dir(char array[]){

        DIR *dir;
        struct dirent *entry;

        dir = opendir(array);

        if(!dir){
                perror("diropen");
                exit(1);
        }

        count_of_dir = 0;


        while( (entry = readdir(dir)) != NULL ){

                strncpy(items[count_of_dir], entry->d_name, sizeof(entry->d_name));
                count_of_dir++;
        }

        closedir(dir);

        return count_of_dir;
}
