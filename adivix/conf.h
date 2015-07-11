#ifndef __ADIVIX_CONF_H__
#define __ADIVIX_CONF_H__

#define NSERVERPROC           8 // number of server processes to launch

#define ADIVIX_SERVER_ROOT    "/usr/local/share/adivix/srv"
#define ADIVIX_SERVER_PORT    "3456"
#define ADIVIX_SERVER_BACKLOG 64

#define USE_SYSCONF           1 // enable POSIX sysconf() interface
#define USE_GETRLIMIT         0
#define SRVNODUMP             1 // exit() instead of dumping core

#endif /* __ADIVIX_CONF_H__ */

