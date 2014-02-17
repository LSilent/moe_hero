 

#ifndef __NETWORKSYSTEM_H__
#define __NETWORKSYSTEM_H__

#include "./base/Global.h"
#include "./base/Singleton.h"
#include "./Packets/Base/Packet.h"
#include <map>

#define MAX_CLIENT_SOCKET_COUNT 1	//定义客户端最大连接数
#define MAX_TIME_OUT 1000*3			//网络连接超时 5

class PacketClientFactoryManager;
class SocketClient;
//selectƒ£–Õœ¬ π”√


#ifdef __WINDOWS__
#include <process.h>
#else
#include<pthread.h>
#endif // __windows__



enum EM_SELECT
{
	EM_SELECT_BAK = 0,	//完整句柄
	EM_SELECT_USE = 1,	//用于select调用句柄
	EM_SELECT_MAX = 2, //数量
};
class NetworkSystem : public Singleton<NetworkSystem>
{
	DECLARE_SINGLETON(NetworkSystem);
public:
	enum NET_WORK_STATE
	{
		NET_NORMAL = 0,			//正常状态
		NET_CONNECTING_STATE,	//连接状态
		NET_RECONNECTING_STATE,
		NET_CONNECTED_OK_STATE,	//连接完成状态
		NET_DATA_WORKING,		//接收发送数据状态
	};
public:
	NetworkSystem();
	virtual ~NetworkSystem();

public:
	X_VOID		Initial();
	X_VOID		Release();
	X_VOID		Tick(X_UINT nTime);
	X_VOID		SetNetworkState(NET_WORK_STATE nState);
	NET_WORK_STATE	GetNetworkState();
	X_VOID		ConnectServer(const X_CHAR* szServerIP, X_INT nServerPort);
	X_VOID		DisconnectServer();
	X_BOOL		SendPacket(Packet* pPacket);
 	X_VOID		ResetNetWorkState();

	X_VOID		__reconnectServer();
private:
	 
	X_VOID					_ProcessNetConnecting();
	X_VOID					_ProcessNetDataWorking();
	X_VOID					_ProcessPacketData();
	X_VOID					_ConnectServer(bool notify = true);
	X_BOOL					_ProcessOutput();
	X_BOOL					_ProcessInput();
	X_BOOL					_ProcessExceptions();
	X_BOOL					_DoSelect();
	
	X_BOOL					_UseSocket();
	X_BOOL					IsValid();

	X_VOID					_ProcessNetReConnecting();
 
	X_VOID					_showNetErrorBox();
private:

	SocketClient*			m_pClientSocket;		 
	//输入输出数据缓存
	SocketStream*			m_pSocketStream ;

	X_ULLONG					m_nConnectStartTime;
	X_CHAR					m_szServerIP[16];
	X_INT					m_nServerPort;
	NET_WORK_STATE			m_nNetworkState;
	PacketClientFactoryManager*	m_pPacketFactoryManager;
 
	fd_set					m_ReadFDs[EM_SELECT_MAX];		//读fd
	fd_set					m_WriteFDs[EM_SELECT_MAX];		//写fd
	fd_set					m_ExceptFDs[EM_SELECT_MAX];		//异常fd
	timeval					m_Timeout[EM_SELECT_MAX];		//select延迟返回时间配置


	static const X_INT DEFAULT_CLIENT_SEND_BUFFERSIZE = 1600*1024;
	static const X_INT DEFAULT_CLIENT_RECV_BUFFERSIZE = 1600*1024;

	map< X_INT, X_INT>    m_allPacketCd;

	//map<X_INT,X_INT>     m_WaitPacket;

	vector<X_INT>   m_AllLimit;
	bool   m_init;

	  
#ifdef __WINDOWS__
	HANDLE m_thread;
	static X_UINT CALLBACK __connectThread(LPVOID pParam);
#else
#include<pthread.h>
	pthread_t m_thread;
	static void* __connectThread(void *pParam);
#endif

	int  __createConnectThread();
    bool bconnectRet;
	 
};

#endif