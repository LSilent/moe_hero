#ifndef __CHATDATA_H__
#define __CHATDATA_H__
#include "./base/Global.h"
#include <list>

class Record 
{
public:
	Record(ENUM_CHAT_TYPE nChatType, 
		X_INT nValue, 
		string strName, 
		string strContex)
	{
		m_nChatType		= nChatType;
		m_nValue		= nValue;
		m_strName		= strName;
		m_strContex		= strContex;
	}
	Record()
	{
		CleanUp();
	}
	Record(Record const& record)
	{
		m_nChatType		= record.m_nChatType;
		m_nValue		= record.m_nValue;
		m_strName		= record.m_strName;
		m_strContex		= record.m_strContex;
	}
	Record& operator=(Record const& record)
	{
		m_nChatType		= record.m_nChatType;
		m_nValue		= record.m_nValue;
		m_strName		= record.m_strName;
		m_strContex		= record.m_strContex;
		return *this;
	}
	X_VOID CleanUp()
	{
		m_nChatType = CHAT_TYPE_INVALID;
		m_nValue = -1;
		m_strName ="";
		m_strContex ="";
	}
	ENUM_CHAT_TYPE m_nChatType; 
	X_CLIENT_GUID m_nValue; 
	string m_strName; 
	string m_strContex;	
};

// 表示具体的频道  
// 私聊频道 世界频道 系统频道  滚屏公告
  
class ChatChannel
{
public:
	struct st_Channel
	{
		st_Channel()
		{
			CleaUp();
		}
		X_VOID CleaUp()
		{
			bPrivate = false;
			bWorld = false;
			bSystem = false;
			bTips = false;
		}
		st_Channel& operator=(const st_Channel& channel)
		{
			bPrivate = channel.bPrivate;
			bWorld = channel.bWorld;
			bSystem = channel.bSystem;
			bTips = channel.bTips;
			return *this;
		}
	public:
		bool	bPrivate;
		bool	bWorld;
		bool	bSystem;
		bool	bTips;
	};

	ChatChannel(X_INT m_maxMsgNum = 50);
	bool		hasChannel(ENUM_CHAT_TYPE chanel);
	X_VOID		SetChannel(ENUM_CHAT_TYPE chanel, bool bFlag = true );

	X_VOID		AddChatMsg(const Record &record);
	X_VOID		GetChatMsg(Record &record,X_INT nMsgIndex =-1);
	X_INT		GetMsgNumber();
	X_VOID		ClearAllMessage();

	X_VOID         SetDefault(const st_Channel& defInfo )
	{
		m_Chanel = defInfo;
	}
	X_VOID         GetCurrent(st_Channel& curInfo ){ curInfo = m_Chanel; }
	X_VOID         SetCurrent(const st_Channel& curInfo ){ m_Chanel = curInfo; }
 
public:
	typedef std::list<Record> RecordList;
	RecordList		m_List; 
protected:
	X_INT	m_maxMsgNum;
	st_Channel m_Chanel;
};

enum  Channel
{
	All_Channel = 0,//系统
	World_Channel,//世界
	Private_Channel,//个人
	Set1_Channel,//滚屏
	Channel_MaxNum
};
class ChatData
{
public:
 
	X_VOID		Initial();
	X_VOID		Release();
	X_VOID     SetChannel(Channel mChanel, ENUM_CHAT_TYPE sChanel, bool bValue );
	bool       GetChannel(Channel mChanel, ENUM_CHAT_TYPE sChanel);
	X_VOID	   AddChatMsg(const Record &record);
	//---------------------------------------------------------------
	X_INT		GetMsgNumber(Channel nChannel);
	X_VOID		GetChatMsg(Channel chanel, Record &record,X_INT nMsgIndex =-1);

   
	X_VOID		ClearChatMsg(Channel nChannel);
protected:
	ChatChannel*        m_AllChannel[Channel_MaxNum];
	X_VOID      _InitialDefault();
}; 
 
#endif

