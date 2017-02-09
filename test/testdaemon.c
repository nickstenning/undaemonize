#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  int fd[2];
  int count, err;
  pid_t chpid, chpid2;

  if (pipe(fd)) {
    perror("pipe");
    return EX_OSERR;
  }

  switch (chpid = fork()) {
  case -1:
    perror("fork");
    return EX_OSERR;

  case 0:
    close(fd[0]);

    if(setsid() == -1) {
      write(fd[1], &errno, sizeof(errno));
      _exit(0);
    }

    switch(chpid2 = fork()) {
    case -1:
      write(fd[1], &errno, sizeof(errno));
    case 0:
      chdir("/");

      close(STDIN_FILENO);
      close(STDOUT_FILENO);
      close(STDERR_FILENO);

      close(fd[1]);

      /* Just hang around doing nothing... */
      pause();
    }
    _exit(0);

  default:
    close(fd[1]);

    while ((count = read(fd[0], &err, sizeof(errno))) == -1) {
      if (errno != EAGAIN && errno != EINTR) {
        break;
      }
    }
    close(fd[0]);

    if (count) {
      fprintf(stderr, "process error: %s\n", strerror(err));
      return EX_UNAVAILABLE;
    }

    printf("daemonized successfully\n");
  }

  return 0;
}
