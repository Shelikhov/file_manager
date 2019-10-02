#include "header.h"

int count_of_slash(char *path){

        int slash = 0;
        for (int i=0; i<sizeof(path); i++){
                if (path[i] == '/'){
                        slash++;
                }
        }
        return slash;
}
