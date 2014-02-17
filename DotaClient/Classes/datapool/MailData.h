#ifndef __MAILDATA_H__
#define __MAILDATA_H__

#include "./base/Global.h"
#include "./GameStruct.h"


/*
enum EM_TYPE_MAIL
{
	EM_TYPE_MAIL_INVALID=-1,
	EM_TYPE_MAIL_NORMAL,					//普通邮件
	EM_TYPE_MAIL_SYSTEM,					//系统邮件
	EM_TYPE_MAIL_EXE,						//可执行邮件

	EM_TYPE_MAIL_COUNT

};*/
 class Message
 {

	 friend class MailData;
 public:
	 //获得title
	const X_CHAR * getTitle()const;
	//消息内容
	const X_CHAR * getContex()const;
	//发信人
	const X_CHAR * getSenderName()const; 

	bool isOpened()const;
	bool CanRevenge() const;

	string   getDate()const;
	string   getDateHour()const;
	X_GUID   getRevengeGUID() const;
	X_INT    getIndex() const;
	

	//读取邮件
	X_VOID    Read(bool bSendToServer = true);
	X_VOID    Reply(const string &title,const string & text);
	X_VOID    Delete();
	X_VOID    OnReadAll();
	EM_TYPE_MAIL getType()const;
	EM_MAIL_SYSTEM_TYPE  getSysyemSubType()const;

	string   getIcon()const;
 protected:
	 const  Mail*  pMail;
	 bool		m_free;
	 X_VOID CleanUp();

	 int   _getDate()const;
	 int   _getDateHour()const;
	 EM_STATUS_MAIL m_status;
 };




class  MailData
{
	friend class Message;
public:
 
	X_INT getMailNum();

	const vector<Message*> & getMail()
	{
		return m_Messages;
	}

	bool getNotifyMail()const;
	void setNotifyMail(bool flag);

public:

	X_VOID Initial();
	X_VOID Release();
	X_VOID setServerData( const MailBoxData * pdata);

private:
	const MailBoxData *m_pdata;
	vector<Message*>  m_Messages;
	const Mail* getMail(X_INT index); 

	vector<Message*>  m_MessagesPool;
	Message* __getFreeMeaasge();
protected:
	bool	isNotifyMail;
	X_INT   _unReadNum;
	static bool	 __dataSort1(const Message *p1,const Message *p2);
	 

};

 


#endif