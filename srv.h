#ifndef __ADIVIX_SRV_H__
#define __ADIVIX_SRV_H__

/* signal.c */
void  srvinitsignals(void);
/* srv.c */
void  srvinitlog(char *srvname);
int   srvinitsock(void);
void  srvloop(int sockfd, void *(*srvfunc)(void *), long procid);
void *srvfunc(void *arg);
/* daemon.c */
int   daemonize(void);
/* util.c */
int   get_open_max(void);

#endif /* __ADIVIX_SRV_H__ */

