#ifndef __ANSI_C_NETDB_H
#define __ANSI_C_NETDB_H

#include <sys/socket.h>

#ifdef  __cplusplus
extern "C" {
#endif

struct hostent
{
  char *h_name;                 /* Official name of host.  */
  char **h_aliases;             /* Alias list.  */
  int h_addrtype;               /* Host address type.  */
  int h_length;                 /* Length of address.  */
  char **h_addr_list;           /* List of addresses from name server.  */
#define h_addr  h_addr_list[0]  /* Address, for backward compatibility.  */
};

struct hostent *gethostent(void);
struct hostent *gethostbyaddr(const void *__addr, socklen_t __len, int __type);
struct hostent *gethostbyname(const char *__name);

#ifdef  __cplusplus
}
#endif

#endif /* netdb.h */
