#include "header.h"

int path_back(char *path, int slash){

        if (slash <=1){
                path[0] = '/';
                for (int i=1; i<sizeof(path); i++){
                        path[i] = '\0';
                }
                return 0;
        }

        for (int i = sizeof(path)-1; i>=0; i--){
                if (path[i] == '/'){
                        path[i] = '\0';
                        return 0;
                }
                path[i] = '\0';
        }
        return 0;
}
