#include "conf.h"
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#if (USE_THPOOL)
#include <C-Thread-Pool/thpool.h>
#endif

extern threadpool    srvthpooltab[];
extern volatile long nsrvproc;

#if (USE_THPOOL)
void
sigdelthpool(void)
{
    long ndx;

    for (ndx = 0 ; ndx < NSERVERPROC ; ndx++) {
        thpool_destroy(srvthpooltab[ndx]);
    }

    return;
}
#endif

void
sigreap(int sig)
{
    int waitret;

    nsrvproc--;
    wait(&waitret);

    return;
}

void
sigcrash(int sig)
{
#if (SRVNODUMP)
    exit(sig);
#else
    abort();
#endif
}

void
sigdie(int sig)
{
#if (USE_THPOOL)
    sigdelthpool();
#endif
    exit(sig);
}

void
srvinitsignals(void)
{
    signal(SIGCHLD, sigreap);
    signal(SIGSEGV, sigcrash);
    signal(SIGILL, sigcrash);
    signal(SIGABRT, sigcrash);
    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, sigdie);
    signal(SIGQUIT, sigdie);
#if defined(SIGTSTP)
    /* ignore job-control signals */
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
#endif

    return;
}

