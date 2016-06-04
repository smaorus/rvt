#ifndef __ANSI_C_SYS_SOCKET_H
#define __ANSI_C_SYS_SOCKET_H

#include <stddef.h>
#include <sys/types.h>
#ifdef  __cplusplus
extern "C" {
#endif

/* The following constants should be used for the second parameter of
   `shutdown'.  */
enum
{
  SHUT_RD = 0,          /* No more receptions.  */
#define SHUT_RD         SHUT_RD
  SHUT_WR,              /* No more transmissions.  */
#define SHUT_WR         SHUT_WR
  SHUT_RDWR             /* No more receptions or transmissions.  */
#define SHUT_RDWR       SHUT_RDWR
};

#define AF_INET 2
#define SOCK_STREAM 1

typedef int ssize_t;
typedef int socklen_t;

struct sockaddr
{
  unsigned short int sa_family;
  unsigned char sa_data[14];
};

int socket (int __domain, int __type, int __protocol);
int socketpair (int __domain, int __type, int __protocol,
                       int __fds[2]);
int bind (int __fd, struct sockaddr *__addr, socklen_t __len);
int getsockname (int __fd, struct sockaddr *__addr,
                       socklen_t *__len);
int connect (int __fd, struct sockaddr * __addr, socklen_t __len);
int getpeername (int __fd, struct sockaddr *__addr,
                       socklen_t *__len);
ssize_t send (int __fd, __const void *__buf, size_t __n, int __flags);
ssize_t recv (int __fd, void *__buf, size_t __n, int __flags);
ssize_t sendto (int __fd, __const void *__buf, size_t __n,
                       int __flags, struct sockaddr * __addr,
                       socklen_t __addr_len);
ssize_t recvfrom (int __fd, void * __buf, size_t __n,
                         int __flags, struct sockaddr *__addr,
                         socklen_t *__addr_len);
ssize_t sendmsg (int __fd, __const struct msghdr *__message,
                        int __flags);
ssize_t recvmsg (int __fd, struct msghdr *__message, int __flags);
int getsockopt (int __fd, int __level, int __optname,
                       void *__optval,
                       socklen_t *__optlen);
int listen (int __fd, int __n);
int accept (int __fd, struct sockaddr *__addr,
                   socklen_t *__addr_len);
int shutdown (int __fd, int __how);
int sockatmark (int __fd);
int isfdtype (int __fd, int __fdtype);

#ifdef  __cplusplus
}
#endif

#endif // _SYS_SOCKET_H
