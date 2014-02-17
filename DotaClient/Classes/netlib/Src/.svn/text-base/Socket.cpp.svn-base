/*
**FileName: Socket.cpp
**Description:
**Autor: liam
**Create Time:
*/
#include "Socket.h"

X_INT GetSocketErrorCode()
{
	extern X_INT  g_socketErrorCode;
	return g_socketErrorCode ;
}

X_CHAR* GetSocketErrorDescription()
{
	extern X_CHAR g_socketError[SOCKET_ERROR_SIZE] ;
	return g_socketError ;
}

Socket::Socket () 
{ 
	m_SocketID = INVALID_SOCKET ;
	memset( &m_SockAddr, 0, sizeof(SOCKADDR_IN) ) ;
}

Socket::~Socket () 
{ 
	if (m_SocketID != INVALID_SOCKET)
	{
		SocketClose();
	}
}

X_BOOL Socket::CreateSocket()
{
	__BASE_ENTER_FUNCTION
	m_SocketID = SocketInterface::socket_create( AF_INET , SOCK_STREAM , 0 );
	if (m_SocketID == INVALID_SOCKET)
	{
		return X_FALSE;
	}

	memset( &m_SockAddr , 0 , sizeof(m_SockAddr) );
	m_SockAddr.sin_family = AF_INET;

	return X_TRUE;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//关闭连接
X_VOID Socket::SocketClose ()
{
	__BASE_ENTER_FUNCTION
	X_SOCKET socketID = m_SocketID;
	if((m_SocketID != INVALID_SOCKET)&& (!IsSockError())) 
	{
		SocketInterface::socket_close(socketID );
		m_SocketID = INVALID_SOCKET;
		memset( &m_SockAddr , 0 , sizeof(m_SockAddr) );
	}

	__BASE_LEAVE_FUNCTION
}

//获得端口
X_SOCKET Socket::GetSocket ()const
{
	__BASE_ENTER_FUNCTION

		return m_SocketID; 

	__BASE_LEAVE_FUNCTION

	return INVALID_VALUE;
}

//设置关闭延时时间
X_BOOL Socket::SetLinger (X_UINT lingertime)
{
	__BASE_ENTER_FUNCTION

	struct linger ling;

	ling.l_onoff = lingertime > 0 ? 1 : 0;
	ling.l_linger = lingertime;
	return SocketInterface::socket_setsockopt( m_SocketID , SOL_SOCKET , SO_LINGER , &ling , sizeof(ling) );

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;	
}

//是否socket有错误
X_BOOL Socket::IsSockError()const
{
	__BASE_ENTER_FUNCTION

	X_INT error=0;
	X_INT length = (X_INT)sizeof(error);
	X_BOOL bResult = SocketInterface::socket_getsockopt( m_SocketID , SOL_SOCKET , SO_ERROR , &error, &length );
	if( bResult == X_TRUE ) 
		return X_FALSE;
	else 			  
		return X_TRUE;

	__BASE_LEAVE_FUNCTION

		return X_TRUE ;
}

//获得错误码
X_INT Socket::GetSockError()const
{
	X_INT error = UNKNOWN_SOCKET_ERROR;
	__BASE_ENTER_FUNCTION

	X_INT length = (X_INT)sizeof(error);
	X_BOOL bResult = SocketInterface::socket_getsockopt( m_SocketID , SOL_SOCKET , SO_ERROR , &error, &length );
	if( bResult == X_FALSE ) 
		return UNKNOWN_SOCKET_ERROR;
	else 			  
		return error;

	__BASE_LEAVE_FUNCTION

		return error;
}


//设置阻塞或非阻塞模式
X_BOOL Socket::SetNonBlocking (X_BOOL on)
{
	__BASE_ENTER_FUNCTION

		return SocketInterface::setsocketnonblocking( m_SocketID , on );

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

X_BOOL Socket::SetNonDelay (X_BOOL on)
{
	__BASE_ENTER_FUNCTION
	X_INT intOn = on;
	return SocketInterface::socket_setsockopt( m_SocketID ,IPPROTO_TCP, TCP_NODELAY, (const void *) &intOn, sizeof(intOn));

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//获得接收缓冲区大小
X_INT Socket::GetReceiveBufferSize ()const 
{ 
	__BASE_ENTER_FUNCTION

	X_INT ReceiveBufferSize = 0;
	X_INT size = (X_INT)sizeof(ReceiveBufferSize);
	SocketInterface::socket_getsockopt( m_SocketID , SOL_SOCKET , SO_RCVBUF , &ReceiveBufferSize, &size );

	return ReceiveBufferSize;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

//设置接收缓冲区大小
X_BOOL Socket::SetReceiveBufferSize (X_INT size)
{ 
	__BASE_ENTER_FUNCTION

		return (X_BOOL)(SocketInterface::socket_setsockopt( m_SocketID , SOL_SOCKET , SO_RCVBUF , &size, sizeof(X_INT) ) ) ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//获得发送缓冲区大小
X_INT Socket::GetSendBufferSize ()const 
{ 
	__BASE_ENTER_FUNCTION

	X_INT SendBufferSize;
	X_INT size = (X_INT)sizeof(SendBufferSize);

	SocketInterface::socket_getsockopt( m_SocketID , SOL_SOCKET , SO_SNDBUF , &SendBufferSize, &size );

	return SendBufferSize;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

//设置发送缓冲区大小
X_BOOL Socket::SetSendBufferSize (X_INT size)
{ 
	__BASE_ENTER_FUNCTION

		return (X_BOOL)(SocketInterface::socket_setsockopt( m_SocketID , SOL_SOCKET , SO_SNDBUF , &size, sizeof(X_INT) ) );

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//发送数据
X_INT Socket::Send(const X_VOID* buf, X_INT length, X_INT flags)
{
	__BASE_ENTER_FUNCTION

		return SocketInterface::socket_send( m_SocketID , buf , length , flags );

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

//接收数据
X_INT Socket::Receive(X_VOID* buf, X_INT length, X_INT flags)
{
	__BASE_ENTER_FUNCTION

		return SocketInterface::socket_recv( m_SocketID , buf , length , flags );

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

//现有数据
X_UINT Socket::Available()const
{
	__BASE_ENTER_FUNCTION

		return SocketInterface::socket_available( m_SocketID );

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

//判断socket是否有效
X_BOOL Socket::IsSocketValid()
{
	__BASE_ENTER_FUNCTION

	if (m_SocketID == INVALID_SOCKET)
	{
		return X_FALSE;
	}
	
	return X_TRUE;

	__BASE_LEAVE_FUNCTION
		return X_FALSE;
}

//获得IP
X_CHAR* Socket::GetIp()
{
	__BASE_ENTER_FUNCTION

	return inet_ntoa(m_SockAddr.sin_addr);

	__BASE_LEAVE_FUNCTION
		return X_NULL;
}
