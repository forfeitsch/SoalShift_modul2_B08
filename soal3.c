#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

//#define die(e) do ( fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); while(0);))

int main() {
  pid_t child_id;

  child_id = fork();
  
  int pipes[4];
  pipe(pipes); // sets up 1st pipe
  pipe(pipes + 2); // sets up 2nd pipe

  int status;
  int status2;
  // if(pipe(link)==-1) {
  //     die(pipe);
  // }

  if (child_id < 0) {
    exit(EXIT_FAILURE);
  }

  if (child_id == 0) {
    // this is child
    
    char *argv[] = {"unzip", "/home/schielen/modul2/campur2.zip", NULL};
    execv("/usr/bin/unzip", argv);
  } else {
    // this is parent
    while ((wait(&status)) > 0);
    child_id = fork();
    if (child_id < 0) {
    exit(EXIT_FAILURE);
  }
    if (child_id == 0) {
    // this is child
    
    char *argv[] = {"ls", "/home/schielen/modul2/campur2", NULL};
    dup2(pipes[1],1);
    close(pipes[0]);
    close(pipes[2]);
    close(pipes[3]);


    execv("/bin/ls", argv);


    } else
        {
          pid_t child_id2;
          child_id2 = fork();
            if (child_id2 == 0) {
        // this is child
        while ((wait(&status2)) > 0);
        char *argv[] = {"grep", ".txt$", NULL};
        dup2(pipes[0],0);
        close(pipes[1]);
        close(pipes[2]);
        dup2(pipes[3],1);
        execv("/bin/grep", argv);

        }
        else
        {
          
          FILE *file = fopen("/home/schielen/modul2/daftar.txt", "w+");
          close(pipes[0]);
          close(pipes[1]);
          close(pipes[3]);
          char str[10000];
          read(pipes[2],str,sizeof(str));
          fputs(str,file);
          // printf("%s\n",str);
        }
        
    }
    
  }
}