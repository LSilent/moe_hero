 
#include "NetworkSystem.h"
#include "PacketClientFactoryManager.h"
#include "PacketExecute.h"
#include "GameDefine.h"
#include "SocketClient.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "SocketInterface.h"
#include "./timer/SystemTimer.h"
#include "./game/MainGame.h"
#include "cocos2d.h"
#include "./Game.h"
#include "./event/EventSystem.h"
#include "./Packets/Base/PacketDefine.h"

#ifdef __WINDOWS__
#pragma comment(lib, "wsock32")
#endif
IMPLEMENT_SINGLETON(NetworkSystem);

NetworkSystem::NetworkSystem()
{
	 m_init =false;
    bconnectRet = false;
}

NetworkSystem::~NetworkSystem()
{
}
//初始化
X_VOID NetworkSystem::Initial()
{
#ifdef __WINDOWS__

	X_SHORT wVersionRequested;
	WSADATA	wsaData;
	X_INT err;

	wVersionRequested = MAKEWORD( 2, 2 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 )
	{
		return;
	}

	if ( LOBYTE( wsaData.wVersion ) != 2 ||	HIBYTE( wsaData.wVersion ) != 2 )
	{
		WSACleanup( );
		return; 
	}
 
#endif 
	m_pPacketFactoryManager		= new  PacketClientFactoryManager();
	if(m_pPacketFactoryManager == X_NULL)
	{
		return;
	}
	if(m_pPacketFactoryManager->Init() == X_FALSE)
	{
		return;
	}
	PacketExecute::Initial();

	m_pClientSocket	= new SocketClient();
	if(m_pClientSocket == X_NULL)
	{
		return;
	}

	m_pSocketStream = new SocketStream();
	if(m_pSocketStream == X_NULL)
	{
		return;
	}
 
	X_BOOL bResult =  m_pSocketStream->Init(m_pClientSocket,DEFAULT_SOCKETINPUT_BUFFERSIZE,MAX_SOCKETINPUT_BUFFERSIZE,DEFAULT_SOCKETOUTPUT_BUFFERSIZE,MAX_SOCKETOUTPUT_BUFFERSIZE);
 
	m_nConnectStartTime			= 0;
	memset(m_szServerIP,0,sizeof(m_szServerIP));
	m_nServerPort				= 0;
	m_nNetworkState				= NET_NORMAL;
	FD_ZERO( &m_ReadFDs[EM_SELECT_BAK] ) ;
	FD_ZERO( &m_WriteFDs[EM_SELECT_BAK] ) ;
	FD_ZERO( &m_ExceptFDs[EM_SELECT_BAK] ) ;
	FD_ZERO( &m_ReadFDs[EM_SELECT_USE] ) ;
	FD_ZERO( &m_WriteFDs[EM_SELECT_USE] ) ;
	FD_ZERO( &m_ExceptFDs[EM_SELECT_USE] ) ;
	m_Timeout[EM_SELECT_BAK].tv_sec = 0;
	m_Timeout[EM_SELECT_BAK].tv_usec = 0;
	m_allPacketCd.clear();
	//m_WaitPacket.clear();
	m_AllLimit.clear();
	m_AllLimit.push_back(PACEKT_CG_ASKFIGHT);
	m_AllLimit.push_back(PACKET_CG_ARENA_CHALLENGE);
	
	m_init =true;
}
X_VOID NetworkSystem::Release()
{
    bconnectRet = false;

	m_init =false;
	m_allPacketCd.clear();
	//m_WaitPacket.clear();
	m_AllLimit.clear();
	FD_ZERO( &m_ReadFDs[EM_SELECT_BAK] ) ;
	FD_ZERO( &m_WriteFDs[EM_SELECT_BAK] ) ;
	FD_ZERO( &m_ExceptFDs[EM_SELECT_BAK] ) ;
	FD_ZERO( &m_ReadFDs[EM_SELECT_USE] ) ;
	FD_ZERO( &m_WriteFDs[EM_SELECT_USE] ) ;
	FD_ZERO( &m_ExceptFDs[EM_SELECT_USE] ) ;
	m_Timeout[EM_SELECT_BAK].tv_sec = 0;
	m_Timeout[EM_SELECT_BAK].tv_usec = 0;
	m_nNetworkState				= NET_NORMAL;
		if(m_pClientSocket != X_NULL)
		{
			
			 m_pClientSocket->Close();
			 SAFE_DELETE(m_pClientSocket);
		}
		if(m_pSocketStream != X_NULL)
		{
			SAFE_DELETE(m_pSocketStream);
            m_pSocketStream =X_NULL;
		}
		if (m_pPacketFactoryManager)
		{
			m_pPacketFactoryManager->Release();
			SAFE_DELETE(m_pPacketFactoryManager);
		}
		
		PacketExecute::Release();
#ifdef __WINDOWS__
		WSACleanup();
#endif
}
X_VOID NetworkSystem::Tick(X_UINT nTime)
{
	if (!m_init)return;
	switch(m_nNetworkState)
	{
		case NET_NORMAL:
			break;
		case NET_CONNECTING_STATE:
			{
				_ProcessNetConnecting();
			}
			break;
		case NET_RECONNECTING_STATE:
			{
				_ProcessNetReConnecting();
			}
			break;
		case NET_CONNECTED_OK_STATE:
			break;
		case NET_DATA_WORKING:
			{
				/*map< X_INT, X_INT>::iterator ib   =  m_WaitPacket.begin();
				map< X_INT, X_INT>::iterator iend   =  m_WaitPacket.end();
				for (;ib != iend;++ib)
				{
					ib->second += nTime;
					if (ib->second >1000)
					{
						vector<string> v_Str;
						v_Str.push_back(UtilTools::GET_TEXT_FROM_LANG(580));
						EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,v_Str);
						break;
					}
				}*/
				_ProcessNetDataWorking();
			}
			break;
	}
}
X_VOID		NetworkSystem::__reconnectServer()
{
	return;
	ResetNetWorkState();

	if(m_pClientSocket != X_NULL)
	{

		m_pClientSocket->Close();
		SAFE_DELETE(m_pClientSocket);
	}
	if(m_pSocketStream != X_NULL)
	{
		m_pSocketStream->CleanUp();
		SAFE_DELETE(m_pSocketStream);
	}
  
	m_pClientSocket	= new SocketClient();
	if(m_pClientSocket == X_NULL)
	{
		return;
	}

	m_pSocketStream = new SocketStream();
	if(m_pSocketStream == X_NULL)
	{
		return;
	}
	X_BOOL bResult =  m_pSocketStream->Init(m_pClientSocket);

	m_nConnectStartTime			= 0;
	FD_ZERO( &m_ReadFDs[EM_SELECT_BAK] ) ;
	FD_ZERO( &m_WriteFDs[EM_SELECT_BAK] ) ;
	FD_ZERO( &m_ExceptFDs[EM_SELECT_BAK] ) ;
	FD_ZERO( &m_ReadFDs[EM_SELECT_USE] ) ;
	FD_ZERO( &m_WriteFDs[EM_SELECT_USE] ) ;
	FD_ZERO( &m_ExceptFDs[EM_SELECT_USE] ) ;
	m_Timeout[EM_SELECT_BAK].tv_sec = 0;
	m_Timeout[EM_SELECT_BAK].tv_usec = 0;
 
	m_pClientSocket->Create(m_szServerIP,m_nServerPort);
	if(IsValid() == XFALSE)
		m_pClientSocket->CreateSocket();
	 
	ConnectServer(m_szServerIP,m_nServerPort);

	cocos2d::CCLog("__reconnectServer");

}
X_VOID NetworkSystem::ConnectServer(const X_CHAR* szServerIP, X_INT nServerPort)
{ 
	SystemTimer* pSystemTimer = SystemTimer::GetSingleton();
	if(pSystemTimer == X_NULL)
	{
		return;
	}
	memset(m_szServerIP,0,sizeof(m_szServerIP));
	memcpy(m_szServerIP,szServerIP,sizeof(m_szServerIP));
	m_nServerPort		= nServerPort;
 
	m_nConnectStartTime = pSystemTimer->GetNowTime();
	m_pClientSocket->Create(m_szServerIP,m_nServerPort);
	if(IsValid() == XFALSE)
		 m_pClientSocket->CreateSocket();
	__createConnectThread();
	SetNetworkState(NET_CONNECTING_STATE);
	
}

//断开连接
X_VOID NetworkSystem::DisconnectServer()
{
	if(m_pClientSocket)
	{
		m_pClientSocket->SocketClose();
	}
}

//发送数据
X_BOOL NetworkSystem::SendPacket(Packet* pPacket)
{

		if(m_pClientSocket == X_NULL || m_pClientSocket->IsSocketValid() == X_FALSE)
		{
			if (m_pClientSocket== X_NULL)
			{
				cocos2d::CCLog("m_pClientSocket == X_NULL");

			}
			 _showNetErrorBox();
			return XFALSE;
		}
			
		if(m_pSocketStream == X_NULL)
		{
			_showNetErrorBox();
			cocos2d::CCLog("m_pSocketStream == X_NULL");
			return XFALSE;
		}
		if(m_nNetworkState != NET_DATA_WORKING)
		{
				cocos2d::CCLog("m_nNetworkState != NET_DATA_WORKING");
				if (m_nNetworkState == NET_NORMAL)
				{
					//__reconnectServer();
				}
				return XFALSE;
		}
		
			
		if(pPacket == X_NULL)
			return X_FALSE;
 
		X_ULLONG nNowTime = SystemTimer::GetSingleton()->GetNowTime();
		map< X_INT, X_INT>::iterator ifind   =  m_allPacketCd.find(pPacket->GetPacketID());
		if (ifind != m_allPacketCd.end())
		{
			if(nNowTime < ifind->second + 1500)  //1s
			{
				return XFALSE;  		  
			}
		} 
		vector<X_INT>::iterator ipass =  find(m_AllLimit.begin(),m_AllLimit.end(),pPacket->GetPacketID() );
		if (ipass != m_AllLimit.end())
		{
				m_allPacketCd[pPacket->GetPacketID()] = nNowTime;
		}

		X_INT nSizeBefore = m_pSocketStream->GetOutputStream()->Length();
		X_INT nSizeAfter = 0;
		X_INT nWriteSize = 0;
		X_BOOL bRet = X_FALSE;
	 
			//查询当前包尾位置。记录写包前位置
			X_INT nTail_Begin = m_pSocketStream->GetOutputStream()->GetTail();
			bRet = m_pSocketStream->WritePacket(pPacket);
			//查询当前包尾位置。记录写包后位置
			X_INT nTail_End = m_pSocketStream->GetOutputStream()->GetTail();
			nSizeAfter = m_pSocketStream->GetOutputStream()->Length();
			nWriteSize = nSizeAfter-nSizeBefore;
#ifdef __ENCRYPT__
			{
				X_INT nHead = m_pSocketStream->GetOutputStream()->GetHead();
				X_INT nTail = m_pSocketStream->GetOutputStream()->GetTail();
				X_INT nBufferLen = m_pSocketStream->GetOutputStream()->Capacity();
				X_CHAR* szBuffer = m_pSocketStream->GetOutputStream()->GetBuffer();
				if ( nHead < nTail ) 
				{
					//X_INT nSize = nTail_End - nTail_Begin;
					Encrypt_SC(&(szBuffer[nTail_Begin]), nWriteSize);
				} 
				else
				{
					if (nTail_End < nTail_Begin)
					{
						X_INT rightLen = nBufferLen - nTail_Begin;
						Encrypt_SC(&(szBuffer[nTail_Begin]), rightLen);
						Encrypt_SC(szBuffer, nWriteSize-rightLen);
					}
					else
					{
						Encrypt_SC(&(szBuffer[nTail_Begin]), nWriteSize);
					}
				}
			}
#endif
 
		if(pPacket->GetSize() != nWriteSize-PACKET_HEADER_SIZE)
		{
			cocos2d::CCLog( "Packet Size Error! ID=%d, SIZE=%d, should=%d", pPacket->GetPacketID(), pPacket->GetSize(), nSizeAfter - nSizeBefore - PACKET_HEADER_SIZE);
			//Log::GetInstance()->CacheLog(LOG_FILE_ERROR, "Packet Size Error! ID=%d, SIZE=%d, should=%d", pPacket->GetPacketID(), pPacket->GetSize(), nSizeAfter - nSizeBefore - PACKET_HEADER_SIZE);
		}
		//m_WaitPacket[pPacket->GetPacketID()] = 0;
             
        cocos2d::CCLog( "send Packet     ID=%d, ------------------------------------------------- ", pPacket->GetPacketID() );
		return XTRUE;
}
 
 
X_VOID NetworkSystem::SetNetworkState(NET_WORK_STATE nState)
{
		m_nNetworkState = nState;
}
NetworkSystem::NET_WORK_STATE	NetworkSystem::GetNetworkState()
{

		return m_nNetworkState;
}

X_VOID NetworkSystem::_ProcessNetConnecting()
{  

#ifdef __WINDOWS__
	X_INT nThreadExitCode =0;
	::GetExitCodeThread(m_thread, (LPDWORD)&nThreadExitCode);
	if(!bconnectRet &&nThreadExitCode == STILL_ACTIVE)
	{
		
		SystemTimer *pSystemTimer = SystemTimer::GetSingleton();
		X_ULLONG nNowTime = pSystemTimer->GetNowTime();
		if(nNowTime - m_nConnectStartTime >= MAX_TIME_OUT)
		{
			TerminateThread(m_thread, 0);
		}
		else
		{
			return;
		}
	}
	if(m_thread)
	{
		::CloseHandle(m_thread);
		m_thread = 0;
	}
#else
    if(!bconnectRet)
    {
        SystemTimer *pSystemTimer = SystemTimer::GetSingleton();
		X_ULLONG nNowTime = pSystemTimer->GetNowTime();
		if(nNowTime - m_nConnectStartTime >= MAX_TIME_OUT)
		{
			pthread_exit(m_thread);
		}
		else
		{ 
			return;
		}
    }
	if (m_thread)
	{
		m_thread = 0;
	}

#endif

	MainGame::GetSingleton()->ConnectServerDone(bconnectRet);
}
X_VOID NetworkSystem::_ProcessNetReConnecting()
{  

}
X_VOID NetworkSystem::_ConnectServer(bool notify )
{
    
	 if(IsValid() == XFALSE)
		 m_pClientSocket->CreateSocket();
	 bconnectRet =  m_pClientSocket->Connect();
	 m_pClientSocket->SetNonBlocking(XTRUE);
	 m_pClientSocket->SetSendBufferSize(DEFAULT_CLIENT_SEND_BUFFERSIZE);  
	 m_pClientSocket->SetReceiveBufferSize(DEFAULT_CLIENT_RECV_BUFFERSIZE);
	 m_pClientSocket->SetLinger( 0 ) ;
	 _UseSocket() ;
} 
 
X_VOID NetworkSystem::_ProcessNetDataWorking()
{
	if(m_pClientSocket == X_NULL || m_pSocketStream == X_NULL)
		return;
	

	if(_ProcessExceptions() == X_FALSE)
	{
		return;
	}
    if(_DoSelect() == X_FALSE)
	{
		return;
	}
	if(m_pClientSocket->IsSocketValid() == X_FALSE)
	{
		_showNetErrorBox();
		__reconnectServer();
		return;
	}
	if(_ProcessInput() == X_FALSE)
	{
		_showNetErrorBox();
 		cocos2d::CCLog("_ProcessInput() == X_FALSE");
		//__reconnectServer();
		return;
		 
 	}
	if(_ProcessOutput() == X_FALSE)
	{
		_showNetErrorBox();
		cocos2d::CCLog("_ProcessOutput() == X_FALSE");
		//__reconnectServer();
		return;
	}
	_ProcessPacketData();
 
}
X_VOID	NetworkSystem::_showNetErrorBox()
{
	if (m_nNetworkState == NET_DATA_WORKING)
	{

		Game::logOffCallBack(); //不提示 直接重连
		return;
		cocos2d::CCLog("m_pClientSocket->IsSocketValid()");
		ModalDialogView * pView = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(565),MainGame::GetSingleton()->getDelegate() ,DIALOG_MODEL_SINGLE);
		SceneManger::GetSingleton()->AddChildToScene(pView,true);
	}
}
X_BOOL NetworkSystem::_ProcessOutput( )
{
	if(m_pSocketStream == X_NULL ||m_pClientSocket ==X_NULL|| !m_pClientSocket->IsSocketValid()) return X_FALSE;
	X_INT nSize = m_pSocketStream->GetOutputStream()->Length() ;
	if( nSize == 0 )
	{
		return XTRUE ;
	}
	X_SOCKET s =m_pClientSocket->GetSocket();
	X_INT nRet = -1;
	if( FD_ISSET( s, &m_WriteFDs[EM_SELECT_USE] ) )
	{
		 nRet = m_pSocketStream->Send( ) ;
		 if( nRet <= SOCKET_ERROR )
		 { 
			 return XFALSE ;
		 }
	}
	
	return XTRUE;
}
X_BOOL NetworkSystem::_ProcessInput( )
{
	if(m_pSocketStream == X_NULL ||m_pClientSocket ==X_NULL|| !m_pClientSocket->IsSocketValid()) return XFALSE;
	X_SOCKET s =m_pClientSocket->GetSocket();
	if( FD_ISSET( s, &m_ReadFDs[EM_SELECT_USE] ) )
	{
		if( m_pClientSocket->IsSockError() )
		{
			cocos2d::CCLog("m_pClientSocket->IsSockError................");
			m_pClientSocket->Close();
			 return XFALSE;
			 
		}
		X_INT nRet = m_pSocketStream->Reveive( ) ;
		cocos2d::CCLog("nRet = m_pSocketStream->Reveive( )................%d",nRet);
		if( nRet <= SOCKET_ERROR )
		{ 
			/*if ( -6 == nRet)
			{
				return XTRUE;
			}*/
			m_pClientSocket->Close();
			return XFALSE ;
		}
	}
	return XTRUE;
}
X_BOOL	NetworkSystem::_ProcessExceptions()
{
	if(m_pSocketStream == X_NULL ||m_pClientSocket ==X_NULL|| !m_pClientSocket->IsSocketValid()) return XFALSE;
	if( FD_ISSET( m_pClientSocket->GetSocket(), &m_ExceptFDs[EM_SELECT_USE] ) )
	{
		return XFALSE;
	}
	return XTRUE ;
}	
X_BOOL	NetworkSystem::_DoSelect()
{
	if(m_pSocketStream == X_NULL ||m_pClientSocket ==X_NULL|| !m_pClientSocket->IsSocketValid()) return XFALSE;

	m_Timeout[EM_SELECT_USE].tv_sec  = m_Timeout[EM_SELECT_BAK].tv_sec;
	m_Timeout[EM_SELECT_USE].tv_usec = m_Timeout[EM_SELECT_BAK].tv_usec;

	m_ReadFDs[EM_SELECT_USE]   = m_ReadFDs[EM_SELECT_BAK];
	m_WriteFDs[EM_SELECT_USE]  = m_WriteFDs[EM_SELECT_BAK];
	m_ExceptFDs[EM_SELECT_USE] = m_ExceptFDs[EM_SELECT_BAK];
	X_INT iRet = SocketInterface::socket_select( m_pClientSocket->GetSocket()+1, 
		&m_ReadFDs[EM_SELECT_USE] , 
		&m_WriteFDs[EM_SELECT_USE] , 
		&m_ExceptFDs[EM_SELECT_USE] , 
		&m_Timeout[EM_SELECT_USE] ) ;
	if (iRet == SOCKET_ERROR)
	{
		return XFALSE;
	}
	return XTRUE ;
}
X_BOOL	 NetworkSystem::_UseSocket()
{
	if(m_pSocketStream == X_NULL ||m_pClientSocket ==X_NULL|| !m_pClientSocket->IsSocketValid()) return XFALSE;

	X_SOCKET fd = m_pClientSocket->GetSocket();
	FD_SET(fd , &m_ReadFDs[EM_SELECT_BAK]);
	FD_SET(fd , &m_WriteFDs[EM_SELECT_BAK]);
	FD_SET(fd , &m_ExceptFDs[EM_SELECT_BAK]);
	return XTRUE;
}
X_VOID NetworkSystem::_ProcessPacketData()
{
	if(m_pClientSocket == X_NULL||m_pSocketStream == X_NULL)
		return;

	X_CHAR	szPacketHead[PACKET_HEADER_SIZE];	//数据包头
	PacketID	nPacketID;			//数据包ID
	X_CHAR		nFlag;				//数据标识
	X_UINT	nPacketLength;		//数据长度

	InputStream* pInputStream = m_pSocketStream->GetInputStream();
		while(XTRUE)
		{
			memset(szPacketHead, 0, sizeof(szPacketHead));
			nPacketID = 0;
			nPacketLength = 0;
			nFlag = 0;

			if(m_pClientSocket == X_NULL ||m_pSocketStream == X_NULL)
				return;

			if(pInputStream->Peek(szPacketHead, PACKET_HEADER_SIZE) == X_FALSE)
			{
				return;
			}
			memcpy(&nPacketID, szPacketHead, sizeof(nPacketID));
			memcpy(&nFlag, szPacketHead+sizeof(nPacketID), sizeof(nFlag));
			memcpy(&nPacketLength, szPacketHead+sizeof(nPacketID)+sizeof(nFlag), sizeof(nPacketLength));
			///协议解密--Begin
#ifdef __ENCRYPT__
			{
				X_INT nSize = nPacketLength+PACKET_HEADER_SIZE;
				X_INT nHead = pInputStream->GetHead();
				X_INT nTail = pInputStream->GetTail();
				X_INT nBufferLen = pInputStream->Capacity();
				X_CHAR* szBuffer = pInputStream->GetBuffer();
				if ( nHead < nTail ) 
				{
					Decrypt_CS(&szBuffer[nHead], nSize);
				}
				else 
				{
					X_INT rightLen = nBufferLen - nHead;
					if( nSize <= rightLen ) 
					{
						Decrypt_CS(&szBuffer[nHead], nSize);
					} 
					else
					{
						Decrypt_CS(&szBuffer[nHead], rightLen);
						Decrypt_CS(szBuffer, nSize-rightLen);
					}
				}
			}
#endif
			//cocos2d::CCLog("---------------------------NetworkSystem::_ProcessPacketData()");
			if(m_pPacketFactoryManager->CheckPacketID(nPacketID) != XTRUE )
			{
				pInputStream->Skip(nPacketLength + PACKET_HEADER_SIZE);
				return;
			}
            static PacketID lastPacketID = 0;

            //判断长度是否在网络包的大小内
			if(nPacketLength > m_pPacketFactoryManager->GetPacketMaxSize(nPacketID))
			{
				char str[100];
				sprintf(str,"sizeof (guid ) = %d ,packet id == %d, nPacketLength ==%d , GetPacketMaxSize() == %d",sizeof(X_GUID),nPacketID,nPacketLength,m_pPacketFactoryManager->GetPacketMaxSize(nPacketID));
				cocos2d::CCLog(str);
			 

				cocos2d::CCLog("---------------------------NetworkSystem::_ProcessPacketData()  size error");
				//跳跃错误内存段
				pInputStream->Skip(nPacketLength + PACKET_HEADER_SIZE);
				return;
			}
			//消息没有接收全
			if( pInputStream->Length()< X_INT(PACKET_HEADER_SIZE+nPacketLength) )
			{
				break;
			}

			//得到网络包的实体
			Packet* pPacket = m_pPacketFactoryManager->CreatePacket(nPacketID);
			if(pPacket == X_NULL)
			{
				cocos2d::CCLog("---------------------------NetworkSystem::_ProcessPacketData()  packet null");
				//跳跃错误内存段
				pInputStream->Skip(nPacketLength + PACKET_HEADER_SIZE);
				 return;
			}
			//读取网络数据
			if(m_pSocketStream->ReadPacket( pPacket )== X_FALSE  ||(pPacket->GetSize() != nPacketLength))
			{
				cocos2d::CCLog("---------------------------NetworkSystem::_ProcessPacketData()  read error");
			 		return;
			}
			lastPacketID = nPacketID;


			/*map< X_INT, X_INT>::iterator ifind   =  m_WaitPacket.find(nPacketID);
			if (ifind != m_WaitPacket.end())
			{
				m_WaitPacket.erase(ifind);
			} */


			PacketExecute::ExecutePacket(nPacketID, pPacket);
			m_pPacketFactoryManager->RemovePacket(pPacket);
			//cocos2d::CCLog("---------------------------NetworkSystem::_ProcessPacketData()  ok");
			pPacket = X_NULL;
		}

		SystemTimer* pSystemTimer = SystemTimer::GetSingleton();
		if(pSystemTimer == X_NULL)
			return;
}
X_BOOL	NetworkSystem::IsValid( )
{
	if( m_pClientSocket == X_NULL )
	{
		return XFALSE ;
	}
	return m_pClientSocket->IsSocketValid();
 
}
//服务器通知登录错误的处理函数
X_VOID NetworkSystem::ResetNetWorkState()
{
	SetNetworkState(NetworkSystem::NET_NORMAL);
	if(m_pClientSocket != X_NULL)
	{
		m_pClientSocket->Close();
	}
}

int NetworkSystem::__createConnectThread()
{
#ifdef __WINDOWS__
	X_UINT nConnectThreadID = -1;
	m_thread = (HANDLE)::_beginthreadex(X_NULL, 0, __connectThread, this, CREATE_SUSPENDED|THREAD_QUERY_INFORMATION, &nConnectThreadID);

	if(m_thread != X_NULL)
		ResumeThread(m_thread);
	return 0;
#else
	int errCode=0;  
	do {  
		pthread_attr_t tAttr;  
		errCode=pthread_attr_init(&tAttr);  
		CC_BREAK_IF(errCode!=0);  
		errCode=pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);  
		if(errCode!=0)  
		{  
			pthread_attr_destroy(&tAttr);  
			break;  
		}  
		errCode=pthread_create(&m_thread, &tAttr, __connectThread, this);  

	} while (0);  
	return errCode;  

#endif
}
#ifdef __WINDOWS__
X_UINT NetworkSystem::__connectThread(LPVOID pParam)
{ 
	NetworkSystem::GetSingleton()->_ConnectServer();
		return true;
}
#else
void*   NetworkSystem::__connectThread(void *pParam)
{ 
	 NetworkSystem::GetSingleton()->_ConnectServer();

	return 0; 

}
#endif
