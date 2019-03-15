#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

time_t a_time(char *path) {
    struct stat attr;
    stat(path, &attr);
    return (attr.st_atime);
}



// int main() {
    
// }

int main() {
  pid_t pid, sid;
  pid_t child_id;
  int i=1;
  child_id = fork();
  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  if (child_id < 0) {
    exit(EXIT_FAILURE);
  }

  while(1) {
        DIR *dir;
  struct dirent *ent;
  
//   int stat(const char *pathname, struct stat *statbuf);
//   char pathname[100] = "/home/schielen/Documents/makanan/";

  if ((dir = opendir ("/home/schielen/Documents/makanan/")) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
         char str[100] = "/makan_enak.txt";
         time_t acc; // access time
         time_t ccc; // local time
         time(&ccc);
         struct tm *info;
         acc = a_time("/home/schielen/Documents/makanan/makan_enak.txt");
         info = localtime(&acc);
        // printf("%s\n", asctime(info));
        // if(time < 30) {
        // }
        if(difftime(ccc, acc)<=30){
            FILE *file;
            char tmp[100];
            
            sprintf(tmp,"/home/schielen/Documents/makanan/makan_sehat%d.txt",i);
            file = fopen(tmp,"w+");
        }
        
        }
    }
        i++;
        sleep(5);
    }
    
  exit(EXIT_SUCCESS);


  
//     closedir (dir);
// }

  
