#include "conf.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <syslog.h>
#include <unistd.h>
#include "srv.h"
#if (USE_THPOOL)
#include <C-Thread-Pool/thpool.h>
#endif

extern threadpool srvthpool;

static pid_t  srvpids[NSERVERPROC];
volatile long nsrvproc = 0;

int
main(int argc, char *argv[])
{
    int   sockfd;
    pid_t pid;
    long  ndx;

    srvinitsignals();
    sockfd = srvinitsock();
    if (sockfd < 0) {
        fprintf(stderr, "srvinit() failed\n");

        exit(1);
    }
    daemonize();
    srvinitlog(argv[0]);
    for (ndx = 0 ; ndx < NSERVERPROC ; ndx++) {
        pid = fork();
        if (pid < 0) {
            syslog(LOG_CRIT, "cannot fork()\n");

            if (!nsrvproc) {
                exit(errno);
            }
        } else if (pid) {
            /* parent process */
            srvpids[nsrvproc] = pid;
            nsrvproc++;
        } else {
            srvloop(sockfd, srvfunc, ndx);
        }
    }
    do {
        const sigset_t sigmask = { { 0 } };

        sigsuspend(&sigmask);
    } while (nsrvproc);

    /* NOTREACHED */
    exit(0);
}

