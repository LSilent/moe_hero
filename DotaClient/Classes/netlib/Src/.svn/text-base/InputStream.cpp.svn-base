/*
**FileName: InputStream.h
**Description: 输入缓冲区
**Autor: liam
**Create Time:
*/
#include "InputStream.h"
#include "SocketStream.h"
#include "Packet.h"
#include "ServerDefine.h"
extern X_INT  g_socketErrorCode;

InputStream::InputStream() 
{
	__BASE_ENTER_FUNCTION

	m_nBufferLength = 0 ;
	m_nMaxBufferLength = 0;

	m_Head = 0;
	m_Tail = 0;
	m_pBuffer = X_NULL;

	__BASE_LEAVE_FUNCTION
}

InputStream::~InputStream( ) 
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
X_BOOL	InputStream::Init(X_INT bufferSize, X_INT maxBufferSize)
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

X_INT InputStream::Length( )const
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

X_INT InputStream::Read( X_CHAR* buf, X_INT length) 
{
	__BASE_ENTER_FUNCTION
	if ((buf == X_NULL)||(length <= 0))
	{
		return 0;
	}

	if ( length > Length() )
		return 0 ;

	if ( m_Head < m_Tail ) 
	{
		memcpy( buf, &m_pBuffer[m_Head], length ) ;
	} 
	else 
	{
		X_UINT rightLen = m_nBufferLength-m_Head ;
		if( (X_UINT)length<=rightLen )
		{
			memcpy( buf, &m_pBuffer[m_Head], length ) ;
		} 
		else 
		{
			memcpy( buf, &m_pBuffer[m_Head], rightLen ) ;
			memcpy( &buf[rightLen], m_pBuffer, length-rightLen ) ;
		}
	}

	m_Head = (m_Head+length)%m_nBufferLength ;

	return length ;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

X_BOOL	InputStream::ReadPacket(SocketStream& socketstream, Packet* pPacket )
{
	__BASE_ENTER_FUNCTION
	if (pPacket == X_NULL)
		return X_FALSE;

	X_BOOL ret = Skip( PACKET_HEADER_SIZE ) ;
	if( !ret )
		return X_FALSE ;

	return pPacket->Fill(socketstream, EM_TYPE_MSG_MODE_READ) ;
	__BASE_LEAVE_FUNCTION
	return X_FALSE;
}

X_BOOL InputStream::Peek( X_CHAR* buf, X_INT length ) 
{
	__BASE_ENTER_FUNCTION

	if ((buf == X_NULL)||(length <= 0))
	{
		return X_FALSE;
	}

	if( length>Length() )
		return X_FALSE ;

	if( m_Head<m_Tail ) 
	{
		memcpy( buf , &m_pBuffer[m_Head] , length );

	} 
	else 
	{
		X_INT rightLen = m_nBufferLength-m_Head ;
		if( length<=rightLen ) 
		{
			memcpy( &buf[0], &m_pBuffer[m_Head], length ) ;
		} 
		else 
		{
			memcpy( &buf[0], &m_pBuffer[m_Head], rightLen ) ;
			memcpy( &buf[rightLen], &m_pBuffer[0], length-rightLen ) ;
		}
	}

	return X_TRUE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

X_BOOL InputStream::Skip( X_INT length ) 
{
	__BASE_ENTER_FUNCTION
	if (length <= 0)
		return X_FALSE ;

	if( length>Length( ) )
		return X_FALSE ;

	m_Head = (m_Head+length)%m_nBufferLength ;

	return X_TRUE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

X_VOID InputStream::Initsize( )
{
	m_Head = 0 ;
	m_Tail = 0 ;

	SAFE_DELETE_ARRAY( m_pBuffer ) ;

	m_pBuffer = new X_CHAR[DEFAULT_SOCKETINPUT_BUFFERSIZE] ;
	m_nBufferLength = DEFAULT_SOCKETINPUT_BUFFERSIZE ;

	memset( m_pBuffer, 0, m_nBufferLength ) ;
}

X_INT InputStream::Reveive( Socket* pSocket ) 
{
	__BASE_ENTER_FUNCTION
	if (pSocket == X_NULL)
		throw 1;

	X_INT nFilled = 0 ;
	X_INT nReceived = 0 ;
	X_INT nFree = 0 ;
	if ( m_Head <= m_Tail ) 
	{
		if ( m_Head == 0 ) 
		{
			nReceived = 0 ;
			nFree = m_nBufferLength-m_Tail-1 ;
			if( nFree != 0 )
			{
				nReceived = pSocket->Receive( &m_pBuffer[m_Tail] , nFree );
				if (nReceived==SOCKET_ERROR_WOULD_BLOCK) 
				{
					return 0 ; 
				}
				if (nReceived==0)
				{
					return EM_SOCKET_ERROR_STEP0;
				}
				if (nReceived<0)
				{
					return EM_SOCKET_ERROR_STEP1;
				}
				m_Tail += nReceived;
				nFilled += nReceived;
			}

			if( nReceived == nFree ) 
			{
				X_UINT available = pSocket->Available();
				if ( available > 0 ) 
				{
					if( (m_nBufferLength+available+1)>m_nMaxBufferLength )
					{
						Initsize( ) ;
						g_socketErrorCode = 0;
						return EM_SOCKET_ERROR_STEP2;
					}
					if( !Resize( available+1 ) )
						return 0 ;

					nReceived = pSocket->Receive( &m_pBuffer[m_Tail] , available );
					if (nReceived==SOCKET_ERROR_WOULD_BLOCK) 
					{
						return 0 ; 
					}
					if (nReceived==0)
					{
						return EM_SOCKET_ERROR_STEP3;
					}
					if (nReceived<0)
					{
						return EM_SOCKET_ERROR_STEP4;
					}

					m_Tail += nReceived;
					nFilled += nReceived;
				}
			}
		} 
		else 
		{
			nFree = m_nBufferLength-m_Tail ;
			nReceived = pSocket->Receive( &m_pBuffer[m_Tail], nFree );
			if (nReceived==SOCKET_ERROR_WOULD_BLOCK) 
			{
				return 0 ; 
			}
			if (nReceived==0)
			{
                
				return EM_SOCKET_ERROR_STEP5;
			}
			if (nReceived<0)
			{
				return EM_SOCKET_ERROR_STEP6;
			}

			m_Tail = (m_Tail+nReceived)%m_nBufferLength ;
			nFilled += nReceived ;

			if( nReceived==nFree ) 
			{
				nReceived = 0 ;
				nFree = m_Head-1 ;
				if( nFree!=0 )
				{
					nReceived = pSocket->Receive( &m_pBuffer[0] , nFree );
					if (nReceived==SOCKET_ERROR_WOULD_BLOCK) 
					{
						return 0 ; 
					}
					if (nReceived==0)
					{
						return EM_SOCKET_ERROR_STEP7;
					}
					if (nReceived<0)
					{
						return EM_SOCKET_ERROR_STEP8;
					}

					m_Tail += nReceived;
					nFilled += nReceived;
				}

				if( nReceived==nFree ) 
				{
					X_UINT available = pSocket->Available();
					if ( available > 0 ) 
					{
						if( (m_nBufferLength+available+1)>m_nMaxBufferLength )
						{
							Initsize( ) ;
							g_socketErrorCode = 0;
							return EM_SOCKET_ERROR_STEP9;
						}
						if( !Resize( available+1 ) )
							return 0 ;

						nReceived = pSocket->Receive( &m_pBuffer[m_Tail] , available );
						if (nReceived==SOCKET_ERROR_WOULD_BLOCK) 
						{
							return 0 ; 
						}
						if (nReceived==0)
						{
							return EM_SOCKET_ERROR_STEP10;
						}
						if (nReceived<0)
						{
							return EM_SOCKET_ERROR_STEP11;
						}

						m_Tail += nReceived;
						nFilled += nReceived;
					}
				}
			}
		}

	} 
	else 
	{	
		nReceived = 0 ;
		nFree = m_Head-m_Tail-1 ;
		if( nFree!=0 )
		{
			nReceived = pSocket->Receive( &m_pBuffer[m_Tail], nFree ) ;
			if (nReceived==SOCKET_ERROR_WOULD_BLOCK) 
			{
				return 0 ; 
			}
			if (nReceived==0)
			{
				return EM_SOCKET_ERROR_STEP12;
			}
			if (nReceived<0)
			{
				return EM_SOCKET_ERROR_STEP13;
			}
			m_Tail += nReceived ;
			nFilled += nReceived ;
		}
		if( nReceived==nFree ) 
		{
			X_UINT available = pSocket->Available( ) ;
			if ( available>0 ) 
			{
				if( (m_nBufferLength+available+1)>m_nMaxBufferLength )
				{
					Initsize( ) ;
					g_socketErrorCode = 0;
					return EM_SOCKET_ERROR_STEP14;
				}
				if( !Resize( available+1 ) )
					return 0 ;

				nReceived = pSocket->Receive( &m_pBuffer[m_Tail], available ) ;
				if (nReceived==SOCKET_ERROR_WOULD_BLOCK) 
				{
					return 0 ; 
				}
				if (nReceived==0)
				{
					return EM_SOCKET_ERROR_STEP15;
				}
				if (nReceived<0)
				{
					return EM_SOCKET_ERROR_STEP16;
				}

				m_Tail += nReceived ;
				nFilled += nReceived ;
			}
		}
	}

	return nFilled ;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

X_BOOL InputStream::Resize( X_INT size )
{
	__BASE_ENTER_FUNCTION

	size = _____max( size, (X_INT)(m_nBufferLength>>1) ) ;
	X_INT newBufferLen = m_nBufferLength + size;
	X_INT length = Length();

	if ( size < 0 ) 
	{
		if ( newBufferLen < 0 || newBufferLen < length )
			return X_FALSE ;		
	} 

	X_CHAR * newBuffer = new X_CHAR[ newBufferLen ];

	if ( m_Head < m_Tail ) 
	{
		memcpy( newBuffer , &m_pBuffer[m_Head] , m_Tail - m_Head );
	} 
	else if ( m_Head > m_Tail ) 
	{
		memcpy( newBuffer , &m_pBuffer[m_Head] , m_nBufferLength - m_Head );
		memcpy( &newBuffer[ m_nBufferLength - m_Head ] , m_pBuffer , m_Tail );
	}

	delete [] m_pBuffer ;

	m_pBuffer = newBuffer ;
	m_nBufferLength = newBufferLen ;
	m_Head = 0 ;
	m_Tail = length ;

	return X_TRUE ;

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

X_VOID InputStream::CleanUp( )
{
	__BASE_ENTER_FUNCTION

	m_Head = 0 ;
	m_Tail = 0 ;

	__BASE_LEAVE_FUNCTION
}




 
