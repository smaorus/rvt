#ifndef __ANSI_C_ARPA_INET_H
#define __ANSI_C_ARPA_INET_H

#include <features.h>
#include <netinet/in.h>         /* To define `struct in_addr'.  */

#ifdef  __cplusplus
extern "C" {
#endif

in_addr_t inet_lnaof(struct in_addr __in);
struct in_addr inet_makeaddr(in_addr_t __net, in_addr_t __host);
in_addr_t inet_netof(struct in_addr __in);
in_addr_t inet_network(const char *__cp);

#ifdef  __cplusplus
}
#endif

#endif /* arpa/inet.h */
