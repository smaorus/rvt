#ifndef __ANSI_C_NETINET_IN_H
#define __ANSI_C_NETINET_IN_H

#include <features.h>
#include <sys/socket.h>

#ifdef  __cplusplus
extern "C" {
#endif

enum
  {
    IPPROTO_IP = 0,        /* Dummy protocol for TCP.  */
#define IPPROTO_IP              IPPROTO_IP
    IPPROTO_HOPOPTS = 0,   /* IPv6 Hop-by-Hop options.  */
#define IPPROTO_HOPOPTS         IPPROTO_HOPOPTS
    IPPROTO_ICMP = 1,      /* Internet Control Message Protocol.  */
#define IPPROTO_ICMP            IPPROTO_ICMP
    IPPROTO_IGMP = 2,      /* Internet Group Management Protocol. */
#define IPPROTO_IGMP            IPPROTO_IGMP
    IPPROTO_IPIP = 4,      /* IPIP tunnels (older KA9Q tunnels use 94).  */
#define IPPROTO_IPIP            IPPROTO_IPIP
    IPPROTO_TCP = 6,       /* Transmission Control Protocol.  */
#define IPPROTO_TCP             IPPROTO_TCP
    IPPROTO_EGP = 8,       /* Exterior Gateway Protocol.  */
#define IPPROTO_EGP             IPPROTO_EGP
    IPPROTO_PUP = 12,      /* PUP protocol.  */
#define IPPROTO_PUP             IPPROTO_PUP
    IPPROTO_UDP = 17,      /* User Datagram Protocol.  */
#define IPPROTO_UDP             IPPROTO_UDP
    IPPROTO_IDP = 22,      /* XNS IDP protocol.  */
#define IPPROTO_IDP             IPPROTO_IDP
    IPPROTO_TP = 29,       /* SO Transport Protocol Class 4.  */
#define IPPROTO_TP              IPPROTO_TP
    IPPROTO_IPV6 = 41,     /* IPv6 header.  */
#define IPPROTO_IPV6            IPPROTO_IPV6
    IPPROTO_ROUTING = 43,  /* IPv6 routing header.  */
#define IPPROTO_ROUTING         IPPROTO_ROUTING
    IPPROTO_FRAGMENT = 44, /* IPv6 fragmentation header.  */
#define IPPROTO_FRAGMENT        IPPROTO_FRAGMENT
    IPPROTO_RSVP = 46,     /* Reservation Protocol.  */
#define IPPROTO_RSVP            IPPROTO_RSVP
    IPPROTO_GRE = 47,      /* General Routing Encapsulation.  */
#define IPPROTO_GRE             IPPROTO_GRE
    IPPROTO_ESP = 50,      /* encapsulating security payload.  */
#define IPPROTO_ESP             IPPROTO_ESP
    IPPROTO_AH = 51,       /* authentication header.  */
#define IPPROTO_AH              IPPROTO_AH
    IPPROTO_ICMPV6 = 58,   /* ICMPv6.  */
#define IPPROTO_ICMPV6          IPPROTO_ICMPV6
    IPPROTO_NONE = 59,     /* IPv6 no next header.  */
#define IPPROTO_NONE            IPPROTO_NONE
#define IPPROTO_NONE            IPPROTO_NONE
    IPPROTO_DSTOPTS = 60,  /* IPv6 destination options.  */
#define IPPROTO_DSTOPTS         IPPROTO_DSTOPTS
    IPPROTO_MTP = 92,      /* Multicast Transport Protocol.  */
#define IPPROTO_MTP             IPPROTO_MTP
    IPPROTO_ENCAP = 98,    /* Encapsulation Header.  */
#define IPPROTO_ENCAP           IPPROTO_ENCAP
    IPPROTO_PIM = 103,     /* Protocol Independent Multicast.  */
#define IPPROTO_PIM             IPPROTO_PIM
    IPPROTO_COMP = 108,    /* Compression Header Protocol.  */
#define IPPROTO_COMP            IPPROTO_COMP
    IPPROTO_SCTP = 132,    /* Stream Control Transmission Protocol.  */
#define IPPROTO_SCTP            IPPROTO_SCTP
    IPPROTO_RAW = 255,     /* Raw IP packets.  */
#define IPPROTO_RAW             IPPROTO_RAW
    IPPROTO_MAX
  };

/* Type to represent a port.  */
typedef ushort in_port_t;

/* Standard well-known ports.  */
enum
  {
    IPPORT_ECHO = 7,            /* Echo service.  */
    IPPORT_DISCARD = 9,         /* Discard transmissions service.  */
    IPPORT_SYSTAT = 11,         /* System status service.  */
    IPPORT_DAYTIME = 13,        /* Time of day service.  */
    IPPORT_NETSTAT = 15,        /* Network status service.  */
    IPPORT_FTP = 21,            /* File Transfer Protocol.  */
    IPPORT_TELNET = 23,         /* Telnet protocol.  */
    IPPORT_SMTP = 25,           /* Simple Mail Transfer Protocol.  */
    IPPORT_TIMESERVER = 37,     /* Timeserver service.  */
    IPPORT_NAMESERVER = 42,     /* Domain Name Service.  */
    IPPORT_WHOIS = 43,          /* Internet Whois service.  */
    IPPORT_MTP = 57,

    IPPORT_TFTP = 69,           /* Trivial File Transfer Protocol.  */
    IPPORT_RJE = 77,
    IPPORT_FINGER = 79,         /* Finger service.  */
    IPPORT_TTYLINK = 87,
    IPPORT_SUPDUP = 95,         /* SUPDUP protocol.  */

    IPPORT_EXECSERVER = 512,    /* execd service.  */
    IPPORT_LOGINSERVER = 513,   /* rlogind service.  */
    IPPORT_CMDSERVER = 514,
    IPPORT_EFSSERVER = 520,

    /* UDP ports.  */
    IPPORT_BIFFUDP = 512,
    IPPORT_WHOSERVER = 513,
    IPPORT_ROUTESERVER = 520,

    /* Ports less than this value are reserved for privileged processes.  */
    IPPORT_RESERVED = 1024,

    /* Ports greater this value are reserved for (non-privileged) servers.  */
    IPPORT_USERRESERVED = 5000
  };

/* Internet address.  */
typedef uint in_addr_t;
struct in_addr
  {
    in_addr_t s_addr;
  };

/* Definitions of the bits in an Internet address integer.

   On subnets, host and network parts are found according to
   the subnet mask, not these masks.  */

#define IN_CLASSA(a)            ((((in_addr_t)(a)) & 0x80000000) == 0)
#define IN_CLASSA_NET           0xff000000
#define IN_CLASSA_NSHIFT        24
#define IN_CLASSA_HOST          (0xffffffff & ~IN_CLASSA_NET)
#define IN_CLASSA_MAX           128

#define IN_CLASSB(a)            ((((in_addr_t)(a)) & 0xc0000000) == 0x80000000)
#define IN_CLASSB_NET           0xffff0000
#define IN_CLASSB_NSHIFT        16
#define IN_CLASSB_HOST          (0xffffffff & ~IN_CLASSB_NET)
#define IN_CLASSB_MAX           65536
#define IN_CLASSC(a)            ((((in_addr_t)(a)) & 0xe0000000) == 0xc0000000)
#define IN_CLASSC_NET           0xffffff00
#define IN_CLASSC_NSHIFT        8
#define IN_CLASSC_HOST          (0xffffffff & ~IN_CLASSC_NET)

#define IN_CLASSD(a)            ((((in_addr_t)(a)) & 0xf0000000) == 0xe0000000)
#define IN_MULTICAST(a)         IN_CLASSD(a)

#define IN_EXPERIMENTAL(a)      ((((in_addr_t)(a)) & 0xe0000000) == 0xe0000000)
#define IN_BADCLASS(a)          ((((in_addr_t)(a)) & 0xf0000000) == 0xf0000000)

/* Address to accept any incoming messages.  */
#define INADDR_ANY              ((in_addr_t) 0x00000000)
/* Address to send to all hosts.  */
#define INADDR_BROADCAST        ((in_addr_t) 0xffffffff)
/* Address indicating an error return.  */
#define INADDR_NONE             ((in_addr_t) 0xffffffff)

/* Network number for local host loopback.  */
#define IN_LOOPBACKNET          127
/* Address to loopback in software to local host.  */
#ifndef INADDR_LOOPBACK
#define INADDR_LOOPBACK        ((in_addr_t) 0x7f000001) /* Inet 127.0.0.1.  */
#endif

/* Defines for Multicast INADDR.  */
#define INADDR_UNSPEC_GROUP     ((in_addr_t) 0xe0000000) /* 224.0.0.0 */
#define INADDR_ALLHOSTS_GROUP   ((in_addr_t) 0xe0000001) /* 224.0.0.1 */
#define INADDR_ALLRTRS_GROUP    ((in_addr_t) 0xe0000002) /* 224.0.0.2 */
#define INADDR_MAX_LOCAL_GROUP  ((in_addr_t) 0xe00000ff) /* 224.0.0.255 */

#define INET_ADDRSTRLEN 16

struct sockaddr_in
{
  int sin_family;
  in_port_t sin_port;                 /* Port number.  */
  struct in_addr sin_addr;            /* Internet address.  */
}; 

uint ntohl(uint __netlong);
uint ntohs(uint __netshort);
uint htonl(uint __hostlong);
uint htons(uint __hostshort);

#ifdef  __cplusplus
}
#endif

#endif /* netinet/in.h */
