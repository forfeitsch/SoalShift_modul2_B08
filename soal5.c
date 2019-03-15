#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
    int count = 1;
    pid_t pid, sid;
    pid = fork();
    if(pid < 0) {
        exit(EXIT_FAILURE);
    }
    if(pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();

    if(sid < 0) {
        exit(EXIT_FAILURE);
    }
    if((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1) {
        time_t t2 = time(0);
        struct tm *tmp;
        char line[80];
        tmp = localtime(&t2);
        strftime(line, sizeof(line), "%d:%m:%Y-%H-%M", tmp);
        char path[100], t[100];
        if(count % 30 == 1){
            strcpy(t, line);
            strcpy(path, "/home/schielen/log/");
            strcat(path, t);
            strcat(path, "/");
            mkdir(path, 0777);
        }
        char str[10];

        strcpy(str, "");
        sprintf(str, "log%d", count);
        strcat(str, ".log");
        char strakhir[100];

        strcpy(strakhir, path);
        strcat(strakhir,str);
        FILE *fc, *fs;
        int c;
        fc = fopen("/var/log/syslog", "r");
        fs = fopen(strakhir, "w+");
        while(1) {
            c = fgetc(fc);
            if(feof(fc)) break;
            fputc(c, fs);
        }
        fclose(fc);
        fclose(fs);
        sleep(60);
        count++;
    }
    exit(EXIT_SUCCESS);
}
