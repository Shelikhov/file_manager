#include "header.h"

char *sl = "/";
char *dot = ".";
char *dot2 = "..";



int main(){

        /*creating windows and subwindows*/
        WINDOW *wnd1;//left window
        WINDOW *subwnd1;//subwindow of wnd1
        WINDOW *wnd2;//right window
        WINDOW *subwnd2;//subwindow of wnd2
        WINDOW *subwnd;//subwindow for moving between subwnd1 and subwnd2

        char path1[100];//current path of subwnd1
        char path2[100];//current path of subwnd2
        char path[100];//path for moving between path1 and path2

        getcwd(path1,100);
        getcwd(path2,100);
        strncpy(path,path1,100);

        int slash;//current count of slashes
        slash = count_of_slash(path);
        count_of_dir = open_dir(path);//count of directories in current subwindow

        initscr();

        start_color();
        init_pair(1,COLOR_GREEN,COLOR_BLACK);
        init_pair(2,COLOR_RED,COLOR_BLACK);
        init_pair(3,COLOR_YELLOW,COLOR_BLACK);
 
        attron(COLOR_PAIR(3));
        attron(A_BLINK);
        attron(A_BOLD);
        move(41,2);
        printw("EXIT -> F2     To change window -> F3     File editor -> F4");
        attroff(A_BLINK);
        attroff(A_BOLD);

        int choice = 0;
        int childExitStatus;
        curs_set(0);
//      wbkgd(stdscr, COLOR_PAIR(1));
        refresh();

        /*locations for windows*/
        wnd1=newwin(40,70,1,1);
        wnd2=newwin(40,70,1,71);

        /*boards for windows*/
        box(wnd1,ACS_VLINE,ACS_HLINE);
        box(wnd2,ACS_VLINE,ACS_HLINE);

        /*locations for subwindows*/
        subwnd1=derwin(wnd1,38,28,1,1);
        subwnd2=derwin(wnd2,38,28,1,1);

        /*creating color in windows*/
        wattron(subwnd1,COLOR_PAIR(1));
        wattron(subwnd1,A_BOLD);
        wattron(subwnd2,COLOR_PAIR(2));
        wattron(subwnd2,A_BOLD);

        /*
        wbkgd(wnd1, COLOR_PAIR(2));
        wbkgd(wnd2, COLOR_PAIR(3));
        wbkgd(stdscr, COLOR_PAIR(1));*/
        /*allows to press keys into subwindows*/
        keypad(subwnd1,true);
        keypad(subwnd2,true);

        subwnd = subwnd1;

        wclear(subwnd1);
        wclear(subwnd2);

        for (int i=0; i<count_of_dir; i++){
                if (i == choice){
                        wprintw(subwnd1,">");
                        wprintw(subwnd2,">");
                }
                else {
                        wprintw(subwnd1," ");
                        wprintw(subwnd2," ");
                }
                wprintw(subwnd1,"%s\n",items[i]);
                wprintw(subwnd2,"%s\n",items[i]);
        }
        wrefresh(wnd1);
        wrefresh(wnd2);

        bool stop = true;

        while(stop){
                wclear(subwnd);
                for (int i=0; i<count_of_dir; i++){
                        if (i == choice){
                                wprintw(subwnd,">");
                        }
                        else {
                                wprintw(subwnd," ");
                        }
                        wprintw(subwnd,"%s\n",items[i]);
                }
                wrefresh(wnd1);

                switch (wgetch(subwnd)){
                        case KEY_UP:
                                if(choice)
                                        choice--;
                                break;
                        case KEY_DOWN:
                                if(choice != count_of_dir-1)
                                        choice++;
                                break;
                        case 10:
                                if (items[choice] == dot){
                                //choice=0;
                                }
                                else if (strncmp(items[choice], dot2, 2) ==0 ){
                                        slash = count_of_slash(path);
                                        if (strncmp(path,path1,100) == 0){
                                                path_back(path1,slash);
                                                strncpy(path,path1,100);
                                        }
                                        else{
                                                path_back(path2,slash);
                                                strncpy(path,path2,100);
                                        }
                                        count_of_dir = open_dir(path);
                                        choice = 0;
                                        break;
                                }
                                else{
                                        struct stat st;
                                        stat(path,&st);
                                        if (S_ISDIR(st.st_mode)){
                                                if (strncmp(path,path1,100) == 0){
                                                        strcat(path1,sl);
                                                        strcat(path1,items[choice]);
                                                        strncpy(path,path1,100);
                                                }
                                                else{
                                                        strcat(path2,sl);
                                                        strcat(path2,items[choice]);
                                                        strncpy(path,path2,100);
                                                }
                                                count_of_dir = open_dir(path);
                                                choice=0;
                                                break;
                                        }
                                        //else if (S_ISREG(st.st_mode)){
                                        //      open_file(path, items[choice]);
                                        //      break;
                                        //}

                                }
                        case KEY_F(3):
                                if (subwnd == subwnd1){
                                        subwnd = subwnd2;
                                        strncpy(path,path2,100);
                                        slash = count_of_slash(path);
                                        count_of_dir = open_dir(path);
                                        choice = 0;
                                        break;
                                }
                                else{
                                        subwnd = subwnd1;
                                        strncpy(path,path1,100);
                                        slash = count_of_slash(path);
                                        count_of_dir = open_dir(path);
                                        choice = 0;
                                        break;
                                }
                        case KEY_F(2):
                                stop = false;
                                break;
                        case KEY_F(4):
                                childExitStatus=piddd();
                                mvwprintw(stdscr, getmaxy(stdscr) - 3, getmaxx(stdscr) - 3, "%d", WEXITSTATUS(childExitStatus));
                                refresh();
                                wgetch(stdscr);
                                break;

/*                              pid_t pid = fork();
                                if (pid == 0){
                                        if(execl("/C/test/pr","pr",NULL)<0){
                                                printf("errorrr\n");
                                                exit(-2);
                                        }
                                        else{
                                                printf("process start\n");
                                        }
                                }
                                exit(0);
                                break;
*/
                }
        }

        /*removing windows*/
        delwin(subwnd);
        delwin(subwnd1);
        delwin(subwnd2);
        delwin(wnd1);
        delwin(wnd2);
        endwin();

        return 0;
}
           
