/*
**FileName: OutputStream.cpp
**Description: 输出缓冲区
**Autor: liam
**Create Time:
*/
#include "OutputStream.h"
#include "Packet.h"
#include "SocketStream.h"
#include "ServerDefine.h"
extern X_INT  g_socketErrorCode;

OutputStream::OutputStream() 
{
	__BASE_ENTER_FUNCTION
	m_nBufferLength = 0 ;
	m_nMaxBufferLength = 0;

	m_Head = 0;
	m_Tail = 0;
	m_pBuffer = X_NULL;

	__BASE_LEAVE_FUNCTION
}

OutputStream::~OutputStream( ) 
{
	__BASE_ENTER_FUNCTION

	SAFE_DELETE_ARRAY(m_pBuffer);

	m_nBufferLength = 0 ;
	m_nMaxBufferLength = 0;

	m_Head = 0;
	m_Tail = 0;
	m_pBuffer = X_NULL;
	__BASE_LEAVE_FUNCTION
}

//初始化
X_BOOL	OutputStream::Init(X_INT bufferSize, X_INT maxBufferSize)
{
	__BASE_ENTER_FUNCTION
	if ((bufferSize>0)&&(maxBufferSize>0))
	{
		m_nBufferLength = bufferSize ;
		m_nMaxBufferLength = maxBufferSize;

		m_Head = 0;
		m_Tail = 0;

		m_pBuffer = new X_CHAR[ m_nBufferLength ];
		memset( m_pBuffer, 0, m_nBufferLength*sizeof(X_CHAR) ) ;

		return X_TRUE ;
	}
	__BASE_LEAVE_FUNCTION
		return X_FALSE;
}

X_INT OutputStream::Length( )const
{
	__BASE_ENTER_FUNCTION

	if( m_Head<m_Tail )
		return m_Tail-m_Head;

	else if( m_Head>m_Tail ) 
		return m_nBufferLength-m_Head+m_Tail ;

	return 0 ;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

X_INT OutputStream::Write( const X_CHAR* buf, X_INT length ) 
{
	__BASE_ENTER_FUNCTION
	if ((buf == X_NULL)||(length <= 0))
	{
		return 0;
	}

	X_INT nFree = ( (m_Head<=m_Tail)?(m_nBufferLength-m_Tail+m_Head-1):(m_Head-m_Tail-1) ) ;

	if( length>=nFree )
	{
		if( !Resize( length-nFree+1 ) )
			return 0 ;
	}

	if( m_Head<=m_Tail ) 
	{	
		if( m_Head==0 ) 
		{
			nFree = m_nBufferLength - m_Tail - 1;
			memcpy( &m_pBuffer[m_Tail], buf, length ) ;
		} 
		else 
		{
			nFree = m_nBufferLength-m_Tail ;
			if( length<=nFree )
			{
				memcpy( &m_pBuffer[m_Tail], buf, length ) ;
			}
			else 
			{
				memcpy( &m_pBuffer[m_Tail], buf, nFree ) ;
				memcpy( m_pBuffer, &buf[nFree], length-nFree ) ;
			}
		}
	} 
	else 
	{	
		memcpy( &m_pBuffer[m_Tail], buf, length ) ;
	}

	m_Tail = (m_Tail+length)%m_nBufferLength ;

	return length;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

X_BOOL OutputStream::WritePacket(SocketStream& socketstream, Packet* pPacket )
{
	__BASE_ENTER_FUNCTION
	if (pPacket == X_NULL)
		return X_FALSE;

	PacketID packetID = pPacket->GetPacketID() ;
	X_INT w = Write( (X_CHAR*)&packetID , sizeof(PacketID) );
	if (w <= 0)
	{
		return X_FALSE;
	}
	X_CHAR packetEncryptFlag = pPacket->GetEncryptFlag( ) ;
	w = Write( (X_CHAR*)&packetEncryptFlag , sizeof(X_CHAR) );
	if (w <= 0)
	{
		return X_FALSE;
	}
	X_CHAR* pBuf = &m_pBuffer[m_Tail];
	//X_INT nbegin = m_Tail;
	X_INT packetINT ;
	X_CHAR* pPacketINT = (X_CHAR*)&packetINT;
	w = Write( (X_CHAR*)&packetINT, sizeof(X_INT) ) ;
	if (w <= 0)
	{
		return X_FALSE;
	}
	pPacket->SetSize(0);
	X_BOOL bRet = pPacket->Fill( socketstream , EM_TYPE_MSG_MODE_WRITE ) ;
	if (bRet)
	{
		X_INT packetSize = pPacket->GetSize() ;
		packetINT = packetSize;
		if (m_Head < m_Tail)
		{
			X_INT nbegin = m_Tail-packetSize-sizeof(X_INT);
			X_CHAR* pBuf = &m_pBuffer[nbegin];
			memcpy( pBuf, pPacketINT, sizeof(X_INT) ) ;
		}
		else
		{
			if (m_Tail >= (packetSize+sizeof(X_INT)))
			{
				X_CHAR* pBuf = &m_pBuffer[m_Tail - packetSize - sizeof(X_INT)];
				memcpy( pBuf, pPacketINT, sizeof(X_INT) ) ;
			}
			else if(m_Tail > packetSize)
			{
				X_INT nbegin = m_nBufferLength - (sizeof(X_INT) - (m_Tail - packetSize));
				X_CHAR* pBuf = &m_pBuffer[nbegin];
				memcpy( pBuf, pPacketINT, sizeof(X_INT) - (m_Tail - packetSize)) ;
				memcpy( m_pBuffer, &pPacketINT[sizeof(X_INT) - (m_Tail - packetSize)], m_Tail - packetSize ) ;
			}
			else
			{
				X_INT nbegin = m_nBufferLength - (packetSize - m_Tail) - sizeof(X_INT);
				X_CHAR* pBuf = &m_pBuffer[nbegin];
				memcpy( pBuf, pPacketINT, sizeof(X_INT) ) ;
			}
		}
	}
	
	return bRet;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

X_VOID OutputStream::Initsize( )
{
	m_Head = 0 ;
	m_Tail = 0 ;

	SAFE_DELETE_ARRAY( m_pBuffer ) ;

	m_pBuffer = new X_CHAR[DEFAULT_SOCKETOUTPUT_BUFFERSIZE] ;
	m_nBufferLength = DEFAULT_SOCKETOUTPUT_BUFFERSIZE ;

	memset( m_pBuffer, 0, m_nBufferLength ) ;
}

X_INT OutputStream::Flush( Socket* pSocket ) 
{
	__BASE_ENTER_FUNCTION
	if ( pSocket == X_NULL)
		throw 1;
	
	X_INT nFlushed = 0;
	X_INT nSent = 0;
	X_INT nLeft;

	//如果单个客户端的缓存太大，则重新设置缓存，并将此客户端断开连接
	if( m_nBufferLength>m_nMaxBufferLength )
	{
		Initsize( ) ;
		return EM_SOCKET_ERROR_STEP0;
	}

#if defined(__WINDOWS__)
	X_UINT flag = MSG_DONTROUTE ;
#elif defined(__LINUX__)
	X_INT flag = 0x4000;//MSG_NOSIGNAL ;
#endif

	__MYTRY 
	{
		if ( m_Head < m_Tail ) 
		{
			nLeft = m_Tail - m_Head;

			while ( nLeft > 0 ) 
			{
				nSent = pSocket->Send( &m_pBuffer[m_Head] , nLeft , (X_INT)flag );
				if (nSent==SOCKET_ERROR_WOULD_BLOCK) return 0 ; 
				if (nSent==SOCKET_ERROR) return EM_SOCKET_ERROR_STEP1 ;
				if (nSent==0) return 0;

				nFlushed += nSent;
				nLeft -= nSent;
				m_Head += nSent;
			}
		} 
		else if( m_Head > m_Tail ) 
		{
			nLeft = m_nBufferLength - m_Head;

			while ( nLeft > 0 ) 
			{
				nSent = pSocket->Send( &m_pBuffer[m_Head] , nLeft , (X_INT)flag );
				if (nSent==SOCKET_ERROR_WOULD_BLOCK) return 0 ; 
				if (nSent==SOCKET_ERROR) return EM_SOCKET_ERROR_STEP2 ;
				if (nSent==0) return 0;

				nFlushed += nSent;
				nLeft -= nSent;
				m_Head += nSent;
			}
			m_Head = 0;

			nLeft = m_Tail;

			while ( nLeft > 0 ) 
			{
				nSent = pSocket->Send( &m_pBuffer[m_Head] , nLeft , (X_INT)flag );
				if (nSent==SOCKET_ERROR_WOULD_BLOCK) return 0 ; 
				if (nSent==SOCKET_ERROR) return EM_SOCKET_ERROR_STEP3 ;
				if (nSent==0) return 0;

				nFlushed += nSent;
				nLeft -= nSent;
				m_Head += nSent;
			}
		}

		if ( m_Head != m_Tail ) 
		{
			g_socketErrorCode = 0;
			return EM_SOCKET_ERROR_STEP4 ;
		}

	}
	__MYCATCH
	{
		if( nSent>0 )
		{
			m_Head += nSent;
		}
	} 

	m_Head = m_Tail = 0 ;

	return nFlushed;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

X_BOOL OutputStream::Resize( X_INT size )
{
	__BASE_ENTER_FUNCTION
	size = _____max( size, (X_INT)(m_nBufferLength>>1) ) ;

	X_INT newBufferLen = m_nBufferLength+size ;
	X_INT length = Length( ) ;

	if( size<0 ) 
	{
		if( newBufferLen<0 || newBufferLen<length )
			return X_FALSE ;
	} 

	X_CHAR * newBuffer = new X_CHAR[ newBufferLen ] ;
	if( newBuffer == X_NULL )
		return X_FALSE ;

	if( m_Head<m_Tail ) 
	{
		memcpy( newBuffer, &m_pBuffer[m_Head], m_Tail-m_Head ) ;
	} 
	else if( m_Head>m_Tail ) 
	{
		memcpy( newBuffer, &m_pBuffer[m_Head] , m_nBufferLength-m_Head );
		memcpy( &newBuffer[m_nBufferLength-m_Head], m_pBuffer, m_Tail );
	}

	delete [] m_pBuffer;

	m_pBuffer = newBuffer;
	m_nBufferLength = newBufferLen;
	m_Head = 0;
	m_Tail = length;	

	return X_TRUE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

X_VOID OutputStream::CleanUp( )
{
	__BASE_ENTER_FUNCTION

	m_Head = 0 ;
	m_Tail = 0 ;

	__BASE_LEAVE_FUNCTION
}
