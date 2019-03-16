/*
** JNetLib
** Copyright (C) 2000-2001 Nullsoft, Inc.
** Author: Justin Frankel
** File: netinc.h - network includes and portability defines (used internally)
** License: see jnetlib.h
*/

#ifndef _JNL_NETINC_H_
#define _JNL_NETINC_H_

#ifdef _WIN32
  #include <windows.h>
  #include <stdio.h>
  #include <time.h>

  typedef SOCKET JNL_SOCKET;
  typedef int socklen_t;

  #define JNL_ERRNO (WSAGetLastError())

  #define JNL_INVALID_SOCKET INVALID_SOCKET

  #define JNL_EWOULDBLOCK WSAEWOULDBLOCK
  #define JNL_EINPROGRESS WSAEWOULDBLOCK // not a typo
  #define JNL_ENOTCONN    WSAENOTCONN

  #define JNL_SHUT_RDWR 2 // SD_BOTH

  #define jnl_set_sock_block(s,block) { unsigned long __i=block?0:1; ioctlsocket(s,FIONBIO,&__i); }

  #define jnl_closesocket(s) ::closesocket(s)

  #define jnl_stricmp(a,b) ::stricmp(a,b)
  #define jnl_strnicmp(a,b,s) ::strnicmp(a,b,s)
#else
  #ifndef THREAD_SAFE
    #define THREAD_SAFE
  #endif

  #ifndef _REENTRANT
    #define _REENTRANT
  #endif

  #include <pthread.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <sys/time.h>
  #include <arpa/inet.h>
  #include <netdb.h>
  #include <stdarg.h>
  #include <stdio.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <signal.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <string.h>

  typedef int JNL_SOCKET;

  #define JNL_ERRNO errno

  #define JNL_INVALID_SOCKET (-1)

  #define JNL_EWOULDBLOCK EWOULDBLOCK
  #define JNL_EINPROGRESS EINPROGRESS
  #define JNL_ENOTCONN    ENOTCONN

  #define JNL_SHUT_RDWR SHUT_RDWR

  #define jnl_set_sock_block(s,block) { int __flags; if ((__flags = fcntl(s, F_GETFL, 0)) != -1) { if (!block) __flags |= O_NONBLOCK; else __flags &= ~O_NONBLOCK; fcntl(s, F_SETFL, __flags);  } }

  #define jnl_closesocket(s) ::close(s)

  #define jnl_stricmp(a,b) ::strcasecmp(a,b)
  #define jnl_strnicmp(a,b,s) ::strncasecmp(a,b,s)
#endif // !_WIN32

#endif //_NETINC_H_
