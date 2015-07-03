#include <adivix/conf.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <syslog.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <adivix/srv.h>

void
srvinitlog(char *srvname)
{
    openlog(srvname, LOG_PID, LOG_DAEMON);
    syslog(LOG_NOTICE, "SERVER: %s started by user %d\n", srvname, getuid());

    return;
}

/* initialise server networking; return socket file descriptor */
int
srvinitsock(void)
{
    int              optname = 1;
    int              sockfd;
    int              retval;
    struct addrinfo  addrhint = { 0 };
    struct addrinfo *srvaddrinfo;

    addrhint.ai_family = AF_UNSPEC;
    addrhint.ai_socktype = SOCK_STREAM;
    addrhint.ai_flags = AI_PASSIVE;
    retval = getaddrinfo(NULL, ADIVIX_SERVER_PORT, &addrhint, &srvaddrinfo);
    if (retval) {
        fprintf(stderr, "getaddrinfo() failed: %s\n", gai_strerror(retval));

        return -1;
    }
    sockfd = socket(srvaddrinfo->ai_family,
                    srvaddrinfo->ai_socktype,
                    srvaddrinfo->ai_protocol);
    if (sockfd < 0) {
        fprintf(stderr, "socket() failed\n");

        return -1;
    }
    retval = bind(sockfd, srvaddrinfo->ai_addr, srvaddrinfo->ai_addrlen);
    if (retval < 0) {
        fprintf(stderr, "bind() failed\n");

        return -1;
    }
    freeaddrinfo(srvaddrinfo);
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optname, sizeof(optname))
        < 0) {
        perror("setsockopt");

        return -1;
    }
    if (listen(sockfd, ADIVIX_SERVER_BACKLOG) < 0) {
        perror("listen");

        return -1;
    }

    return sockfd;
}

/* server-specific connection handling */
void *
srvfunc(void *sockfd)
{
    int     fd = *(int *)sockfd;
    ssize_t nread;

    return NULL;                                                          
}

void
srvloop(int sockfd, void *(*srvfunc)(void *))
{
    int                     retval;
    intptr_t                clifd = -1;
    struct sockaddr_storage addrstore;
    socklen_t               addrsize = sizeof(addrstore);

    while (1) {
        pthread_t newthr;

        do {
            clifd = accept(sockfd, (struct sockaddr *)&addrstore, &addrsize);
            if (clifd >= 0) {
                syslog(LOG_NOTICE, "accepted connection on fd %ld\n",
                       (long)clifd);
            } else if (errno == ECONNABORTED) {
                syslog(LOG_NOTICE, "connection aborted\n");
            } else {
                switch (errno) {
#if defined(ENOMEM)
                    case ENOMEM:
                        syslog(LOG_CRIT, "out of memory\n");
                        
                        exit(errno);
#endif
                    case EBADF:
                    case ENOTSOCK:
                        syslog(LOG_CRIT, "invalid socket %d\n", sockfd);
                        
                        exit(errno);
                    case EMFILE:
                    case ENFILE:
                        syslog(LOG_CRIT, "cannot create descriptor\n");
                        
                        break;
                    default:

                        break;
                }
            }
        } while (clifd < 0 && errno == EINTR); /* retry interrupted system calls */
        /* create a new thread to handle the [client] connection */
        retval = pthread_create(&newthr, NULL, srvfunc, (void *)clifd);
        if (retval) {
            syslog(LOG_CRIT, "failed to create server thread\n");
        } else {
            syslog(LOG_NOTICE, "started server thread %ld\n", (long)newthr);
        }
        /* do not wait for thread cancellation explicitly */
        pthread_detach(newthr);
    }

    /* NOTREACHED */
    return;
}

