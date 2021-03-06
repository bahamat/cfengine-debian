/* 
   Copyright (C) Cfengine AS

   This file is part of Cfengine 3 - written and maintained by Cfengine AS.
 
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; version 3.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License  
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

  To the extent this program is licensed as part of the Enterprise
  versions of Cfengine, the applicable Commerical Open Source License
  (COSL) may apply to this file if you as a licensee so wish it. See
  included file COSL.txt.

*/
 
/*****************************************************************************/
/*                                                                           */
/* File: sockaddr.c                                                          */
/*                                                                           */
/*****************************************************************************/

#include "cf3.defs.h"
#include "cf3.extern.h"

/*****************************************************************************/
/* TOOLKIT                                                                   */
/* INET independent address/struct conversion routines                       */
/* Note these functions are not thread safe                                  */
/*****************************************************************************/

char *sockaddr_ntop(struct sockaddr *sa)

{ 
#if defined(HAVE_GETADDRINFO)
 static char addrbuf[INET6_ADDRSTRLEN];
 void *addr;
#else
 static char addrbuf[20];
 struct in_addr addr;
#endif

switch (sa->sa_family)
   {
   case AF_INET:
       Debug("IPV4 address\n");
       snprintf(addrbuf,20,"%.19s",inet_ntoa(((struct sockaddr_in *)sa)->sin_addr));
       break;

#ifdef AF_LOCAL
   case AF_LOCAL:
       Debug("Local socket\n") ;
       strcpy(addrbuf, "127.0.0.1") ;
       break;
#endif

#if defined(HAVE_GETADDRINFO)
   case AF_INET6:
       Debug("IPV6 address\n");
       addr = &((struct sockaddr_in6 *)sa)->sin6_addr;
       inet_ntop(sa->sa_family,addr,addrbuf,sizeof(addrbuf));
       break;
#endif
   default:
       Debug("Address family was %d\n",sa->sa_family);
       FatalError("Software failure in sockaddr_ntop\n");
   }

Debug("sockaddr_ntop(%s)\n",addrbuf);
return addrbuf;
}

/*****************************************************************************/

 /* Example:
   
 struct sockaddr_in p;
 struct sockaddr_in6 p6;
 
sockaddr_pton(AF_INET,"128.39.89.10", &p);
sockaddr_pton(AF_INET6,"2001:700:700:3:290:27ff:fea2:477b", &p6);

printf("Coded %s\n",sockaddr_ntop((struct sockaddr *)&p));
 */

/*****************************************************************************/

bool sockaddr_pton(int af,void *src, void *genaddr)
{
switch (af)
   {
   case AF_INET:
      {
      struct sockaddr_in *addr = (struct sockaddr_in *)genaddr;
      memset(addr, 0, sizeof(struct sockaddr_in));
      addr->sin_family = AF_INET;
      addr->sin_addr.s_addr = inet_addr(src);

      Debug("Coded ipv4 %s\n",sockaddr_ntop((struct sockaddr *)genaddr));

      return addr->sin_addr.s_addr != INADDR_NONE;
      }
#if defined(HAVE_GETADDRINFO)
   case AF_INET6:
      {
      int err;
      struct sockaddr_in6 *addr = (struct sockaddr_in6 *)genaddr;
      memset(addr, 0, sizeof(struct sockaddr_in6));
      addr->sin6_family = AF_INET6;
      err = inet_pton(AF_INET6, src, &addr->sin6_addr);

      Debug("Coded ipv6 %s\n",sockaddr_ntop((struct sockaddr *)genaddr));

      return err > 0;
      }
#endif
   default:
      Debug("Address family was %d\n",af);
      FatalError("Software failure in sockaddr_pton\n");
   }
}
