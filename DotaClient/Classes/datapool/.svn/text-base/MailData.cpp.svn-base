#include "./datapool/MailData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./datapool/DataPool.h"
X_VOID Message::CleanUp()
{
	m_free = true;
	pMail = X_NULL;
	m_status = EM_STATUS_MAIL_UNREAD;

}
const X_CHAR * Message::getTitle()const
{
	return pMail->m_Title;
}
const X_CHAR * Message::getContex()const
{
	return pMail->m_Contex;
}
const X_CHAR * Message::getSenderName()const
{
	if (getType() == EM_TYPE_MAIL_SYSTEM || getType() ==  EM_TYPE_MAIL_EXE)
	{
		return UtilTools::GET_TEXT_FROM_LANG(735);
	}
	else if(getType() == EM_TYPE_MAIL_WOODROB)
	{
		return UtilTools::GET_TEXT_FROM_LANG(736);
	}

	return pMail->m_SourName;
}
bool Message::isOpened()const
{
	return m_status == EM_STATUS_MAIL_READ;
}
string  Message::getDate()const
{
	
	return UtilTools::getDatestr(pMail->m_Date);
}

int   Message::_getDate()const
{
	if (!pMail)
	{
		return 0;
	}
	return pMail->m_Date;
}
int  Message:: _getDateHour()const
{
	if (!pMail)
	{
		return 0;
	}
	return pMail->m_HourMinSec;
}

string Message::getDateHour()const
{
	return UtilTools::getDateHourstr(pMail->m_HourMinSec);
}
X_VOID    Message::Read(bool bSendToServer)
{
	if (bSendToServer)
	{
		if (m_status != EM_STATUS_MAIL_READ)
		{
			if (SendLogicPacket::ReadMailByIndex(pMail->m_Index)) 
				m_status = EM_STATUS_MAIL_READ;
		}
	}else
	{
			m_status = EM_STATUS_MAIL_READ;
	}
	
	DataPool::GetSingleton()->getMailData()->_unReadNum--;
	DataPool::GetSingleton()->getMailData()->setNotifyMail( DataPool::GetSingleton()->getMailData()->_unReadNum >0);
}
X_VOID    Message::Reply(const string &title,const string & text)
{
	SendLogicPacket::WriteMail(pMail->m_SourGuid.GetValue(),title,text);
}
X_VOID    Message::Delete()
{
	SendLogicPacket::DeleteMailByIndex(pMail->m_Index);
}
EM_TYPE_MAIL Message::getType()const
{
	return pMail->m_Type;
}
 
EM_MAIL_SYSTEM_TYPE  Message::getSysyemSubType()const
{
	if (pMail->m_Type == EM_TYPE_MAIL_SYSTEM )
	{
		return    EM_MAIL_SYSTEM_TYPE(pMail->m_Param[0]);
 
	}
	return (EM_MAIL_SYSTEM_TYPE)-1;
}
string   Message::getIcon()const
{

	switch (pMail->m_Type)
	{

	case	EM_TYPE_MAIL_NORMAL:					//普通邮件
		return "mail_item2.png";
		break;
	case	EM_TYPE_MAIL_SYSTEM:					//系统邮件
		return "mail_item2.png";
		break;
	case	EM_TYPE_MAIL_EXE:						//可执行邮件
		{
			if (m_status == EM_STATUS_MAIL_READ)
			{
					return "mail_item2.png";
			}else
			{
					return "mail_item1.png";
			}
		}
		break;
	case	EM_TYPE_MAIL_WOODROB:					//掠夺伐木场邮件
		return "mail_item2.png";
		break;

	}
	return"mail_item2.png";
}
bool Message::CanRevenge() const
{
	if (pMail->m_Type != EM_TYPE_MAIL_WOODROB)
		return X_FALSE;
	return pMail->m_Param[0] > 0;
}

X_GUID Message::getRevengeGUID() const
{
	if (pMail->m_Type != EM_TYPE_MAIL_WOODROB)
		return INVALID_ID;
	return X_GUID(pMail->m_Param[1],pMail->m_Param[2]);
}

X_INT Message::getIndex() const
{
	return pMail->m_Index;
}

X_VOID MailData::setServerData(const MailBoxData * pdata)
 {
	 m_Messages.clear();
	 X_UINT size = m_MessagesPool.size();
	 for (X_UINT i = 0; i < size ;i++)
	 {
		  m_MessagesPool[i]->m_free = true;
	 }
	 m_pdata = pdata;
	 if (!m_pdata)return;
	 
	 X_UINT num = m_pdata->m_MailNum;

	 Message *m_pMessage = X_NULL;
	 _unReadNum = 0;
	 for (X_UINT i = 0; i < num;i++)
	 {
		 m_pMessage =  __getFreeMeaasge();
		 m_pMessage->pMail = &m_pdata->m_MailList[i];
		 m_pMessage->m_free = false;
		 m_pMessage->m_status =  m_pMessage->pMail->m_Status;
		 m_Messages.push_back(m_pMessage);

		 if (!m_pMessage->isOpened())
		 {
			 _unReadNum++;
		 } 
	 }
	setNotifyMail((_unReadNum > 0));
	std::sort(m_Messages.begin(),m_Messages.end(),__dataSort1);

 }
 bool	MailData::__dataSort1(const Message *p1,const Message *p2)
 {
	X_INT opened1 = p1->isOpened();
	X_INT opened2 = p2->isOpened();
	
	if (opened1 != opened2)
	{
		return  opened1 == false ;
	}

	X_INT d1 = p1->_getDate();
	X_INT d2 = p2->_getDate();
 
	if (d1 == d2)
	{
		  d1 = p1->_getDateHour();
		  d2 = p2->_getDateHour();
		  return d1 > d2;
	}else
	{
		return d1 >d2;
	}
 }


 bool MailData::getNotifyMail()const
 {
	 return isNotifyMail;
 }
 void MailData::setNotifyMail(bool flag)
 {
	 isNotifyMail = flag;
 }


 X_INT MailData::getMailNum()
 {
	return m_Messages.size();
 }
 const Mail* MailData::getMail(X_INT index)
 {
	 if (index < 0 ||!m_pdata|| index > getMailNum())
	 {
		 return X_NULL;
	 }
	 return  &m_pdata->m_MailList[index];
 }

 X_VOID MailData::Initial()
 {
	 m_Messages.clear();
	 m_MessagesPool.clear();

	 isNotifyMail = false;
	 _unReadNum = 0;
 }
 X_VOID MailData::Release()
 {
	 X_UINT size = m_MessagesPool.size();
	 for (X_UINT i = 0; i < size ;i++)
	 {
		SAFE_DELETE(m_MessagesPool[i]);
	 }
	 m_Messages.clear();
	 m_MessagesPool.clear();
 }
 Message* MailData::__getFreeMeaasge()
 {
	 X_UINT size = m_MessagesPool.size();
	 Message* pMessage = X_NULL;

	 for (X_UINT i = 0; i < size ;i++)
	 {
		 pMessage= m_MessagesPool[i];
		 if (pMessage&&pMessage->m_free)
		 {
			 pMessage->CleanUp();
			 return pMessage;
		 }
	 }
	 pMessage = new Message();
	 pMessage->CleanUp();
	 m_MessagesPool.push_back(pMessage);

	 return pMessage;
 }