#include <adivix/conf.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

extern volatile long nsrvproc;

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

