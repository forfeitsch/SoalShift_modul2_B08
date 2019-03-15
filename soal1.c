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

int main() {
  pid_t pid, sid;

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

  DIR *dir;
  struct dirent *ent;
  char* name;
  char oldname[1000];
  const char* ext = ".png";
  const char* add = "_grey.png";
  char p_old[100]="/home/schielen/modul2/gambar/";
  char p_new[100]="/home/schielen/modul2/";
  char temp[1000];
  char newname[100];
  char* filename;
  char* str;
  if ((dir = opendir ("/home/schielen/modul2/gambar/")) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
        str = strstr(ent->d_name,".png"); //mencari file png
        if(str) {
          strcpy(temp,p_old);
          strcat(temp,ent->d_name);
          strcpy(oldname,temp);
          name = strtok(ent->d_name,".");
          strcat(name, add);
          strcpy(temp,p_new);
          strcat(temp,name);
          strcpy(newname,temp);
          printf("%s\n", newname);
          printf("%s\n", oldname);
          rename(oldname,newname);
        }
      }
      closedir (dir); 
    }  

    
  exit(EXIT_SUCCESS);
}

// int main() {

// }