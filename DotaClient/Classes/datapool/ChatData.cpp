#include "./datapool/ChatData.h"

ChatChannel::ChatChannel(X_INT nmaxMsgNum)
{ 
	m_maxMsgNum = nmaxMsgNum;
}
 
bool ChatChannel::hasChannel(ENUM_CHAT_TYPE chanel)
{
	switch(chanel)
	{
		case CHAT_TYPE_USER:
			{
				return m_Chanel.bPrivate;
			}
			break;

		case CHAT_TYPE_WORLD:
			{
				return m_Chanel.bWorld;

			}
			break;

		case CHAT_TYPE_SYSTEM:
			{
				return m_Chanel.bSystem;
			}
			break;
		case CHAT_TYPE_NOTICE:
			{
				return m_Chanel.bTips;
			}
			break;
	}
	return false;
 
}
X_VOID		ChatChannel::SetChannel(ENUM_CHAT_TYPE chanel, bool bFlag )
{
	 
	switch(chanel)
	{

		case CHAT_TYPE_USER:
			{
				m_Chanel.bPrivate  = bFlag; 
			}
			break;
		case CHAT_TYPE_WORLD:
			{
				m_Chanel.bWorld = bFlag;

			}
			break;
		 
		case CHAT_TYPE_SYSTEM:
			{
				m_Chanel.bSystem = bFlag;
			}
			break;
	 
		case CHAT_TYPE_NOTICE:
			{
				m_Chanel.bTips = bFlag;
			}
			break;
	}
}
X_VOID		ChatChannel::AddChatMsg(const Record &record)
{
		if((X_INT)m_List.size() >= m_maxMsgNum)
		{ 
			m_List.pop_front();
		}
		m_List.push_back(record);
}

X_VOID		ChatChannel::GetChatMsg(Record &record,X_INT nMsgIndex)
{
	 
	record.CleanUp();
	if (m_List.empty())
	{
		return;
	}
	if (nMsgIndex ==-1)
	{
		record = (m_List.back() );
		return;
	}
	if ( 0<= nMsgIndex && nMsgIndex < (X_INT)m_List.size())
	{
		RecordList::iterator it = m_List.begin();
		advance(it,nMsgIndex);
		record =  *it;
	}
}
X_INT	ChatChannel::GetMsgNumber()
{
	return m_List.size();
}

X_VOID	ChatChannel::ClearAllMessage()
{ 
	m_List.clear();
}

 
 
X_VOID		ChatData::Initial()
{
	m_AllChannel[All_Channel] = new ChatChannel(); // 包含全部频道
	m_AllChannel[World_Channel] = new ChatChannel();//世界、系统
	m_AllChannel[Private_Channel] = new ChatChannel();//私聊
	m_AllChannel[Set1_Channel] = new ChatChannel();// 滚屏公告
 
	_InitialDefault();
}
 
X_VOID		ChatData::Release()
{
		for( X_INT i = All_Channel;i < Channel_MaxNum ;i++)
		{
			ClearChatMsg( Channel(i));
			SAFE_DELETE(m_AllChannel[i]);
		}
}

X_VOID		ChatData::AddChatMsg(const Record &record)
{
		for( X_INT i = 0;i < Channel_MaxNum ;i++)
		{
			if (m_AllChannel[i]->hasChannel(record.m_nChatType))
			{
				m_AllChannel[i]->AddChatMsg(record);
			}
		}
}

X_VOID		ChatData::GetChatMsg(Channel chanel, Record &record,X_INT nMsgIndex)
{
		if (chanel < All_Channel || chanel >= Channel_MaxNum)
		{
			return;
		}
		m_AllChannel[chanel]->GetChatMsg( record,nMsgIndex);
}

X_INT	ChatData::GetMsgNumber(Channel nChannel)
{
		if (nChannel < All_Channel || nChannel >= Channel_MaxNum)
		{
			return 0;
		}
		return m_AllChannel[nChannel]->GetMsgNumber();
}

X_VOID		ChatData::ClearChatMsg(Channel nChannel)
{
		if (nChannel < All_Channel || nChannel >= Channel_MaxNum)
		{
			return;
		}
		m_AllChannel[nChannel]->ClearAllMessage();
}
X_VOID ChatData::SetChannel(Channel mChanel, ENUM_CHAT_TYPE sChanel, bool bValue )
{
		if (mChanel < All_Channel || mChanel >= Channel_MaxNum)
		{
			return;
		}
		m_AllChannel[mChanel]->SetChannel( sChanel, bValue );
}
bool ChatData::GetChannel(Channel mChanel, ENUM_CHAT_TYPE sChanel)
{
		if (mChanel < All_Channel || mChanel >= Channel_MaxNum)
		{
			return false;
		}
		return m_AllChannel[mChanel]->hasChannel(sChanel);
}
X_VOID ChatData::_InitialDefault()
{
	ChatChannel::st_Channel defaultInfo;
	defaultInfo.bPrivate = true;
	defaultInfo.bWorld = true;
	defaultInfo.bSystem = true;
	defaultInfo.bTips = false;
	if ( m_AllChannel[All_Channel] != X_NULL )
	{
		m_AllChannel[All_Channel]->SetDefault(defaultInfo);
	}
	defaultInfo.bPrivate = false;
	defaultInfo.bWorld = true;
	defaultInfo.bSystem = true;
	defaultInfo.bTips = false;
	if ( m_AllChannel[World_Channel] != X_NULL )
	{
		m_AllChannel[World_Channel]->SetDefault(defaultInfo);
	}
	defaultInfo.bPrivate = true;
	defaultInfo.bWorld = false;
	defaultInfo.bSystem = false;
	defaultInfo.bTips = false;
	if ( m_AllChannel[Private_Channel] != X_NULL )
	{
		m_AllChannel[Private_Channel]->SetDefault(defaultInfo);
	}
	defaultInfo.bPrivate = false;
	defaultInfo.bWorld = false;
	defaultInfo.bSystem = false;
	defaultInfo.bTips = true;
	if ( m_AllChannel[Set1_Channel] != X_NULL )
	{
		m_AllChannel[Set1_Channel]->SetDefault(defaultInfo);
	}
}
 