#include "SocketInterface.h"
#ifdef __LINUX__
//extern X_INT errno;
#endif
X_CHAR g_socketError[SOCKET_ERROR_SIZE];
X_INT  g_socketErrorCode = -1;

//
X_SOCKET SocketInterface::socket_create(X_INT domain, X_INT type, X_INT protocol)
{
	__BASE_ENTER_FUNCTION

	X_SOCKET s = ::socket(domain,type,protocol);
	if ( s == INVALID_SOCKET ) 
	{
#ifdef __LINUX__
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EACCES : 
			strncpy( g_socketError, "EACCES", SOCKET_ERROR_SIZE ) ;
			break;
		case EAFNOSUPPORT :
			strncpy( g_socketError, "EAFNOSUPPORT", SOCKET_ERROR_SIZE ) ;
			break;
		case EINVAL :
			strncpy( g_socketError, "EINVAL", SOCKET_ERROR_SIZE ) ;
			break;
		case EMFILE : 
			strncpy( g_socketError, "EMFILE", SOCKET_ERROR_SIZE ) ;
			break;
		case ENFILE : 
			strncpy( g_socketError, "ENFILE", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOBUFS : 
			strncpy( g_socketError, "ENOBUFS", SOCKET_ERROR_SIZE ) ;
			break;
		case EPROTONOSUPPORT :
			strncpy( g_socketError, "EPROTONOSUPPORT", SOCKET_ERROR_SIZE ) ;
			break;
		default : 
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break;
			}
		}//end of switch
#elif __WINDOWS__
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEAFNOSUPPORT : 
			strncpy( g_socketError, "WSAEAFNOSUPPORT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEMFILE : 
			strncpy( g_socketError, "WSAEMFILE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( g_socketError, "WSAENOBUFS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEPROTONOSUPPORT : 
			strncpy( g_socketError, "WSAEPROTONOSUPPORT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEPROTOTYPE : 
			strncpy( g_socketError, "WSAEPROTOTYPE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAESOCKTNOSUPPORT : 
			strncpy( g_socketError, "WSAESOCKTNOSUPPORT", SOCKET_ERROR_SIZE ) ;
			break ;
		default : 
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
#endif
	}

	return s;
	
	__BASE_LEAVE_FUNCTION

	return INVALID_SOCKET ;
}

X_BOOL SocketInterface::socket_bind ( X_SOCKET s , const struct sockaddr * addr , X_INT addrlen ) 
{
	__BASE_ENTER_FUNCTION

	if ( bind ( s , addr , addrlen ) == SOCKET_ERROR ) 
	{
#ifdef __LINUX__
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EADDRINUSE :
			strncpy( g_socketError, "EADDRINUSE", SOCKET_ERROR_SIZE ) ;
			break;
		case EINVAL : 
			strncpy( g_socketError, "EINVAL", SOCKET_ERROR_SIZE ) ;
			break;
		case EACCES : 
			strncpy( g_socketError, "EACCES", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTSOCK : 
			strncpy( g_socketError, "ENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break;
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break;
		case EROFS : 
			strncpy( g_socketError, "EROFS", SOCKET_ERROR_SIZE ) ;
			break;
		case EFAULT : 
			strncpy( g_socketError, "EFAULT", SOCKET_ERROR_SIZE ) ;
			break;
		case ENAMETOOLONG : 
			strncpy( g_socketError, "ENAMETOOLONG", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOENT : 
			strncpy( g_socketError, "ENOENT", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOMEM : 
			strncpy( g_socketError, "ENOMEM", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTDIR : 
			strncpy( g_socketError, "ENOTDIR", SOCKET_ERROR_SIZE ) ;
			break;
		case ELOOP : 
			strncpy( g_socketError, "ELOOP", SOCKET_ERROR_SIZE ) ;
			break;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break;
			}
		}//end of switch
#elif __WINDOWS__
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSAESOCKTNOSUPPORT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEADDRINUSE : 
			strncpy( g_socketError, "WSAEADDRINUSE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEADDRNOTAVAIL : 
			strncpy( g_socketError, "WSAEADDRNOTAVAIL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( g_socketError, "WSAEFAULT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEAFNOSUPPORT : 
			strncpy( g_socketError, "WSAEAFNOSUPPORT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( g_socketError, "WSAEINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( g_socketError, "WSAENOBUFS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
#endif

		return X_FALSE ;
	}
	
	return X_TRUE ;

	__BASE_LEAVE_FUNCTION

	return X_FALSE ;
}

//建立连接
X_BOOL SocketInterface::socket_connect(X_SOCKET s , const struct sockaddr * addr , X_INT addrlen)
{
	__BASE_ENTER_FUNCTION

	if ( connect(s,addr,addrlen) == SOCKET_ERROR ) 
	{
#ifdef __LINUX__
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EALREADY : 
			strncpy( g_socketError, "EALREADY", SOCKET_ERROR_SIZE ) ;
			break;
		case EINPROGRESS : 
			strncpy( g_socketError, "EINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break;
		case ECONNREFUSED :
			strncpy( g_socketError, "ECONNREFUSED", SOCKET_ERROR_SIZE ) ;
			break;
		case EISCONN : 
			strncpy( g_socketError, "EISCONN", SOCKET_ERROR_SIZE ) ;
			break;
		case ETIMEDOUT : 
			strncpy( g_socketError, "ETIMEDOUT", SOCKET_ERROR_SIZE ) ;
			break;
		case ENETUNREACH : 
			strncpy( g_socketError, "ENETUNREACH", SOCKET_ERROR_SIZE ) ;
			break;
		case EADDRINUSE : 
			strncpy( g_socketError, "EADDRINUSE", SOCKET_ERROR_SIZE ) ;
			break;
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break;
		case EFAULT : 
			strncpy( g_socketError, "EFAULT", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTSOCK :
			strncpy( g_socketError, "ENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break;
			}
		}//end of switch
#elif __WINDOWS__
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEADDRINUSE : 
			strncpy( g_socketError, "WSAEADDRINUSE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( g_socketError, "WSAEINTR", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEADDRNOTAVAIL : 
			strncpy( g_socketError, "WSAEADDRNOTAVAIL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEAFNOSUPPORT : 
			strncpy( g_socketError, "WSAEAFNOSUPPORT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAECONNREFUSED : 
			strncpy( g_socketError, "WSAECONNREFUSED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEALREADY : 
			strncpy( g_socketError, "WSAEALREADY", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( g_socketError, "WSAEFAULT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( g_socketError, "WSAEINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEISCONN : 
			strncpy( g_socketError, "WSAEISCONN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEMFILE : 
			strncpy( g_socketError, "WSAEMFILE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETUNREACH : 
			strncpy( g_socketError, "WSAENETUNREACH", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( g_socketError, "WSAENOBUFS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAETIMEDOUT : 
			strncpy( g_socketError, "WSAETIMEDOUT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEWOULDBLOCK  : 
			strncpy( g_socketError, "WSAEWOULDBLOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
#endif
		return X_FALSE ;
	}
	return X_TRUE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//监听
X_BOOL SocketInterface::socket_listen(X_SOCKET s, X_INT backlog)
{
	__BASE_ENTER_FUNCTION

	if ( listen( s , backlog ) == SOCKET_ERROR ) 
	{
#ifdef __LINUX__
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTSOCK :
			strncpy( g_socketError, "ENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break;
		case EOPNOTSUPP :
			strncpy( g_socketError, "EOPNOTSUPP", SOCKET_ERROR_SIZE ) ;
			break;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break;
			}
		}//end of switch
#elif __WINDOWS__
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEADDRINUSE : 
			strncpy( g_socketError, "WSAEADDRINUSE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( g_socketError, "WSAEINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEISCONN : 
			strncpy( g_socketError, "WSAEISCONN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEMFILE : 
			strncpy( g_socketError, "WSAEMFILE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( g_socketError, "WSAENOBUFS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( g_socketError, "WSAEOPNOTSUPP", SOCKET_ERROR_SIZE ) ;
			break ;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
#endif
		return X_FALSE ;
	}

	return X_TRUE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//接受连接
X_SOCKET SocketInterface::socket_accept(X_SOCKET s, struct sockaddr* addr, X_INT* addrlen)
{
	__BASE_ENTER_FUNCTION
#ifdef __LINUX__
	X_SOCKET client = accept( s , addr , (socklen_t*)addrlen );
#elif __WINDOWS__
	X_SOCKET client = accept( s , addr , addrlen );
#endif
	if ( client == INVALID_SOCKET ) 
	{
#ifdef __LINUX__
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EWOULDBLOCK : 
			strncpy( g_socketError, "EWOULDBLOCK", SOCKET_ERROR_SIZE ) ;
			break;
		case ECONNRESET :
			strncpy( g_socketError, "ECONNRESET", SOCKET_ERROR_SIZE ) ;
			break;
		case ECONNABORTED :
			strncpy( g_socketError, "ECONNABORTED", SOCKET_ERROR_SIZE ) ;
			break;
		case EPROTO :
			strncpy( g_socketError, "EPROTO", SOCKET_ERROR_SIZE ) ;
			break;
		case EINTR :
			strncpy( g_socketError, "EINTR", SOCKET_ERROR_SIZE ) ;
			break;
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTSOCK : 
			strncpy( g_socketError, "ENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break;
		case EOPNOTSUPP : 
			strncpy( g_socketError, "EOPNOTSUPP", SOCKET_ERROR_SIZE ) ;
			break;
		case EFAULT : 
			strncpy( g_socketError, "EFAULT", SOCKET_ERROR_SIZE ) ;
			break;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break;
			}
		}//end of switch
#elif __WINDOWS__
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( g_socketError, "WSAEFAULT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( g_socketError, "WSAEINTR", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( g_socketError, "WSAEINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEMFILE : 
			strncpy( g_socketError, "WSAEMFILE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( g_socketError, "WSAENOBUFS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( g_socketError, "WSAEOPNOTSUPP", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			strncpy( g_socketError, "WSAEWOULDBLOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAECONNRESET : 
			strncpy( g_socketError, "WSAECONNRESET", SOCKET_ERROR_SIZE ) ;
			break ;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
#endif
		return INVALID_SOCKET ;
	}
	return client;

	__BASE_LEAVE_FUNCTION

		return INVALID_SOCKET ;
}

//发送数据
X_INT SocketInterface::socket_send(X_SOCKET s, const X_VOID* buf, X_INT length, X_INT flags)
{
	__BASE_ENTER_FUNCTION

	X_INT nSent =send(s,(const X_CHAR *)buf, length, flags);
	if ( nSent == SOCKET_ERROR ) 
	{
#ifdef __LINUX__
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EWOULDBLOCK : 
			return SOCKET_ERROR_WOULD_BLOCK;
		case ECONNRESET :
			strncpy( g_socketError, "ECONNRESET", SOCKET_ERROR_SIZE ) ;
			break;
		case EPIPE :
			strncpy( g_socketError, "EPIPE", SOCKET_ERROR_SIZE ) ;
			break;
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTSOCK : 
			strncpy( g_socketError, "ENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break;
		case EFAULT : 
			strncpy( g_socketError, "EFAULT", SOCKET_ERROR_SIZE ) ;
			break;
		case EMSGSIZE : 
			strncpy( g_socketError, "EMSGSIZE", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOBUFS : 
			strncpy( g_socketError, "ENOBUFS", SOCKET_ERROR_SIZE ) ;
			break;
		default : 
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			}
		}//end of switch
#elif __WINDOWS__
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEACCES : 
			strncpy( g_socketError, "WSAEACCES", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( g_socketError, "WSAEINTR", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( g_socketError, "WSAEFAULT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETRESET : 
			strncpy( g_socketError, "WSAENETRESET", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( g_socketError, "WSAENOBUFS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTCONN : 
			strncpy( g_socketError, "WSAENOTCONN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( g_socketError, "WSAEOPNOTSUPP", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAESHUTDOWN : 
			strncpy( g_socketError, "WSAESHUTDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			return SOCKET_ERROR_WOULD_BLOCK ;
			break ;
		case WSAEMSGSIZE : 
			strncpy( g_socketError, "WSAEMSGSIZE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( g_socketError, "WSAEINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAECONNABORTED : 
			strncpy( g_socketError, "WSAECONNABORTED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAECONNRESET : 
			strncpy( g_socketError, "WSAECONNRESET", SOCKET_ERROR_SIZE ) ;
			break ;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
#endif
	} 

	return nSent;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

X_INT SocketInterface::socket_sendto(X_SOCKET s, const X_VOID* buf, X_INT length, X_INT flags, const struct sockaddr* to, X_INT tolen)
{
	__BASE_ENTER_FUNCTION

	X_INT nSent = sendto(s,(const X_CHAR *)buf,length,flags,to,tolen);
	if ( nSent == SOCKET_ERROR ) 
	{
#ifdef __LINUX__
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EWOULDBLOCK : 
			return SOCKET_ERROR_WOULD_BLOCK;
		case ECONNRESET :
			strncpy( g_socketError, "ECONNRESET", SOCKET_ERROR_SIZE ) ;
			break;
		case EPIPE :
			strncpy( g_socketError, "EPIPE", SOCKET_ERROR_SIZE ) ;
			break;
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTSOCK : 
			strncpy( g_socketError, "ENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break;
		case EFAULT : 
			strncpy( g_socketError, "EFAULT", SOCKET_ERROR_SIZE ) ;
			break;
		case EMSGSIZE : 
			strncpy( g_socketError, "EMSGSIZE", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOBUFS : 
			strncpy( g_socketError, "ENOBUFS", SOCKET_ERROR_SIZE ) ;
			break;
		default : 
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			}
		}//end of switch
#elif __WINDOWS__
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEACCES : 
			strncpy( g_socketError, "WSAEACCES", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( g_socketError, "WSAEINTR", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( g_socketError, "WSAEFAULT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETRESET : 
			strncpy( g_socketError, "WSAENETRESET", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOBUFS : 
			strncpy( g_socketError, "WSAENOBUFS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTCONN : 
			strncpy( g_socketError, "WSAENOTCONN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( g_socketError, "WSAEOPNOTSUPP", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAESHUTDOWN : 
			strncpy( g_socketError, "WSAESHUTDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			return SOCKET_ERROR_WOULD_BLOCK ;
			break ;
		case WSAEMSGSIZE : 
			strncpy( g_socketError, "WSAEMSGSIZE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAECONNABORTED : 
			strncpy( g_socketError, "WSAECONNABORTED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAECONNRESET : 
			strncpy( g_socketError, "WSAECONNRESET", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEADDRNOTAVAIL : 
			strncpy( g_socketError, "WSAEADDRNOTAVAIL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEAFNOSUPPORT : 
			strncpy( g_socketError, "WSAEAFNOSUPPORT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( g_socketError, "WSAEINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETUNREACH : 
			strncpy( g_socketError, "WSAENETUNREACH", SOCKET_ERROR_SIZE ) ;
			break ;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
#endif
	}

	return nSent;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

//接收数据
X_INT SocketInterface::socket_recv(X_SOCKET s, X_VOID* buf, X_INT length, X_INT flags)
{
	__BASE_ENTER_FUNCTION

	X_INT nrecv = recv(s,(X_CHAR*)buf, length, flags);
	if ( nrecv == SOCKET_ERROR ) 
	{
#ifdef __LINUX__
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EWOULDBLOCK : 
			return SOCKET_ERROR_WOULD_BLOCK;
		case ECONNRESET :
			strncpy( g_socketError, "ECONNRESET", SOCKET_ERROR_SIZE ) ;
			break;
		case EPIPE :
			strncpy( g_socketError, "EPIPE", SOCKET_ERROR_SIZE ) ;
			break;
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTCONN : 
			strncpy( g_socketError, "ENOTCONN", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTSOCK : 
			strncpy( g_socketError, "ENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break;
		case EINTR : 
			strncpy( g_socketError, "EINTR", SOCKET_ERROR_SIZE ) ;
			break;
		case EFAULT : 
			strncpy( g_socketError, "EFAULT", SOCKET_ERROR_SIZE ) ;
			break;
		default : 
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			}
		}//end of switch

#elif __WINDOWS__
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTCONN : 
			strncpy( g_socketError, "WSAENOTCONN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( g_socketError, "WSAEINTR", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( g_socketError, "WSAEOPNOTSUPP", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAESHUTDOWN : 
			strncpy( g_socketError, "WSAESHUTDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			return SOCKET_ERROR_WOULD_BLOCK ;
			break ;
		case WSAEMSGSIZE : 
			strncpy( g_socketError, "WSAEMSGSIZE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( g_socketError, "WSAEINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAECONNABORTED : 
			strncpy( g_socketError, "WSAECONNABORTED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAECONNRESET : 
			strncpy( g_socketError, "WSAECONNRESET", SOCKET_ERROR_SIZE ) ;
			break ;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
#endif
	} 

	return nrecv;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

X_INT SocketInterface::socket_recvfrom(X_SOCKET s, X_VOID* buf, X_INT length, X_INT flags, struct sockaddr* from, X_INT* fromlen)
{
	__BASE_ENTER_FUNCTION
#ifdef __LINUX__
	X_INT nReceived = recvfrom(s,(X_CHAR*)buf,length,flags,from,(socklen_t*)fromlen);
#elif __WINDOWS__
	X_INT nReceived = recvfrom(s,(X_CHAR*)buf,length,flags,from,fromlen);
#endif
	if ( nReceived == SOCKET_ERROR ) 
	{
#ifdef __LINUX__
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EWOULDBLOCK : 
			return SOCKET_ERROR_WOULD_BLOCK;
		case ECONNRESET :
			strncpy( g_socketError, "ECONNRESET", SOCKET_ERROR_SIZE ) ;
			break;
		case EPIPE :
			strncpy( g_socketError, "EPIPE", SOCKET_ERROR_SIZE ) ;
			break;
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTCONN : 
			strncpy( g_socketError, "ENOTCONN", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTSOCK : 
			strncpy( g_socketError, "ENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break;
		case EINTR : 
			strncpy( g_socketError, "EINTR", SOCKET_ERROR_SIZE ) ;
			break;
		case EFAULT : 
			strncpy( g_socketError, "EFAULT", SOCKET_ERROR_SIZE ) ;
			break;
		default : 
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			}
		}//end of switch

#elif __WINDOWS__
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( g_socketError, "WSAEFAULT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( g_socketError, "WSAEINTR", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( g_socketError, "WSAEINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTCONN : 
			strncpy( g_socketError, "WSAENOTCONN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEOPNOTSUPP : 
			strncpy( g_socketError, "WSAEOPNOTSUPP", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAESHUTDOWN : 
			strncpy( g_socketError, "WSAESHUTDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			return SOCKET_ERROR_WOULD_BLOCK ;
			break ;
		case WSAEMSGSIZE : 
			strncpy( g_socketError, "WSAEMSGSIZE", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAECONNABORTED : 
			strncpy( g_socketError, "WSAECONNABORTED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAECONNRESET : 
			strncpy( g_socketError, "WSAECONNRESET", SOCKET_ERROR_SIZE ) ;
			break ;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
#endif
	}

	return nReceived;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

//关闭套接字
X_BOOL SocketInterface::socket_close(X_SOCKET s)
{
	__BASE_ENTER_FUNCTION

#ifdef __LINUX__
	if ( close(s) < 0 ) 
	{
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break;
		default :
			{
				break;
			}
		}
		return X_FALSE ;
	}
#elif __WINDOWS__
	if ( closesocket(s) == SOCKET_ERROR ) 
	{
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINTR : 
			strncpy( g_socketError, "WSAEINTR", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEWOULDBLOCK : 
			strncpy( g_socketError, "WSAEWOULDBLOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		default : 
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
		return X_FALSE ;
	}
#endif

	return X_TRUE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//获得套接字信息
X_BOOL SocketInterface::socket_getsockopt(X_SOCKET s, X_INT level, X_INT optname, X_VOID* optval, X_INT* optlen)
{
	__BASE_ENTER_FUNCTION
#ifdef __LINUX__
	if ( getsockopt( s , level , optname , optval , (socklen_t*)optlen ) == SOCKET_ERROR )
	{
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTSOCK : 
			strncpy( g_socketError, "ENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOPROTOOPT : 
			strncpy( g_socketError, "ENOPROTOOPT", SOCKET_ERROR_SIZE ) ;
			break;
		case EFAULT : 
			strncpy( g_socketError, "EFAULT", SOCKET_ERROR_SIZE ) ;
			break;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			}
		}//end of switch

		return X_FALSE ;
	}
#elif __WINDOWS__
	if ( getsockopt( s , level , optname , (X_CHAR*)optval , optlen ) == SOCKET_ERROR ) 
	{
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( g_socketError, "WSAEFAULT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( g_socketError, "WSAEINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOPROTOOPT : 
			strncpy( g_socketError, "WSAENOPROTOOPT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		default : 
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
		return X_FALSE ;
	}
#endif

	return X_TRUE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE;	
}

//设置套接字信息
X_BOOL SocketInterface::socket_setsockopt(X_SOCKET s, X_INT level, X_INT optname, const X_VOID* optval, X_INT optlen)
{
	__BASE_ENTER_FUNCTION

#ifdef __LINUX__
	if ( setsockopt( s , level , optname , optval , optlen ) == SOCKET_ERROR ) 
	{
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break ;
		case ENOTSOCK : 
			strncpy( g_socketError, "ENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		case ENOPROTOOPT : 
			strncpy( g_socketError, "ENOPROTOOPT", SOCKET_ERROR_SIZE ) ;
			break ;
		case EFAULT : 
			strncpy( g_socketError, "EFAULT", SOCKET_ERROR_SIZE ) ;
			break ;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break;
			}
		}//end of switch
		return X_FALSE ;
	}
#elif __WINDOWS__
	if ( setsockopt( s , level , optname , (X_CHAR*)optval , optlen ) == SOCKET_ERROR ) 
	{
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( g_socketError, "WSAEFAULT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINVAL : 
			strncpy( g_socketError, "WSAEINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETRESET : 
			strncpy( g_socketError, "WSAENETRESET", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOPROTOOPT : 
			strncpy( g_socketError, "WSAENOPROTOOPT", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTCONN : 
			strncpy( g_socketError, "WSAENOTCONN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};//end of switch
		return X_FALSE ;
	}
#endif

	return X_TRUE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//控制套接字选项
X_BOOL SocketInterface::socket_ioctlsocket(X_SOCKET s, long cmd, unsigned long* argp)
{
	__BASE_ENTER_FUNCTION

#ifdef __LINUX__
#elif __WINDOWS__
	if ( ioctlsocket(s,cmd,argp) == SOCKET_ERROR ) 
	{
		X_INT iErr = WSAGetLastError() ;
		g_socketErrorCode = iErr;
		switch ( iErr ) 
		{
		case WSANOTINITIALISED : 
			strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENETDOWN : 
			strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEINPROGRESS : 
			strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAENOTSOCK : 
			strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
			break ;
		case WSAEFAULT : 
			strncpy( g_socketError, "WSAEFAULT", SOCKET_ERROR_SIZE ) ;
			break ;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			};
		};
		return X_FALSE ;
	}
#endif

	return X_TRUE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//设置阻塞及非阻塞模式
X_BOOL SocketInterface::setsocketnonblocking(X_SOCKET s, X_BOOL on)
{
	__BASE_ENTER_FUNCTION

#ifdef __LINUX__

	X_INT flags = fcntl( s , F_GETFL , 0 );
	if (flags < 0)
	{
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EINTR : 
			strncpy( g_socketError, "EINTR", SOCKET_ERROR_SIZE ) ;
			break ;
		case EINVAL : 
			strncpy( g_socketError, "EINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break ;
		case EACCES : 
			strncpy( g_socketError, "EACCES", SOCKET_ERROR_SIZE ) ;
			break ;
		case EAGAIN : 
			strncpy( g_socketError, "EAGAIN", SOCKET_ERROR_SIZE ) ;
			break ;
		case EDEADLK : 
			strncpy( g_socketError, "EDEADLK", SOCKET_ERROR_SIZE ) ;
			break ;
		case EMFILE  : 
			strncpy( g_socketError, "EMFILE", SOCKET_ERROR_SIZE ) ;
			break ;
		case ENOLCK : 
			strncpy( g_socketError, "ENOLCK", SOCKET_ERROR_SIZE ) ;
			break ;
		default : 
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break;
			}
		}
		return X_FALSE;
	}
	
	if ( on )
		flags |= O_NONBLOCK;
	else
		flags &= ~O_NONBLOCK;
	X_INT result = fcntl ( s , F_SETFL , flags );
	if ( result < 0 ) 
	{
		g_socketErrorCode = errno;
		switch ( errno ) 
		{
		case EINTR : 
			strncpy( g_socketError, "EINTR", SOCKET_ERROR_SIZE ) ;
			break ;
		case EINVAL : 
			strncpy( g_socketError, "EINVAL", SOCKET_ERROR_SIZE ) ;
			break ;
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break ;
		case EACCES : 
			strncpy( g_socketError, "EACCES", SOCKET_ERROR_SIZE ) ;
			break ;
		case EAGAIN : 
			strncpy( g_socketError, "EAGAIN", SOCKET_ERROR_SIZE ) ;
			break ;
		case EDEADLK : 
			strncpy( g_socketError, "EDEADLK", SOCKET_ERROR_SIZE ) ;
			break ;
		case EMFILE  : 
			strncpy( g_socketError, "EMFILE", SOCKET_ERROR_SIZE ) ;
			break ;
		case ENOLCK : 
			strncpy( g_socketError, "ENOLCK", SOCKET_ERROR_SIZE ) ;
			break ;
		default : 
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break;
			}
		}
		return X_FALSE;
	}
	return X_TRUE;

#elif __WINDOWS__

	unsigned long argp = ( on == X_TRUE ) ? 1 : 0;
	return socket_ioctlsocket( s,FIONBIO,&argp);

#endif

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}


X_UINT SocketInterface::socket_available( X_SOCKET s )
{
	__BASE_ENTER_FUNCTION

#ifdef __LINUX__
	X_INT arg = 0;
	if ( ioctl(s, (unsigned long int)FIONREAD, &arg) < 0 )
	{
		g_socketErrorCode = errno;
		switch ( errno ) {
		case EBADF : 
			strncpy( g_socketError, "EBADF", SOCKET_ERROR_SIZE ) ;
			break;
		case ENOTTY :
			strncpy( g_socketError, "ENOTTY", SOCKET_ERROR_SIZE ) ;
			break;
		case EINVAL : 
			strncpy( g_socketError, "EINVAL", SOCKET_ERROR_SIZE ) ;
			break;
		default :
			{
				strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
				break;
			}
		}
		arg = 0;
	}
	return arg;
#elif __WINDOWS__
	unsigned long argp = 0;
	X_BOOL bRet = socket_ioctlsocket(s,FIONREAD,&argp);
	if (!bRet)
	{
		argp = 0;
	}
	return argp;
#endif

	__BASE_LEAVE_FUNCTION
		return 0 ;
}

//查询状态
X_INT SocketInterface::socket_select(X_INT maxfdp1, fd_set* readset, fd_set* writeset, fd_set* exceptset, struct timeval* timeout)
{
	__BASE_ENTER_FUNCTION

	X_INT result;
	__MYTRY 
	{
		result = select( maxfdp1 , readset , writeset , exceptset , timeout );
		if( result == SOCKET_ERROR )
		{
#ifdef __LINUX__

#elif __WINDOWS__
			X_INT iErr = WSAGetLastError() ;
			g_socketErrorCode = iErr;
			switch ( iErr ) 
			{
			case WSANOTINITIALISED : 
				strncpy( g_socketError, "WSANOTINITIALISED", SOCKET_ERROR_SIZE ) ;
				break ;
			case WSAEFAULT:
				strncpy( g_socketError, "WSAEFAULT", SOCKET_ERROR_SIZE ) ;
				break ;
			case WSAENETDOWN:
				strncpy( g_socketError, "WSAENETDOWN", SOCKET_ERROR_SIZE ) ;
				break ;
			case WSAEINVAL:
				strncpy( g_socketError, "WSAEINVAL", SOCKET_ERROR_SIZE ) ;
				break ;
			case WSAEINTR:
				strncpy( g_socketError, "WSAEINTR", SOCKET_ERROR_SIZE ) ;
				break ;
			case WSAEINPROGRESS:
				strncpy( g_socketError, "WSAEINPROGRESS", SOCKET_ERROR_SIZE ) ;
				break ;
			case WSAENOTSOCK:
				strncpy( g_socketError, "WSAENOTSOCK", SOCKET_ERROR_SIZE ) ;
				break ;
			default :
				{
					strncpy( g_socketError, "UNKNOWN", SOCKET_ERROR_SIZE ) ;
					break ;
				};
			};
#endif
		}//end if
	} 
	__MYCATCH
	{
	}

	return result;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}
