/*
**FileName: SocketStream.h
**Description: 输入缓冲区
**Autor: liam
**Create Time:
*/
#include "SocketStream.h"
#include "Packet.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "ServerDefine.h"
SocketStream::SocketStream() 
{
	__BASE_ENTER_FUNCTION

	m_pSocket = X_NULL;
	m_pInputStream = X_NULL;
	m_pOutputStream = X_NULL;

	__BASE_LEAVE_FUNCTION
}

SocketStream::~SocketStream( ) 
{
	__BASE_ENTER_FUNCTION

	SAFE_DELETE(m_pInputStream);
	SAFE_DELETE(m_pOutputStream);

	m_pSocket = X_NULL;
	m_pInputStream = X_NULL;
	m_pOutputStream = X_NULL;

	__BASE_LEAVE_FUNCTION
}

//初始化
X_BOOL	SocketStream::Init(Socket* pSocket,
						   X_INT inbufferSize, 
						   X_INT inmaxBufferSize,
						   X_INT outbufferSize, 
						   X_INT outmaxBufferSize)
{
	__BASE_ENTER_FUNCTION
	if (pSocket ==X_NULL )
	{
		return X_FALSE;
	}
	if ((inbufferSize<=0)&&(inmaxBufferSize<=0))
	{
		return X_FALSE;
	}
	if ((outbufferSize<=0)&&(outmaxBufferSize<=0))
	{
		return X_FALSE;
	}
	if ((inbufferSize>inmaxBufferSize)||(outbufferSize>outmaxBufferSize))
	{
		return X_FALSE;
	}

	m_pSocket = pSocket;
	m_pInputStream = new InputStream();
	if (m_pInputStream == X_NULL)
	{
		return X_FALSE;
	}
	m_pOutputStream = new OutputStream();
	if (m_pInputStream == X_NULL)
	{
		return X_FALSE;
	}

	X_BOOL bRet = m_pInputStream->Init(inbufferSize, inmaxBufferSize);
	if (!bRet)
	{
		return X_FALSE;
	}
	bRet =m_pOutputStream->Init(outbufferSize, outmaxBufferSize);
	if (!bRet)
	{
		return X_FALSE;
	}

	return X_TRUE;
		__BASE_LEAVE_FUNCTION
			return X_FALSE;
}

X_INT SocketStream::Fill( X_CHAR* buf, X_INT length, EM_TYPE_MSG_MODE mode, X_INT& nSize) 
{
	__BASE_ENTER_FUNCTION
	if ((m_pInputStream == X_NULL)||(m_pOutputStream == X_NULL))
	{
		return 0;
	}
	if ((mode != EM_TYPE_MSG_MODE_READ)&&(mode != EM_TYPE_MSG_MODE_WRITE))
	{
		return 0;
	}
	if ( buf == X_NULL )
		return 0 ;

	if ( length <= 0 )
		return 0 ;

	if (mode == EM_TYPE_MSG_MODE_READ)
	{
		length = m_pInputStream->Read(buf, length);
		nSize = nSize + length;
	}
	else if (mode == EM_TYPE_MSG_MODE_WRITE)
	{
		length =m_pOutputStream->Write(buf, length);
		nSize = nSize + length;
	}
	return length ;

	__BASE_LEAVE_FUNCTION

		return 0 ;
}

X_BOOL SocketStream::ReadPacket( Packet* pPacket ) 
{
	__BASE_ENTER_FUNCTION
	if ((pPacket == X_NULL)||(m_pInputStream == X_NULL))
	{
		return X_FALSE;
	}

	return m_pInputStream->ReadPacket(*this, pPacket);

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

X_BOOL SocketStream::WritePacket( Packet* pPacket )
{
	__BASE_ENTER_FUNCTION
	if ((pPacket == X_NULL)||(m_pOutputStream == X_NULL))
	{
		return X_FALSE;
	}

	return m_pOutputStream->WritePacket(*this, pPacket);

	__BASE_LEAVE_FUNCTION

		return X_FALSE ;
}

X_INT SocketStream::Reveive( )
{
	__BASE_ENTER_FUNCTION
		if ((m_pSocket == X_NULL)||(m_pInputStream == X_NULL))
		{
			return SOCKET_ERROR;
		}

		return m_pInputStream->Reveive(m_pSocket);

		__BASE_LEAVE_FUNCTION

			return X_FALSE ;
}

X_INT SocketStream::Send( )
{
	__BASE_ENTER_FUNCTION
		if ((m_pSocket == X_NULL)||(m_pOutputStream == X_NULL))
		{
			return SOCKET_ERROR;
		}

		return m_pOutputStream->Flush(m_pSocket);

		__BASE_LEAVE_FUNCTION

			return X_FALSE ;
}

X_VOID SocketStream::CleanUp( )
{
	__BASE_ENTER_FUNCTION

	m_pInputStream->CleanUp();
	m_pOutputStream->CleanUp();

	__BASE_LEAVE_FUNCTION
}




