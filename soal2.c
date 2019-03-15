#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

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

	if ((chdir("/home/schielen/")) < 0) {
		exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while(1) {
		struct stat st;
		char folder[20] = "hatiku/elen.ku";
		stat(folder, &st);

		struct passwd *pw = getpwuid(st.st_uid);
		struct group *gr = getgrgid(st.st_gid);
		char nama[10] = "www-data";
		int usr = strcmp(pw->pw_name, nama);
		int grp = strcmp(gr->gr_name, nama);
		if(usr == 0 && grp == 0)
			remove(folder);
		sleep(3);
	}
	exit(EXIT_SUCCESS);
	return 0;
}