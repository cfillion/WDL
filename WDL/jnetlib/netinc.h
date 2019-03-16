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

  namespace JNL
  {
    typedef int socklen_t;
    typedef ::SOCKET SOCKET;

    const SOCKET _INVALID_SOCKET = INVALID_SOCKET;

    const int _EWOULDBLOCK = WSAEWOULDBLOCK;
    const int _EINPROGRESS = WSAEWOULDBLOCK; // not a typo
    const int _ENOTCONN    = WSAENOTCONN;

    const int _SHUT_RDWR = 2; // SD_BOTH

    inline int last_error() { return WSAGetLastError(); }

    inline void set_sock_block(SOCKET socket, const bool block)
    {
      unsigned long __i = block ? 0 : 1;
      ioctlsocket(socket, FIONBIO, &__i);
    }

    inline int closesocket(SOCKET s) { return ::closesocket(s); }

    inline int stricmp(const char *a, const char *b) { return ::stricmp(a, b); }
    inline int strnicmp(const char *a, const char *b, size_t s) { return ::strnicmp(a, b, s); }
  };
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

  namespace JNL
  {
    typedef ::socklen_t socklen_t;
    typedef int SOCKET;

    const SOCKET _INVALID_SOCKET = -1;

    const int _EWOULDBLOCK = EWOULDBLOCK;
    const int _EINPROGRESS = EINPROGRESS;
    const int _ENOTCONN    = ENOTCONN;

    const int _SHUT_RDWR = SHUT_RDWR;

    inline int last_error() { return errno; }

    inline void set_sock_block(SOCKET socket, const bool block)
    {
      int __flags;
      if ((__flags = fcntl(socket, F_GETFL, 0)) != -1)
      {
        if (!block)
          __flags |= O_NONBLOCK;
        else
          __flags &= ~O_NONBLOCK;

        fcntl(socket, F_SETFL, __flags);
      }
    }

    inline int closesocket(SOCKET s) { return ::close(s); }

    inline int stricmp(const char *a, const char *b) { return ::strcasecmp(a, b); }
    inline int strnicmp(const char *a, const char *b, size_t s) { return ::strncasecmp(a, b, s); }
  };
#endif // !_WIN32

#endif //_NETINC_H_
