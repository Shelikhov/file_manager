#include "header.h"

int open_file(char *file, char *file2){
        int t=0;
        int p=0;
        for (int i=0; i<100;i++){
                if(file[i] != '\0') t++;
                if(file2[i] != '\0') p++;
        }

        char file3[100];

        for (int i=0; i<100; i++){
                file3[i] = '\0';
        }

        strncpy(file3,file,t);
        strncpy(file3,file2,p);

        FILE *fd;
        fd = fopen(file3,"r");
        if(fd == NULL){
                perror(file3);
                return 0;
        }
        initscr();
        keypad(stdscr, TRUE);
        int c;
        int line=0;
        while ( (c=getc(fd)) != EOF){
                if (c == '\n') line++;
                if (line > LINES -2) break;
                addch(c);
        }
        fclose(fd);
        refresh();
        getch();
        endwin();
        return 0;
}
