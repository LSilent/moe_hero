/*
**FileName: SocketClient.cpp
**Description:
**Autor: liam
**Create Time:
*/
#include "SocketClient.h"

SocketClient::SocketClient () 
{ 
	m_SocketID = INVALID_SOCKET ;
	memset( &m_SockAddr, 0, sizeof(SOCKADDR_IN) ) ;
	memset( m_HostIp, 0, IP_SIZE ) ;
	m_HostPort = 0 ;
}

SocketClient::~SocketClient () 
{ 
	if (m_SocketID != INVALID_SOCKET)
	{
		Close();
	}
}

X_BOOL SocketClient::Create( const X_CHAR* host , X_UINT port )
{
	__BASE_ENTER_FUNCTION

	X_BOOL bRet = CreateSocket();
	if (!bRet)
	{
		return X_FALSE;
	}

	strncpy( m_HostIp, host, IP_SIZE-1 ) ;
	m_HostPort = port ;
	memset( &m_SockAddr , 0 , sizeof(m_SockAddr) );
	m_SockAddr.sin_family = AF_INET;

	return X_TRUE;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//关闭连接
X_VOID SocketClient::Close ()
{
	__BASE_ENTER_FUNCTION

	if((m_SocketID != INVALID_SOCKET)&& (!IsSockError())) 
	{
		SocketClose();
	}
	
	m_SocketID = INVALID_SOCKET ;
	memset( &m_SockAddr, 0, sizeof(SOCKADDR_IN) ) ;
	memset( m_HostIp, 0, IP_SIZE ) ;
	m_HostPort = 0 ;

	__BASE_LEAVE_FUNCTION
}

//连接远程主机
X_BOOL SocketClient::Connect()
{
	__BASE_ENTER_FUNCTION

	m_SockAddr.sin_addr.s_addr = inet_addr( m_HostIp );
	m_SockAddr.sin_port = htons(m_HostPort);
	X_BOOL bResult = SocketInterface::socket_connect( m_SocketID , (const struct sockaddr *)&m_SockAddr , sizeof(m_SockAddr) );
	if( bResult)
		return X_TRUE ;
	else
		return X_FALSE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

//获得主机端口
X_UINT SocketClient::GetHostPort ()const
{
	__BASE_ENTER_FUNCTION

	return m_HostPort; 

	__BASE_LEAVE_FUNCTION
}

//获得主机IP
IP_t SocketClient::GetHostIP ()const
{
	__BASE_ENTER_FUNCTION

	return (IP_t)(m_SockAddr.sin_addr.s_addr);; 

	__BASE_LEAVE_FUNCTION
}