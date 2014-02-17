/*
**FileName: SocketServer.cpp
**Description:
**Autor: liam
**Create Time:
*/
#include "SocketServer.h"

SocketServer::SocketServer () 
{ 
	m_SocketID = INVALID_SOCKET ;
	memset( &m_SockAddr, 0, sizeof(m_SockAddr) ) ;
	memset( m_Ip, 0, IP_SIZE ) ;
	m_Port = 0 ;
}

SocketServer::~SocketServer () 
{ 
	if (m_SocketID != INVALID_SOCKET)
	{
		Close();
	}
}

X_BOOL SocketServer::Create( const X_CHAR* host , X_INT port)
{
	__BASE_ENTER_FUNCTION
	strncpy( m_Ip, host, IP_SIZE-1 ) ;
	m_Port = port ;

	X_BOOL bRet = CreateSocket();
	if (!bRet)
	{
		return X_FALSE;
	}

	bRet = ReuseAddr( ) ;
	if (!bRet)
	{
		return X_FALSE;
	}

	return X_TRUE;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//关闭连接
X_VOID SocketServer::Close ()
{
	__BASE_ENTER_FUNCTION

	if((m_SocketID != INVALID_SOCKET)&& (!IsSockError())) 
	{
		SocketClose();
	}

	memset( &m_SockAddr, 0, sizeof(SOCKADDR_IN) ) ;
	memset( m_Ip, 0, IP_SIZE ) ;
	m_Port = 0 ;

	__BASE_LEAVE_FUNCTION
}

//获得主机端口
X_UINT SocketServer::GetPort ()const
{
	__BASE_ENTER_FUNCTION

		return m_Port; 

	__BASE_LEAVE_FUNCTION
}

//获得主机IP
IP_t SocketServer::GetIP ()const
{
	__BASE_ENTER_FUNCTION

		return (IP_t)(m_SockAddr.sin_addr.s_addr);; 

	__BASE_LEAVE_FUNCTION
}

//绑定
X_BOOL SocketServer::Bind()
{
	__BASE_ENTER_FUNCTION

	m_SockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_SockAddr.sin_port        = htons(m_Port);

	X_BOOL result = SocketInterface::socket_bind( m_SocketID , (const struct sockaddr *)&m_SockAddr , sizeof(m_SockAddr) ) ;
	if( result )
		return X_TRUE ;
	else
		return X_FALSE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//监听
X_BOOL SocketServer::Listen( X_INT backlog )
{
	__BASE_ENTER_FUNCTION

		return SocketInterface::socket_listen( m_SocketID , backlog );

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;	
}

//重用地址
X_BOOL SocketServer::ReuseAddr ( X_BOOL on )
{
	__BASE_ENTER_FUNCTION 

	X_INT opt = on == X_TRUE ? 1 : 0;
	return SocketInterface::socket_setsockopt( m_SocketID , SOL_SOCKET , SO_REUSEADDR , &opt , sizeof(opt) );

	__BASE_LEAVE_FUNCTION

		return X_FALSE;
}

//接受连接
X_SOCKET SocketServer::Accept( struct sockaddr* addr, X_INT* addrlen )
{
	__BASE_ENTER_FUNCTION

	return SocketInterface::socket_accept( m_SocketID, addr, addrlen ) ;

	__BASE_LEAVE_FUNCTION

		return INVALID_SOCKET ;
}

X_BOOL SocketServer::Accept ( Socket* socket )
{
	__BASE_ENTER_FUNCTION

	X_INT addrlen = sizeof(SOCKADDR_IN) ;
	socket->SocketClose();

	X_SOCKET s = Accept( (struct sockaddr *)(socket->GetSocketAddr()), &addrlen ) ;
	if( s == INVALID_SOCKET )
		return X_FALSE ;
	
	socket->SetSocket(s);
	return X_TRUE;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}